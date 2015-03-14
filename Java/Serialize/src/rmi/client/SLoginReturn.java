package rmi.client;

import rmi.SerializeStream;
import java.util.Date;

public class SLoginReturn{
	public int userId;
	public String nickname;
	public byte[] avatar;
	public String sessionKey;

	public SLoginReturn(){
		userId = 0;
		nickname = 0;
		avatar = new byte[0];
		sessionKey = 0;
	}
	public void read(SerializeStream __is){
		userId = __is.read(userId);
		nickname = __is.read(nickname);
		avatar = __is.read(avatar);
		sessionKey = __is.read(sessionKey);
	}
	public void write(SerializeStream __os){
		__os.write(userId);
		__os.write(nickname);
		__os.write(avatar);
		__os.write(sessionKey);
	}
}

