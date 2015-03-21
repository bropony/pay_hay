/// <reference path="serialize.ts" />
/// <reference path="rmidatastruct.ts" />
/// <reference path="rmimanager.ts" />

module Rmi {
//Callbacks
	//LoginCallback
	export class LoginCallback implements CallbackBase {
		onResponse: (userInfo: SLoginReturn) => void;
		onError: (what: string, code: number) => void;
		onTimeout: () => void;

		__onResponse(__is: SimpleSerializer) : void {
			var userInfo: SLoginReturn = new SLoginReturn();
			userInfo.__read(__is);
			this.onResponse(userInfo);
		}

		__onError(what: string, code: number) : void {
			this.onError(what, code);
		}

		__onTimeout() : void {
			this.onTimeout();
		}
	} // end of LoginCallback


	//SignupCallback
	export class SignupCallback implements CallbackBase {
		onResponse: (userInfo: SLoginReturn) => void;
		onError: (what: string, code: number) => void;
		onTimeout: () => void;

		__onResponse(__is: SimpleSerializer) : void {
			var userInfo: SLoginReturn = new SLoginReturn();
			userInfo.__read(__is);
			this.onResponse(userInfo);
		}

		__onError(what: string, code: number) : void {
			this.onError(what, code);
		}

		__onTimeout() : void {
			this.onTimeout();
		}
	} // end of SignupCallback


	//ChangeAvatarCallback
	export class ChangeAvatarCallback implements CallbackBase {
		onResponse: () => void;
		onError: (what: string, code: number) => void;
		onTimeout: () => void;

		__onResponse(__is: SimpleSerializer) : void {
			this.onResponse();
		}

		__onError(what: string, code: number) : void {
			this.onError(what, code);
		}

		__onTimeout() : void {
			this.onTimeout();
		}
	} // end of ChangeAvatarCallback


	//GetPostsCallback
	export class GetPostsCallback implements CallbackBase {
		onResponse: (postList: SPost[]) => void;
		onError: (what: string, code: number) => void;
		onTimeout: () => void;

		__onResponse(__is: SimpleSerializer) : void {
			var postList: SPost[] = [];
			postList = readSeqPost(__is);
			this.onResponse(postList);
		}

		__onError(what: string, code: number) : void {
			this.onError(what, code);
		}

		__onTimeout() : void {
			this.onTimeout();
		}
	} // end of GetPostsCallback


	//GetImageCallback
	export class GetImageCallback implements CallbackBase {
		onResponse: (img: ArrayBuffer, shortDesc: string) => void;
		onError: (what: string, code: number) => void;
		onTimeout: () => void;

		__onResponse(__is: SimpleSerializer) : void {
			var img: ArrayBuffer = new ArrayBuffer(0);
			img = __is.read(10);
			var shortDesc: string = "";
			shortDesc = __is.read(8);
			this.onResponse(img, shortDesc);
		}

		__onError(what: string, code: number) : void {
			this.onError(what, code);
		}

		__onTimeout() : void {
			this.onTimeout();
		}
	} // end of GetImageCallback


	//GetMyPostsCallback
	export class GetMyPostsCallback implements CallbackBase {
		onResponse: (postList: SPost[]) => void;
		onError: (what: string, code: number) => void;
		onTimeout: () => void;

		__onResponse(__is: SimpleSerializer) : void {
			var postList: SPost[] = [];
			postList = readSeqPost(__is);
			this.onResponse(postList);
		}

		__onError(what: string, code: number) : void {
			this.onError(what, code);
		}

		__onTimeout() : void {
			this.onTimeout();
		}
	} // end of GetMyPostsCallback


	//StartPostCallback
	export class StartPostCallback implements CallbackBase {
		onResponse: () => void;
		onError: (what: string, code: number) => void;
		onTimeout: () => void;

		__onResponse(__is: SimpleSerializer) : void {
			this.onResponse();
		}

		__onError(what: string, code: number) : void {
			this.onError(what, code);
		}

		__onTimeout() : void {
			this.onTimeout();
		}
	} // end of StartPostCallback


	//UploadPostImgCallback
	export class UploadPostImgCallback implements CallbackBase {
		onResponse: (imgId: number) => void;
		onError: (what: string, code: number) => void;
		onTimeout: () => void;

		__onResponse(__is: SimpleSerializer) : void {
			var imgId: number = 0;
			imgId = __is.read(4);
			this.onResponse(imgId);
		}

		__onError(what: string, code: number) : void {
			this.onError(what, code);
		}

