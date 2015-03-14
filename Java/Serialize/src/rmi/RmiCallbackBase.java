package rmi;

import java.util.Date;

public abstract class RmiCallbackBase {
	private Date __createDt;
	public RmiCallbackBase(){
		__createDt = new Date();
	}
	
	public boolean isTimeout(long timeout){
		Date now = new Date();
		
		if ((now.getTime() - __createDt.getTime()) > timeout){
			return true;
		}
		
		return false;
	}
	
	public abstract void __onResponse(SerializeStream __is);
	public abstract void __onTimeout();
	public abstract void __onError(String what, int code);
}
