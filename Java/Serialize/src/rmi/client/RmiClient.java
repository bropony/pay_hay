package rmi.client;

import rmi.SerializeStream;
import rmi.RmiManager;
import rmi.RmiCallbackBase;
import java.util.Date;

public class RmiClient{
	private static int __msgIdBase = 0;

	private RmiClient(){}

	//Method definitions
		public static void login(LoginCallback clientCB__, String account, String passwd){
			SerializeStream __os = new SerializeStream();
			__os.startToWrite();

			__msgIdBase++;
			__os.write(__msgIdBase);
			__os.write(1);

			__os.write(account);
			__os.write(passwd);

			RmiManager.instance().invoke(clientCB__, __msgIdBase, __os);
		}

		public static void signup(SignupCallback clientCB__, String account, String passwd, String nickname){
			SerializeStream __os = new SerializeStream();
			__os.startToWrite();

			__msgIdBase++;
			__os.write(__msgIdBase);
			__os.write(2);

			__os.write(account);
			__os.write(passwd);
			__os.write(nickname);

			RmiManager.instance().invoke(clientCB__, __msgIdBase, __os);
		}

		public static void changeAvatar(ChangeAvatarCallback clientCB__, String sessionKey, byte[] avatar){
			SerializeStream __os = new SerializeStream();
			__os.startToWrite();

			__msgIdBase++;
			__os.write(__msgIdBase);
			__os.write(3);

			__os.write(sessionKey);
			__os.write(avatar);

			RmiManager.instance().invoke(clientCB__, __msgIdBase, __os);
		}

		public static void getPosts(GetPostsCallback clientCB__, int lastPostId, boolean forNew, int requestNum){
			SerializeStream __os = new SerializeStream();
			__os.startToWrite();

			__msgIdBase++;
			__os.write(__msgIdBase);
			__os.write(20);

			__os.write(lastPostId);
			__os.write(forNew);
			__os.write(requestNum);

			RmiManager.instance().invoke(clientCB__, __msgIdBase, __os);
		}

		public static void getImage(GetImageCallback clientCB__, int imgId){
			SerializeStream __os = new SerializeStream();
			__os.startToWrite();

			__msgIdBase++;
			__os.write(__msgIdBase);
			__os.write(21);

			__os.write(imgId);

			RmiManager.instance().invoke(clientCB__, __msgIdBase, __os);
		}

		public static void getMyPosts(GetMyPostsCallback clientCB__, String sessionKey, int lastPostId, boolean forNew){
			SerializeStream __os = new SerializeStream();
			__os.startToWrite();

			__msgIdBase++;
			__os.write(__msgIdBase);
			__os.write(22);

			__os.write(sessionKey);
			__os.write(lastPostId);
			__os.write(forNew);

			RmiManager.instance().invoke(clientCB__, __msgIdBase, __os);
		}

		public static void startPost(StartPostCallback clientCB__, String sessionKey, String title, String content){
			SerializeStream __os = new SerializeStream();
			__os.startToWrite();

			__msgIdBase++;
			__os.write(__msgIdBase);
			__os.write(30);

			__os.write(sessionKey);
			__os.write(title);
			__os.write(content);

			RmiManager.instance().invoke(clientCB__, __msgIdBase, __os);
		}

		public static void uploadPostImg(UploadPostImgCallback clientCB__, String sessionKey, byte[] img, String descrpt){
			SerializeStream __os = new SerializeStream();
			__os.startToWrite();

			__msgIdBase++;
			__os.write(__msgIdBase);
			__os.write(31);

			__os.write(sessionKey);
			__os.write(img);
			__os.write(descrpt);

			RmiManager.instance().invoke(clientCB__, __msgIdBase, __os);
		}

		public static void endPost(EndPostCallback clientCB__, String sessionKey){
			SerializeStream __os = new SerializeStream();
			__os.startToWrite();

			__msgIdBase++;
			__os.write(__msgIdBase);
			__os.write(32);

			__os.write(sessionKey);

			RmiManager.instance().invoke(clientCB__, __msgIdBase, __os);
		}