		__onTimeout() : void {
			this.onTimeout();
		}
	} // end of UploadPostImgCallback


	//EndPostCallback
	export class EndPostCallback implements CallbackBase {
		onResponse: (postId: number) => void;
		onError: (what: string, code: number) => void;
		onTimeout: () => void;

		__onResponse(__is: SimpleSerializer) : void {
			var postId: number = 0;
			postId = __is.read(4);
			this.onResponse(postId);
		}

		__onError(what: string, code: number) : void {
			this.onError(what, code);
		}

		__onTimeout() : void {
			this.onTimeout();
		}
	} // end of EndPostCallback


	//LikePostCallback
	export class LikePostCallback implements CallbackBase {
		onResponse: () => void;
		onError: (what: string, code: number) => void;
		onTimeout: () => void;

		__onResponse(__is: SimpleSerializer) : void {
			this.onResponse();
		}

		__onError(what: string, code: number) : void {
			this.onError(what, code);
		}

		__onTimeout() : void {
			this.onTimeout();
		}
	} // end of LikePostCallback


	//DislikePostCallback
	export class DislikePostCallback implements CallbackBase {
		onResponse: () => void;
		onError: (what: string, code: number) => void;
		onTimeout: () => void;

		__onResponse(__is: SimpleSerializer) : void {
			this.onResponse();
		}

		__onError(what: string, code: number) : void {
			this.onError(what, code);
		}

		__onTimeout() : void {
			this.onTimeout();
		}
	} // end of DislikePostCallback


	//CommentPostCallback
	export class CommentPostCallback implements CallbackBase {
		onResponse: () => void;
		onError: (what: string, code: number) => void;
		onTimeout: () => void;

		__onResponse(__is: SimpleSerializer) : void {
			this.onResponse();
		}

		__onError(what: string, code: number) : void {
			this.onError(what, code);
		}

		__onTimeout() : void {
			this.onTimeout();
		}
	} // end of CommentPostCallback


	//GetCommentsCallback
	export class GetCommentsCallback implements CallbackBase {
		onResponse: (comments: SComment[]) => void;
		onError: (what: string, code: number) => void;
		onTimeout: () => void;

		__onResponse(__is: SimpleSerializer) : void {
			var comments: SComment[] = [];
			comments = readSeqComment(__is);
			this.onResponse(comments);
		}

		__onError(what: string, code: number) : void {
			this.onError(what, code);
		}

		__onTimeout() : void {
			this.onTimeout();
		}
	} // end of GetCommentsCallback



	//Client Rmi Proxy
	export class Proxy {
		static __msgIdBase: number = 0;

		static login(__cb: LoginCallback, account: string, passwd: string) : void {
			var __os: SimpleSerializer = new SimpleSerializer();
			__os.startToWrite();
			Proxy.__msgIdBase += 1;
			__os.writeInt(Proxy.__msgIdBase);
			__os.writeInt(1);

			__os.write(8, account);
			__os.write(8, passwd);

			RmiManager.invoke(Proxy.__msgIdBase, __os, __cb);
		}

		static signup(__cb: SignupCallback, account: string, passwd: string, nickname: string) : void {
			var __os: SimpleSerializer = new SimpleSerializer();
			__os.startToWrite();
			Proxy.__msgIdBase += 1;
			__os.writeInt(Proxy.__msgIdBase);
			__os.writeInt(2);

			__os.write(8, account);
			__os.write(8, passwd);
			__os.write(8, nickname);

			RmiManager.invoke(Proxy.__msgIdBase, __os, __cb);
		}

		static changeAvatar(__cb: ChangeAvatarCallback, sessionKey: string, avatar: ArrayBuffer) : void {
			var __os: SimpleSerializer = new SimpleSerializer();
			__os.startToWrite();
			Proxy.__msgIdBase += 1;
			__os.writeInt(Proxy.__msgIdBase);
			__os.writeInt(3);

			__os.write(8, sessionKey);
			__os.write(10, avatar);

			RmiManager.invoke(Proxy.__msgIdBase, __os, __cb);
		}

		static getPosts(__cb: GetPostsCallback, lastPostId: number, forNew: boolean, requestNum: number) : void {
			var __os: SimpleSerializer = new SimpleSerializer();
			__os.startToWrite();
			Proxy.__msgIdBase += 1;
			__os.writeInt(Proxy.__msgIdBase);
			__os.writeInt(20);

			__os.write(4, lastPostId);
			__os.write(2, forNew);
			__os.write(4, requestNum);

			RmiManager.invoke(Proxy.__msgIdBase, __os, __cb);
		}

