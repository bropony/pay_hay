package rmi.client;

import rmi.SerializeStream;
import java.util.Date;

public class ListReader{
	private ListReader(){}

	public static int[][] read(SerializeStream __is, int[][] res){
		int size = __is.readInt();
		res = new int[size][];

		for (int i = 0; i < size; ++i){
			int[] val = null;
			val = __is.read(val);
			res[i] = val;
		}

		return res;
	}

	public static void write(SerializeStream __os, int[][] v){
		int size = v.length;
		__os.write(size);

		for (int i = 0; i < size; i++){
			__os.write(v[i]);
		}
	}

}

