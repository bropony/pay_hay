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

		public static void changeAvatar(ChangeAvatarCallback clientCB__, byte[] avatar){
			SerializeStream __os = new SerializeStream();
			__os.startToWrite();

			__msgIdBase++;
			__os.write(__msgIdBase);
			__os.write(3);

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

		public static void getMyPosts(GetMyPostsCallback clientCB__){
			SerializeStream __os = new SerializeStream();
			__os.startToWrite();

			__msgIdBase++;
			__os.write(__msgIdBase);
			__os.write(22);


			RmiManager.instance().invoke(clientCB__, __msgIdBase, __os);
		}

		public static void startPost(StartPostCallback clientCB__, String title, String content){
			SerializeStream __os = new SerializeStream();
			__os.startToWrite();

			__msgIdBase++;
			__os.write(__msgIdBase);
			__os.write(30);

			__os.write(title);
			__os.write(content);

			RmiManager.instance().invoke(clientCB__, __msgIdBase, __os);
		}

		public static void uploadPostImg(UploadPostImgCallback clientCB__, byte[] img){
			SerializeStream __os = new SerializeStream();
			__os.startToWrite();

			__msgIdBase++;
			__os.write(__msgIdBase);
			__os.write(31);

			__os.write(img);

			RmiManager.instance().invoke(clientCB__, __msgIdBase, __os);
		}

		public static void endPost(EndPostCallback clientCB__){
			SerializeStream __os = new SerializeStream();
			__os.startToWrite();

			__msgIdBase++;
			__os.write(__msgIdBase);
			__os.write(32);


			RmiManager.instance().invoke(clientCB__, __msgIdBase, __os);
		}

		public static void likePost(LikePostCallback clientCB__, int postId){
			SerializeStream __os = new SerializeStream();
			__os.startToWrite();

			__msgIdBase++;
			__os.write(__msgIdBase);
			__os.write(40);

			__os.write(postId);

			RmiManager.instance().invoke(clientCB__, __msgIdBase, __os);
		}

		public static void dislikePost(DislikePostCallback clientCB__, int postId){
			SerializeStream __os = new SerializeStream();
			__os.startToWrite();

			__msgIdBase++;
			__os.write(__msgIdBase);
			__os.write(41);

			__os.write(postId);

			RmiManager.instance().invoke(clientCB__, __msgIdBase, __os);
		}

		public static void commentPost(CommentPostCallback clientCB__, int postId, String comments){
			SerializeStream __os = new SerializeStream();
			__os.startToWrite();

			__msgIdBase++;
			__os.write(__msgIdBase);
			__os.write(42);

			__os.write(postId);
			__os.write(comments);

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

		public abstract void onResponse(byte[] img);
		public abstract void onError(String what, int code);
		public abstract void onTimeout();

		@Override
		public void __onResponse(SerializeStream __is){
			byte[] img = null;
			img = __is.read(img);

			onResponse(img);
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

}
