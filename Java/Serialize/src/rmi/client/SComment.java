package rmi.client;

import rmi.SerializeStream;
import java.util.Date;

public class SComment{
	public int userId;
	public String nickname;
	public int avatarImgId;
	public String content;
	public Date commentDt;

	public SComment(){
		userId = 0;
		nickname = "";
		avatarImgId = 0;
		content = "";
		commentDt = new Date();
	}
	public void read(SerializeStream __is){
		userId = __is.read(userId);
		nickname = __is.read(nickname);
		avatarImgId = __is.read(avatarImgId);
		content = __is.read(content);
		commentDt = __is.read(commentDt);
	}
	public void write(SerializeStream __os){
		__os.write(userId);
		__os.write(nickname);
		__os.write(avatarImgId);
		__os.write(content);
		__os.write(commentDt);
	}
}

