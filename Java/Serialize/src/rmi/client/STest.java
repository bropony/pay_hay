package rmi.client;

import rmi.SerializeStream;
import java.util.Date;

public class STest{
	public short[] s;
	public long[] l;
	public int[] i;
	public boolean[] b;
	public String[] ss;

	public STest(){
		s = new short[0];
		l = new long[0];
		i = new int[0];
		b = new boolean[0];
		ss = new String[0];
	}
	public void read(SerializeStream __is){
		s = __is.read(s);
		l = __is.read(l);
		i = __is.read(i);
		b = __is.read(b);
		ss = __is.read(ss);
	}
	public void write(SerializeStream __os){
		__os.write(s);
		__os.write(l);
		__os.write(i);
		__os.write(b);
		__os.write(ss);
	}
}

