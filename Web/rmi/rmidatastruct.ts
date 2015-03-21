/// <reference path="serialize.ts" />

module Rmi {
	//Read SeqInt
	export var readSeqInt = function (__is: SimpleSerializer): number[]{
		var size = __is.readInt();
		var res: number[] = [];
		for (var i = 0; i < size; i++) {
			var val: number = 0;
			val = __is.read(4);
			res.push(val);
		}
		return res;
	}

	//Write SeqInt
	export var writeSeqInt = function (__os: SimpleSerializer, data: number[]) {
		var size = data.length;
		__os.writeInt(size);
		for (var i = 0; i < size; i++) {
			__os.write(4, data[i]);
		}
	}


	//Read SeqString
	export var readSeqString = function (__is: SimpleSerializer): string[]{
		var size = __is.readInt();
		var res: string[] = [];
		for (var i = 0; i < size; i++) {
			var val: string = "";
			val = __is.read(8);
			res.push(val);
		}
		return res;
	}

	//Write SeqString
	export var writeSeqString = function (__os: SimpleSerializer, data: string[]) {
		var size = data.length;
		__os.writeInt(size);
		for (var i = 0; i < size; i++) {
			__os.write(8, data[i]);
		}
	}


	//Read SeqDate
	export var readSeqDate = function (__is: SimpleSerializer): Date[]{
		var size = __is.readInt();
		var res: Date[] = [];
		for (var i = 0; i < size; i++) {
			var val: Date = new Date();
			val = __is.read(9);
			res.push(val);
		}
		return res;
	}

	//Write SeqDate
	export var writeSeqDate = function (__os: SimpleSerializer, data: Date[]) {
		var size = data.length;
		__os.writeInt(size);
		for (var i = 0; i < size; i++) {
			__os.write(9, data[i]);
		}
	}


	//Read SeqBool
	export var readSeqBool = function (__is: SimpleSerializer): boolean[]{
		var size = __is.readInt();
		var res: boolean[] = [];
		for (var i = 0; i < size; i++) {
			var val: boolean = false;
			val = __is.read(2);
			res.push(val);
		}
		return res;
	}

	//Write SeqBool
	export var writeSeqBool = function (__os: SimpleSerializer, data: boolean[]) {
		var size = data.length;
		__os.writeInt(size);
		for (var i = 0; i < size; i++) {
			__os.write(2, data[i]);
		}
	}


	//Read SeqByte
	export var readSeqByte = function (__is: SimpleSerializer): number[]{
		var size = __is.readInt();
		var res: number[] = [];
		for (var i = 0; i < size; i++) {
			var val: number = 0;
			val = __is.read(1);
			res.push(val);
		}
		return res;
	}

	//Write SeqByte
	export var writeSeqByte = function (__os: SimpleSerializer, data: number[]) {
		var size = data.length;
		__os.writeInt(size);
		for (var i = 0; i < size; i++) {
			__os.write(1, data[i]);
		}
	}


	//Read SeqShort
	export var readSeqShort = function (__is: SimpleSerializer): number[]{
		var size = __is.readInt();
		var res: number[] = [];
		for (var i = 0; i < size; i++) {
			var val: number = 0;
			val = __is.read(3);
			res.push(val);
		}
		return res;
	}

	//Write SeqShort
	export var writeSeqShort = function (__os: SimpleSerializer, data: number[]) {
		var size = data.length;
		__os.writeInt(size);
		for (var i = 0; i < size; i++) {
			__os.write(3, data[i]);
		}
	}


	//Read SeqDouble
	export var readSeqDouble = function (__is: SimpleSerializer): number[]{
		var size = __is.readInt();
		var res: number[] = [];
		for (var i = 0; i < size; i++) {
			var val: number = 0;
			val = __is.read(7);
			res.push(val);
		}
		return res;
	}

	//Write SeqDouble
	export var writeSeqDouble = function (__os: SimpleSerializer, data: number[]) {
		var size = data.length;
		__os.writeInt(size);
		for (var i = 0; i < size; i++) {
			__os.write(7, data[i]);
		}
	}


	//Read SeqLong
	export var readSeqLong = function (__is: SimpleSerializer): number[]{
		var size = __is.readInt();
		var res: number[] = [];
		for (var i = 0; i < size; i++) {
			var val: number = 0;
			val = __is.read(5);
			res.push(val);
		}
		return res;
	}

	//Write SeqLong
	export var writeSeqLong = function (__os: SimpleSerializer, data: number[]) {
		var size = data.length;
		__os.writeInt(size);
		for (var i = 0; i < size; i++) {
			__os.write(5, data[i]);
		}
	}


