import rmi.client.RmiClient;
import rmi.client.STest;
import rmi.SerializeStream;
//import rmi.SOhGood;
import rmi.RmiManager;

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
			serverURI = new URI("ws://192.168.3.24:9600");
		}
		catch(Exception e)
		{
			e.printStackTrace();
			return;
		}
		
		RmiManager.initInstance(serverURI);
		RmiManager.instance().connect();
		
		RmiClient.UploadImageCallback upCb = new RmiClient.UploadImageCallback() {
			
			@Override
			public void onTimeout() {
				System.out.println("timeout");
				
			}
			
			@Override
			public void onResponse(String fileName) {
				System.out.println("Response: " + fileName);
				
			}
			
			@Override
			public void onError(String what, int code) {
				System.out.println("What: " + what);
				
			}
		};
		
		Path path = Paths.get("D:\\Cocos2dx\\cocos2d-js-v3.2\\samples\\js-tests\\res\\CloseNormal.png");
		
		try{
			byte[] bb = Files.readAllBytes(path);
			
			for (int i = 0; i < 4; i++){
				System.out.print(Integer.toHexString(bb[i]) + " ");
			}
			System.out.println();
			RmiClient.uploadImage(upCb, bb);
		}catch(Exception e){
			e.printStackTrace();
		}
		
		path = Paths.get("F:\\doc\\年会照片\\况壁群\\DCIM\\100CANON\\_MG_3009.JPG");
		try{
			byte[] bb = Files.readAllBytes(path);
			for (int i = 0; i < 4; i++){
				System.out.print(Integer.toHexString(bb[i]) + " ");
			}
			System.out.println();
			RmiClient.uploadImage(upCb, bb);
		}catch(Exception e){
			e.printStackTrace();
		}
		
		RmiManager.instance().join();
	}
}