		public static void likePost(LikePostCallback clientCB__, String sessionKey, int postId){
			SerializeStream __os = new SerializeStream();
			__os.startToWrite();

			__msgIdBase++;
			__os.write(__msgIdBase);
			__os.write(40);

			__os.write(sessionKey);
			__os.write(postId);

			RmiManager.instance().invoke(clientCB__, __msgIdBase, __os);
		}

		public static void dislikePost(DislikePostCallback clientCB__, String sessionKey, int postId){
			SerializeStream __os = new SerializeStream();
			__os.startToWrite();

			__msgIdBase++;
			__os.write(__msgIdBase);
			__os.write(41);

			__os.write(sessionKey);
			__os.write(postId);

			RmiManager.instance().invoke(clientCB__, __msgIdBase, __os);
		}

		public static void commentPost(CommentPostCallback clientCB__, String sessionKey, int postId, String comments){
			SerializeStream __os = new SerializeStream();
			__os.startToWrite();

			__msgIdBase++;
			__os.write(__msgIdBase);
			__os.write(42);

			__os.write(sessionKey);
			__os.write(postId);
			__os.write(comments);

			RmiManager.instance().invoke(clientCB__, __msgIdBase, __os);
		}

		public static void getComments(GetCommentsCallback clientCB__, String sessionKey, int postId){
			SerializeStream __os = new SerializeStream();
			__os.startToWrite();

			__msgIdBase++;
			__os.write(__msgIdBase);
			__os.write(43);

			__os.write(sessionKey);
			__os.write(postId);

			RmiManager.instance().invoke(clientCB__, __msgIdBase, __os);
		}

		public static void startPostEx(StartPostExCallback clientCB__, String sessionKey, String title, String content, int imgNum){
			SerializeStream __os = new SerializeStream();
			__os.startToWrite();

			__msgIdBase++;
			__os.write(__msgIdBase);
			__os.write(44);

			__os.write(sessionKey);
			__os.write(title);
			__os.write(content);
			__os.write(imgNum);

			RmiManager.instance().invoke(clientCB__, __msgIdBase, __os);
		}

		public static void uploadPostImgEx(UploadPostImgExCallback clientCB__, String sessionKey, byte[] img, String descrpt, int postId, int index){
			SerializeStream __os = new SerializeStream();
			__os.startToWrite();

			__msgIdBase++;
			__os.write(__msgIdBase);
			__os.write(45);

			__os.write(sessionKey);
			__os.write(img);
			__os.write(descrpt);
			__os.write(postId);
			__os.write(index);

			RmiManager.instance().invoke(clientCB__, __msgIdBase, __os);
		}

		public static void isSessionKeyValid(IsSessionKeyValidCallback clientCB__, String sessionKey){
			SerializeStream __os = new SerializeStream();
			__os.startToWrite();

			__msgIdBase++;
			__os.write(__msgIdBase);
			__os.write(50);

			__os.write(sessionKey);

			RmiManager.instance().invoke(clientCB__, __msgIdBase, __os);
		}


	//Callback definitions
	public static abstract class LoginCallback extends RmiCallbackBase {
		public LoginCallback(){}

		public abstract void onResponse(SLoginReturn userInfo);
		public abstract void onError(String what, int code);
		public abstract void onTimeout();

		@Override
		public void __onResponse(SerializeStream __is){
			SLoginReturn userInfo = new SLoginReturn();
			userInfo.read(__is);

			onResponse(userInfo);
		}

		@Override
		public void __onError(String what, int code){
			onError(what, code);
		}

		@Override
		public void __onTimeout(){
			onTimeout();
		}

	}

	public static abstract class SignupCallback extends RmiCallbackBase {
		public SignupCallback(){}

