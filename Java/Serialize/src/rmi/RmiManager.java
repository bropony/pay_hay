package rmi;

import rmi.Logger;
import rmi.SerializeStream;

import java.net.URI;
import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;

import org.java_websocket.client.WebSocketClient;
import org.java_websocket.framing.Framedata;
import org.java_websocket.handshake.ServerHandshake;

class Outgoing{
	public RmiCallbackBase __cb;
	public int __msgId;
	public SerializeStream __os;
	public Outgoing(RmiCallbackBase cb, int msgId, SerializeStream os){
		__cb = cb;
		__msgId = msgId;
		__os = os;
	}
}

class WebSocketClientImpl extends WebSocketClient{ 
	public WebSocketClientImpl(URI serverURI) {
		super(serverURI);
	}

	@Override
	public void onOpen(ServerHandshake handshakedata) {
		RmiManager.instance().onOpen(handshakedata);
	}

	@Override
	public void onMessage(String message) {
		RmiManager.instance().onMessage(message);
	}
	
	@Override
	public void onMessage( ByteBuffer bytes ) {
		RmiManager.instance().onMessage(bytes);
	}
	
	@Override
	public void onFragment( Framedata frame ) {
		RmiManager.instance().onFragment(frame);
	}

	@Override
	public void onClose(int code, String reason, boolean remote) {
		RmiManager.instance().onClose(code, reason, remote);
	}

	@Override
	public void onError(Exception ex) {
		RmiManager.instance().onError(ex);
	}
}

public class RmiManager implements Runnable{
	static private RmiManager _inst;
	static private Object _lock = new Object();
	static private Thread _timer;
	
	private long _rmiTimeout;
	private WebSocketClient _ws;
	private URI _serverURI;
	
	private Map<Integer, RmiCallbackBase> _mapCallback;
	private ArrayList<Outgoing> _outgoings;
	
	static public void initInstance(URI serverURI){
		if (null != _inst){
			return;
		}
		
		_inst = new RmiManager(serverURI);
		_timer.start();
	}
	
	static public RmiManager instance(){
		return _inst;
	}
	
	public RmiManager(URI serverURI){
		_rmiTimeout = 10000;
		_serverURI = serverURI;
		_ws = null;
		
		_mapCallback = new HashMap<Integer, RmiCallbackBase>();
		_outgoings = new ArrayList<Outgoing>();
		_timer = new Thread(this);
	}
	
	public void setRmiTimeout(long timeout){
		if (timeout > 300){
			_rmiTimeout = timeout;
		}
	}
	
	public void connect(){
		if (_ws == null || _ws.isClosed() || _ws.isFlushAndClose())
		{
			_ws = new WebSocketClientImpl(_serverURI);
			_ws.connect();
		}
	}

	public void onOpen(ServerHandshake handshakedata) {
		Logger.log("onOpen", "Net connection opened");
	}

	public void onMessage(String message) {
		SerializeStream __is = new SerializeStream(message.getBytes());
		onMessage(__is);
	}
	
	public void onMessage( ByteBuffer bytes ) {
		SerializeStream __is = new SerializeStream(bytes);
		onMessage(__is);
	}
	
	public void onFragment( Framedata frame ) {
		SerializeStream __is = new SerializeStream(frame.getPayloadData());
		onMessage(__is);
	}
	
	public void onMessage(SerializeStream __is){
		__is.decrypt();
		__is.startToRead();
		int msgId = __is.readInt();
		boolean isOk = __is.readBool();
		Integer key = new Integer(msgId);
		RmiCallbackBase cb = _mapCallback.get(key);
		if (null != cb){
			if (isOk){
				cb.__onResponse(__is);
			}
			else{
				String what = __is.readString();
				int code = __is.readInt();
				cb.__onError(what, code);
			}
			
			_mapCallback.remove(key);
		}
	}

	public void onClose(int code, String reason, boolean remote) {
		String __log = "" + code + ", " + reason + ", " + remote;
		Logger.log("onClose", __log);
	}

	public void onError(Exception ex) {
		Logger.log("onError", ex.toString());
	}
	
	public void invoke(RmiCallbackBase __cb, int __msgId, SerializeStream __os){
		Outgoing og = new Outgoing(__cb, __msgId, __os);
		
		synchronized(_lock){
			_outgoings.add(og);
		}
	}
	
	private void __sendOut(){
		
		if (this._ws == null){
			System.out.println("Connect to Server");
			
			this.connect();
			return;
		}
		
		while (_outgoings.size() > 0){
			if (!this._ws.isOpen()){
				
				if (this._ws.isConnecting())
				{
					System.out.println("Connecting to Server");
				}
				
				if (this._ws.isClosed() || this._ws.isFlushAndClose())
				{
					System.out.println("Reconnect to Server");
					this.connect();
				}
				
				break;
			}
			
			synchronized(_lock){
				Outgoing og = _outgoings.get(0);
				
				Integer key = new Integer(og.__msgId);
				_mapCallback.put(key, og.__cb);
				
				og.__os.encrypt();
				this._ws.send(og.__os.getBytes());
				
				_outgoings.remove(0);
			}
		}
		
		synchronized(_lock){
			Set<Integer> keySet = null;
			
			keySet = _mapCallback.keySet();
			
			Iterator<Integer> it = keySet.iterator();
			while (it.hasNext())
			{
				Integer key = it.next();
				
				RmiCallbackBase cb = _mapCallback.get(key);
				if (null == cb)
				{
					continue;
				}
					
				if (cb.isTimeout(_rmiTimeout))
				{
					cb.__onTimeout();
					_mapCallback.remove(key);
				}
			}
		}
	}
	
	@Override
	public void run(){
		while(true){
			try{
				Thread.sleep(30);
				__sendOut();
			}
			catch(InterruptedException e){
				Logger.log(e.toString());
			}
		}
	}
	
	public void join(){
		if (_timer != null && _timer.isAlive()){
			try{
				_timer.join();
			}
			catch(Exception e)
			{
				e.printStackTrace();
			}
		}
	}
}

