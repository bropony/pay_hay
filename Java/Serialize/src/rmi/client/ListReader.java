package rmi.client;

import rmi.SerializeStream;
import java.util.Date;

public class ListReader{
	private ListReader(){}

	public static SPost[] read(SerializeStream __is, SPost[] res){
		int size = __is.readInt();
		res = new SPost[size];

		for (int i = 0; i < size; ++i){
			SPost val = new SPost();
			val.read(__is);
			res[i] = val;
		}

		return res;
	}

	public static void write(SerializeStream __os, SPost[] v){
		int size = v.length;
		__os.write(size);

		for (int i = 0; i < size; i++){
			v[i].write(__os);
		}
	}

	public static SComment[] read(SerializeStream __is, SComment[] res){
		int size = __is.readInt();
		res = new SComment[size];

		for (int i = 0; i < size; ++i){
			SComment val = new SComment();
			val.read(__is);
			res[i] = val;
		}

		return res;
	}

	public static void write(SerializeStream __os, SComment[] v){
		int size = v.length;
		__os.write(size);

		for (int i = 0; i < size; i++){
			v[i].write(__os);
		}
	}

}