		public abstract void onResponse(SLoginReturn userInfo);
		public abstract void onError(String what, int code);
		public abstract void onTimeout();

		@Override
		public void __onResponse(SerializeStream __is){
			SLoginReturn userInfo = new SLoginReturn();
			userInfo.read(__is);

			onResponse(userInfo);
		}

		@Override
		public void __onError(String what, int code){
			onError(what, code);
		}

		@Override
		public void __onTimeout(){
			onTimeout();
		}

	}

	public static abstract class ChangeAvatarCallback extends RmiCallbackBase {
		public ChangeAvatarCallback(){}

		public abstract void onResponse(int avatarImgId);
		public abstract void onError(String what, int code);
		public abstract void onTimeout();

		@Override
		public void __onResponse(SerializeStream __is){
			int avatarImgId = 0;
			avatarImgId = __is.read(avatarImgId);

			onResponse(avatarImgId);
		}

		@Override
		public void __onError(String what, int code){
			onError(what, code);
		}

		@Override
		public void __onTimeout(){
			onTimeout();
		}

	}

	public static abstract class GetPostsCallback extends RmiCallbackBase {
		public GetPostsCallback(){}

		public abstract void onResponse(SPost[] postList);
		public abstract void onError(String what, int code);
		public abstract void onTimeout();

		@Override
		public void __onResponse(SerializeStream __is){
			SPost[] postList = null;
			postList = ListReader.read(__is, postList);

			onResponse(postList);
		}

		@Override
		public void __onError(String what, int code){
			onError(what, code);
		}

		@Override
		public void __onTimeout(){
			onTimeout();
		}

	}

	public static abstract class GetImageCallback extends RmiCallbackBase {
		public GetImageCallback(){}

		public abstract void onResponse(byte[] img, String shortDesc);
		public abstract void onError(String what, int code);
		public abstract void onTimeout();

		@Override
		public void __onResponse(SerializeStream __is){
			byte[] img = null;
			img = __is.read(img);

			String shortDesc = null;
			shortDesc = __is.read(shortDesc);

			onResponse(img, shortDesc);
		}

		@Override
		public void __onError(String what, int code){
			onError(what, code);
		}

		@Override
		public void __onTimeout(){
			onTimeout();
		}

	}

	public static abstract class GetMyPostsCallback extends RmiCallbackBase {
		public GetMyPostsCallback(){}

		public abstract void onResponse(SPost[] postList);
		public abstract void onError(String what, int code);
		public abstract void onTimeout();

		@Override
		public void __onResponse(SerializeStream __is){
			SPost[] postList = null;
			postList = ListReader.read(__is, postList);

			onResponse(postList);
		}

		@Override
		public void __onError(String what, int code){
			onError(what, code);
		}

		@Override
		public void __onTimeout(){
			onTimeout();
		}

	}

	public static abstract class StartPostCallback extends RmiCallbackBase {
		public StartPostCallback(){}

		public abstract void onResponse();
		public abstract void onError(String what, int code);
		public abstract void onTimeout();

		@Override
		public void __onResponse(SerializeStream __is){
			onResponse();
		}

		@Override
		public void __onError(String what, int code){
			onError(what, code);
		}

		@Override
		public void __onTimeout(){
			onTimeout();
		}

	}

	public static abstract class UploadPostImgCallback extends RmiCallbackBase {
		public UploadPostImgCallback(){}

		public abstract void onResponse(int imgId);
		public abstract void onError(String what, int code);
		public abstract void onTimeout();

		@Override
		public void __onResponse(SerializeStream __is){
			int imgId = 0;
			imgId = __is.read(imgId);

			onResponse(imgId);
		}

		@Override
		public void __onError(String what, int code){
			onError(what, code);
		}

		@Override
		public void __onTimeout(){
			onTimeout();
		}

	}

	public static abstract class EndPostCallback extends RmiCallbackBase {
		public EndPostCallback(){}