	//Read SeqImage
	export var readSeqImage = function (__is: SimpleSerializer): ArrayBuffer[]{
		var size = __is.readInt();
		var res: ArrayBuffer[] = [];
		for (var i = 0; i < size; i++) {
			var val: ArrayBuffer = new ArrayBuffer(0);
			val = __is.read(10);
			res.push(val);
		}
		return res;
	}

	//Write SeqImage
	export var writeSeqImage = function (__os: SimpleSerializer, data: ArrayBuffer[]) {
		var size = data.length;
		__os.writeInt(size);
		for (var i = 0; i < size; i++) {
			__os.write(10, data[i]);
		}
	}


	export class SLoginReturn{
		userId: number;
		nickname: string;
		avatar: ArrayBuffer;
		sessionKey: string;

		constructor() {
			this.userId = 0;
			this.nickname = "";
			this.avatar = new ArrayBuffer(0);
			this.sessionKey = "";
		}

		__read(__is: SimpleSerializer) {
			this.userId = __is.read(4);
			this.nickname = __is.read(8);
			this.avatar = __is.read(10);
			this.sessionKey = __is.read(8);
		}

		__write(__os: SimpleSerializer) {
			__os.write(4, this.userId);
			__os.write(8, this.nickname);
			__os.write(10, this.avatar);
			__os.write(8, this.sessionKey);
		}

	} // end of SLoginReturn


	export class SPost{
		postId: number;
		title: string;
		content: string;
		authorUserId: number;
		authorAccount: string;
		authorNickname: string;
		imgIdList: number[];
		postDt: Date;
		likes: number;
		dislikes: number;
		comments: number;

		constructor() {
			this.postId = 0;
			this.title = "";
			this.content = "";
			this.authorUserId = 0;
			this.authorAccount = "";
			this.authorNickname = "";
			this.imgIdList = [];
			this.postDt = new Date();
			this.likes = 0;
			this.dislikes = 0;
			this.comments = 0;
		}

		__read(__is: SimpleSerializer) {
			this.postId = __is.read(4);
			this.title = __is.read(8);
			this.content = __is.read(8);
			this.authorUserId = __is.read(4);
			this.authorAccount = __is.read(8);
			this.authorNickname = __is.read(8);
			this.imgIdList = readSeqInt(__is);
			this.postDt = __is.read(9);
			this.likes = __is.read(4);
			this.dislikes = __is.read(4);
			this.comments = __is.read(4);
		}

		__write(__os: SimpleSerializer) {
			__os.write(4, this.postId);
			__os.write(8, this.title);
			__os.write(8, this.content);
			__os.write(4, this.authorUserId);
			__os.write(8, this.authorAccount);
			__os.write(8, this.authorNickname);
			writeSeqInt(__os, this.imgIdList);
			__os.write(9, this.postDt);
			__os.write(4, this.likes);
			__os.write(4, this.dislikes);
			__os.write(4, this.comments);
		}

	} // end of SPost


	//Read SeqPost
	export var readSeqPost = function (__is: SimpleSerializer): SPost[]{
		var size = __is.readInt();
		var res: SPost[] = [];
		for (var i = 0; i < size; i++) {
			var val: SPost = new SPost();
			val.__read(__is);
			res.push(val);
		}
		return res;
	}

	//Write SeqPost
	export var writeSeqPost = function (__os: SimpleSerializer, data: SPost[]) {
		var size = data.length;
		__os.writeInt(size);
		for (var i = 0; i < size; i++) {
			data[i].__write(__os);
		}
	}


	export class SComment{
		userId: number;
		nickname: string;
		content: string;
		commentDt: Date;

		constructor() {
			this.userId = 0;
			this.nickname = "";
			this.content = "";
			this.commentDt = new Date();
		}

		__read(__is: SimpleSerializer) {
			this.userId = __is.read(4);
			this.nickname = __is.read(8);
			this.content = __is.read(8);
			this.commentDt = __is.read(9);
		}

		__write(__os: SimpleSerializer) {
			__os.write(4, this.userId);
			__os.write(8, this.nickname);
			__os.write(8, this.content);
			__os.write(9, this.commentDt);
		}

	} // end of SComment


	//Read SeqComment
	export var readSeqComment = function (__is: SimpleSerializer): SComment[]{
		var size = __is.readInt();
		var res: SComment[] = [];
		for (var i = 0; i < size; i++) {
			var val: SComment = new SComment();
			val.__read(__is);
			res.push(val);
		}
		return res;
	}

	//Write SeqComment
	export var writeSeqComment = function (__os: SimpleSerializer, data: SComment[]) {
		var size = data.length;
		__os.writeInt(size);
		for (var i = 0; i < size; i++) {
			data[i].__write(__os);
		}
	}


} //end of module Rmi