		static getImage(__cb: GetImageCallback, imgId: number) : void {
			var __os: SimpleSerializer = new SimpleSerializer();
			__os.startToWrite();
			Proxy.__msgIdBase += 1;
			__os.writeInt(Proxy.__msgIdBase);
			__os.writeInt(21);

			__os.write(4, imgId);

			RmiManager.invoke(Proxy.__msgIdBase, __os, __cb);
		}

		static getMyPosts(__cb: GetMyPostsCallback, sessionKey: string, lastPostId: number, forNew: boolean) : void {
			var __os: SimpleSerializer = new SimpleSerializer();
			__os.startToWrite();
			Proxy.__msgIdBase += 1;
			__os.writeInt(Proxy.__msgIdBase);
			__os.writeInt(22);

			__os.write(8, sessionKey);
			__os.write(4, lastPostId);
			__os.write(2, forNew);

			RmiManager.invoke(Proxy.__msgIdBase, __os, __cb);
		}

		static startPost(__cb: StartPostCallback, sessionKey: string, title: string, content: string) : void {
			var __os: SimpleSerializer = new SimpleSerializer();
			__os.startToWrite();
			Proxy.__msgIdBase += 1;
			__os.writeInt(Proxy.__msgIdBase);
			__os.writeInt(30);

			__os.write(8, sessionKey);
			__os.write(8, title);
			__os.write(8, content);

			RmiManager.invoke(Proxy.__msgIdBase, __os, __cb);
		}

		static uploadPostImg(__cb: UploadPostImgCallback, sessionKey: string, img: ArrayBuffer, descrpt: string) : void {
			var __os: SimpleSerializer = new SimpleSerializer();
			__os.startToWrite();
			Proxy.__msgIdBase += 1;
			__os.writeInt(Proxy.__msgIdBase);
			__os.writeInt(31);

			__os.write(8, sessionKey);
			__os.write(10, img);
			__os.write(8, descrpt);

			RmiManager.invoke(Proxy.__msgIdBase, __os, __cb);
		}

		static endPost(__cb: EndPostCallback, sessionKey: string) : void {
			var __os: SimpleSerializer = new SimpleSerializer();
			__os.startToWrite();
			Proxy.__msgIdBase += 1;
			__os.writeInt(Proxy.__msgIdBase);
			__os.writeInt(32);

			__os.write(8, sessionKey);

			RmiManager.invoke(Proxy.__msgIdBase, __os, __cb);
		}

		static likePost(__cb: LikePostCallback, sessionKey: string, postId: number) : void {
			var __os: SimpleSerializer = new SimpleSerializer();
			__os.startToWrite();
			Proxy.__msgIdBase += 1;
			__os.writeInt(Proxy.__msgIdBase);
			__os.writeInt(40);

			__os.write(8, sessionKey);
			__os.write(4, postId);

			RmiManager.invoke(Proxy.__msgIdBase, __os, __cb);
		}

		static dislikePost(__cb: DislikePostCallback, sessionKey: string, postId: number) : void {
			var __os: SimpleSerializer = new SimpleSerializer();
			__os.startToWrite();
			Proxy.__msgIdBase += 1;
			__os.writeInt(Proxy.__msgIdBase);
			__os.writeInt(41);

			__os.write(8, sessionKey);
			__os.write(4, postId);

			RmiManager.invoke(Proxy.__msgIdBase, __os, __cb);
		}

		static commentPost(__cb: CommentPostCallback, sessionKey: string, postId: number, comments: string) : void {
			var __os: SimpleSerializer = new SimpleSerializer();
			__os.startToWrite();
			Proxy.__msgIdBase += 1;
			__os.writeInt(Proxy.__msgIdBase);
			__os.writeInt(42);

			__os.write(8, sessionKey);
			__os.write(4, postId);
			__os.write(8, comments);

			RmiManager.invoke(Proxy.__msgIdBase, __os, __cb);
		}

		static getComments(__cb: GetCommentsCallback, sessionKey: string, postId: number) : void {
			var __os: SimpleSerializer = new SimpleSerializer();
			__os.startToWrite();
			Proxy.__msgIdBase += 1;
			__os.writeInt(Proxy.__msgIdBase);
			__os.writeInt(43);

			__os.write(8, sessionKey);
			__os.write(4, postId);

			RmiManager.invoke(Proxy.__msgIdBase, __os, __cb);
		}

	} // end of Proxy
}// end of Rmi
