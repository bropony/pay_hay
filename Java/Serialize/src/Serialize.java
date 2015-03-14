import rmi.client.RmiClient;
import rmi.client.SLoginReturn;
import rmi.SerializeStream;
import rmi.RmiManager;
import rmi.Logger;

import java.util.Date;
import java.net.URI;
import java.nio.ByteBuffer;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.Path;

public class Serialize {	
	static public void main(String[] args){
		
		URI serverURI = null;
		try{
			serverURI = new URI("ws://112.74.102.141:9600");
		}
		catch(Exception e)
		{
			e.printStackTrace();
			return;
		}
		
		RmiManager.initInstance(serverURI);
		RmiManager.instance().connect();
		
		RmiClient.SignupCallback signupCB = new RmiClient.SignupCallback() {
			
			@Override
			public void onTimeout() {
				Logger.log("Signup", "Timeout");
				
			}
			
			@Override
			public void onResponse(SLoginReturn userInfo) {
				Logger.log("Signup Response", "UserId: " + userInfo.userId, "SessionKey: " + userInfo.sessionKey);
				
			}
			
			@Override
			public void onError(String what, int code) {
				Logger.log("signup error", "what: " + what, "code: " + code);
				
			}
		};
		
		String account = "test1";
		RmiClient.signup(signupCB, account, account, account);
		
		RmiManager.instance().join();
	}
}
