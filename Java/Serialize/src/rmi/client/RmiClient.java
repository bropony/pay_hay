package rmi.client;

import rmi.SerializeStream;
import rmi.RmiManager;
import rmi.RmiCallbackBase;
import java.util.Date;

public class RmiClient{
	private static int __msgIdBase = 0;

	private RmiClient(){}

	//Method definitions
		public static void test(TestCallback clientCB__, Date dt){
			SerializeStream __os = new SerializeStream();
			__os.startToWrite();

			__msgIdBase++;
			__os.write(__msgIdBase);
			__os.write(12);

			__os.write(dt);

			RmiManager.instance().invoke(clientCB__, __msgIdBase, __os);
		}

		public static void showError(ShowErrorCallback clientCB__, Date dt){
			SerializeStream __os = new SerializeStream();
			__os.startToWrite();

			__msgIdBase++;
			__os.write(__msgIdBase);
			__os.write(13);

			__os.write(dt);

			RmiManager.instance().invoke(clientCB__, __msgIdBase, __os);
		}

		public static void uploadImage(UploadImageCallback clientCB__, byte[] img){
			SerializeStream __os = new SerializeStream();
			__os.startToWrite();

			__msgIdBase++;
			__os.write(__msgIdBase);
			__os.write(14);

			__os.write(img);

			RmiManager.instance().invoke(clientCB__, __msgIdBase, __os);
		}

		public static void echo(EchoCallback clientCB__, STest input){
			SerializeStream __os = new SerializeStream();
			__os.startToWrite();

			__msgIdBase++;
			__os.write(__msgIdBase);
			__os.write(15);

			input.write(__os);

			RmiManager.instance().invoke(clientCB__, __msgIdBase, __os);
		}


	//Callback definitions
	public static abstract class TestCallback extends RmiCallbackBase {
		public TestCallback(){}

		public abstract void onResponse(Date testOut);
		public abstract void onError(String what, int code);
		public abstract void onTimeout();

		@Override
		public void __onResponse(SerializeStream __is){
			Date testOut = null;
			testOut = __is.read(testOut);

			onResponse(testOut);
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

	public static abstract class ShowErrorCallback extends RmiCallbackBase {
		public ShowErrorCallback(){}

		public abstract void onResponse(String out);
		public abstract void onError(String what, int code);
		public abstract void onTimeout();

		@Override
		public void __onResponse(SerializeStream __is){
			String out = null;
			out = __is.read(out);

			onResponse(out);
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

	public static abstract class UploadImageCallback extends RmiCallbackBase {
		public UploadImageCallback(){}

		public abstract void onResponse(String fileName);
		public abstract void onError(String what, int code);
		public abstract void onTimeout();

		@Override
		public void __onResponse(SerializeStream __is){
			String fileName = null;
			fileName = __is.read(fileName);

			onResponse(fileName);
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

	public static abstract class EchoCallback extends RmiCallbackBase {
		public EchoCallback(){}

		public abstract void onResponse(STest output);
		public abstract void onError(String what, int code);
		public abstract void onTimeout();

		@Override
		public void __onResponse(SerializeStream __is){
			STest output = new STest();
			output.read(__is);

			onResponse(output);
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