		public abstract void onResponse(int postId);
		public abstract void onError(String what, int code);
		public abstract void onTimeout();

		@Override
		public void __onResponse(SerializeStream __is){
			int postId = 0;
			postId = __is.read(postId);

			onResponse(postId);
		}

		@Override
		public void __onError(String what, int code){
			onError(what, code);
		}

		@Override
		public void __onTimeout(){
			onTimeout();
		}

	}

	public static abstract class LikePostCallback extends RmiCallbackBase {
		public LikePostCallback(){}

		public abstract void onResponse();
		public abstract void onError(String what, int code);
		public abstract void onTimeout();

		@Override
		public void __onResponse(SerializeStream __is){
			onResponse();
		}

		@Override
		public void __onError(String what, int code){
			onError(what, code);
		}

		@Override
		public void __onTimeout(){
			onTimeout();
		}

	}

	public static abstract class DislikePostCallback extends RmiCallbackBase {
		public DislikePostCallback(){}

		public abstract void onResponse();
		public abstract void onError(String what, int code);
		public abstract void onTimeout();

		@Override
		public void __onResponse(SerializeStream __is){
			onResponse();
		}

		@Override
		public void __onError(String what, int code){
			onError(what, code);
		}

		@Override
		public void __onTimeout(){
			onTimeout();
		}

	}

	public static abstract class CommentPostCallback extends RmiCallbackBase {
		public CommentPostCallback(){}

		public abstract void onResponse();
		public abstract void onError(String what, int code);
		public abstract void onTimeout();

		@Override
		public void __onResponse(SerializeStream __is){
			onResponse();
		}

		@Override
		public void __onError(String what, int code){
			onError(what, code);
		}

		@Override
		public void __onTimeout(){
			onTimeout();
		}

	}

	public static abstract class GetCommentsCallback extends RmiCallbackBase {
		public GetCommentsCallback(){}

		public abstract void onResponse(SComment[] comments);
		public abstract void onError(String what, int code);
		public abstract void onTimeout();

		@Override
		public void __onResponse(SerializeStream __is){
			SComment[] comments = null;
			comments = ListReader.read(__is, comments);

			onResponse(comments);
		}

		@Override
		public void __onError(String what, int code){
			onError(what, code);
		}

		@Override
		public void __onTimeout(){
			onTimeout();
		}

	}

	public static abstract class StartPostExCallback extends RmiCallbackBase {
		public StartPostExCallback(){}

		public abstract void onResponse(int postId);
		public abstract void onError(String what, int code);
		public abstract void onTimeout();

		@Override
		public void __onResponse(SerializeStream __is){
			int postId = 0;
			postId = __is.read(postId);

			onResponse(postId);
		}

		@Override
		public void __onError(String what, int code){
			onError(what, code);
		}

		@Override
		public void __onTimeout(){
			onTimeout();
		}

	}

	public static abstract class UploadPostImgExCallback extends RmiCallbackBase {
		public UploadPostImgExCallback(){}

		public abstract void onResponse(int imgId);
		public abstract void onError(String what, int code);
		public abstract void onTimeout();

		@Override
		public void __onResponse(SerializeStream __is){
			int imgId = 0;
			imgId = __is.read(imgId);

			onResponse(imgId);
		}

		@Override
		public void __onError(String what, int code){
			onError(what, code);
		}

		@Override
		public void __onTimeout(){
			onTimeout();
		}

	}

	public static abstract class IsSessionKeyValidCallback extends RmiCallbackBase {
		public IsSessionKeyValidCallback(){}

		public abstract void onResponse(boolean res);
		public abstract void onError(String what, int code);
		public abstract void onTimeout();

		@Override
		public void __onResponse(SerializeStream __is){
			boolean res = false;
			res = __is.read(res);

			onResponse(res);
		}

		@Override
		public void __onError(String what, int code){
			onError(what, code);
		}

		@Override
		public void __onTimeout(){
			onTimeout();
		}

	}

}
