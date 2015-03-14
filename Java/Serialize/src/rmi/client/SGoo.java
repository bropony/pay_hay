package rmi.client;

import rmi.SerializeStream;
import java.util.Date;

public class SGoo{
	public STest st;
	public int[][] ilist;

	public SGoo(){
		st = new STest();
		ilist = new int[0][];
	}
	public void read(SerializeStream __is){
		st.read(__is);
		ilist = ListReader.read(__is, ilist);
	}
	public void write(SerializeStream __os){
		st.write(__os);
		ListReader.write(__os, ilist);
	}
}

