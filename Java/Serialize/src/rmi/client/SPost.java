package rmi.client;

import rmi.SerializeStream;
import java.util.Date;

public class SPost{
	public int postId;
	public String title;
	public String content;
	public int authorUserId;
	public String authorAccount;
	public String authorNickname;
	public int[] imgIdList;
	public Date postDt;
	public int likes;
	public int dislikes;
	public int comments;

	public SPost(){
		postId = 0;
		title = "";
		content = "";
		authorUserId = 0;
		authorAccount = "";
		authorNickname = "";
		imgIdList = new int[0];
		postDt = new Date();
		likes = 0;
		dislikes = 0;
		comments = 0;
	}
	public void read(SerializeStream __is){
		postId = __is.read(postId);
		title = __is.read(title);
		content = __is.read(content);
		authorUserId = __is.read(authorUserId);
		authorAccount = __is.read(authorAccount);
		authorNickname = __is.read(authorNickname);
		imgIdList = __is.read(imgIdList);
		postDt = __is.read(postDt);
		likes = __is.read(likes);
		dislikes = __is.read(dislikes);
		comments = __is.read(comments);
	}
	public void write(SerializeStream __os){
		__os.write(postId);
		__os.write(title);
		__os.write(content);
		__os.write(authorUserId);
		__os.write(authorAccount);
		__os.write(authorNickname);
		__os.write(imgIdList);
		__os.write(postDt);
		__os.write(likes);
		__os.write(dislikes);
		__os.write(comments);
	}
}

