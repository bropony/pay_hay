/// <reference path="serialize.ts" />
/// <reference path="rmidatastruct.ts" />
/// <reference path="rmimanager.ts" />
var Rmi;
(function (Rmi) {
    //Callbacks
    //LoginCallback
    var LoginCallback = (function () {
        function LoginCallback() {
        }
        LoginCallback.prototype.__onResponse = function (__is) {
            var userInfo = new Rmi.SLoginReturn();
            userInfo.__read(__is);
            this.onResponse(userInfo);
        };
        LoginCallback.prototype.__onError = function (what, code) {
            this.onError(what, code);
        };
        LoginCallback.prototype.__onTimeout = function () {
            this.onTimeout();
        };
        return LoginCallback;
    })();
    Rmi.LoginCallback = LoginCallback; // end of LoginCallback
    //SignupCallback
    var SignupCallback = (function () {
        function SignupCallback() {
        }
        SignupCallback.prototype.__onResponse = function (__is) {
            var userInfo = new Rmi.SLoginReturn();
            userInfo.__read(__is);
            this.onResponse(userInfo);
        };
        SignupCallback.prototype.__onError = function (what, code) {
            this.onError(what, code);
        };
        SignupCallback.prototype.__onTimeout = function () {
            this.onTimeout();
        };
        return SignupCallback;
    })();
    Rmi.SignupCallback = SignupCallback; // end of SignupCallback
    //ChangeAvatarCallback
    var ChangeAvatarCallback = (function () {
        function ChangeAvatarCallback() {
        }
        ChangeAvatarCallback.prototype.__onResponse = function (__is) {
            var avatarImgId = 0;
            avatarImgId = __is.read(4);
            this.onResponse(avatarImgId);
        };
        ChangeAvatarCallback.prototype.__onError = function (what, code) {
            this.onError(what, code);
        };
        ChangeAvatarCallback.prototype.__onTimeout = function () {
            this.onTimeout();
        };
        return ChangeAvatarCallback;
    })();
    Rmi.ChangeAvatarCallback = ChangeAvatarCallback; // end of ChangeAvatarCallback
    //GetPostsCallback
    var GetPostsCallback = (function () {
        function GetPostsCallback() {
        }
        GetPostsCallback.prototype.__onResponse = function (__is) {
            var postList = [];
            postList = Rmi.readSeqPost(__is);
            this.onResponse(postList);
        };
        GetPostsCallback.prototype.__onError = function (what, code) {
            this.onError(what, code);
        };
        GetPostsCallback.prototype.__onTimeout = function () {
            this.onTimeout();
        };
        return GetPostsCallback;
    })();
    Rmi.GetPostsCallback = GetPostsCallback; // end of GetPostsCallback
    //GetImageCallback
    var GetImageCallback = (function () {
        function GetImageCallback() {
        }
        GetImageCallback.prototype.__onResponse = function (__is) {
            var img = new ArrayBuffer(0);
            img = __is.read(10);
            var shortDesc = "";
            shortDesc = __is.read(8);
            this.onResponse(img, shortDesc);
        };
        GetImageCallback.prototype.__onError = function (what, code) {
            this.onError(what, code);
        };
        GetImageCallback.prototype.__onTimeout = function () {
            this.onTimeout();
        };
        return GetImageCallback;
    })();
    Rmi.GetImageCallback = GetImageCallback; // end of GetImageCallback
    //GetMyPostsCallback
    var GetMyPostsCallback = (function () {
        function GetMyPostsCallback() {
        }
        GetMyPostsCallback.prototype.__onResponse = function (__is) {
            var postList = [];
            postList = Rmi.readSeqPost(__is);
            this.onResponse(postList);
        };
        GetMyPostsCallback.prototype.__onError = function (what, code) {
            this.onError(what, code);
        };
        GetMyPostsCallback.prototype.__onTimeout = function () {
            this.onTimeout();
        };
        return GetMyPostsCallback;
    })();
    Rmi.GetMyPostsCallback = GetMyPostsCallback; // end of GetMyPostsCallback
    //StartPostCallback
    var StartPostCallback = (function () {
        function StartPostCallback() {
        }
        StartPostCallback.prototype.__onResponse = function (__is) {
            this.onResponse();
        };
        StartPostCallback.prototype.__onError = function (what, code) {
            this.onError(what, code);
        };
        StartPostCallback.prototype.__onTimeout = function () {
            this.onTimeout();
        };
        return StartPostCallback;
    })();
    Rmi.StartPostCallback = StartPostCallback; // end of StartPostCallback
    //UploadPostImgCallback
    var UploadPostImgCallback = (function () {
        function UploadPostImgCallback() {
        }
        UploadPostImgCallback.prototype.__onResponse = function (__is) {
            var imgId = 0;
            imgId = __is.read(4);
            this.onResponse(imgId);
        };
        UploadPostImgCallback.prototype.__onError = function (what, code) {
            this.onError(what, code);
        };
        UploadPostImgCallback.prototype.__onTimeout = function () {
            this.onTimeout();
        };
        return UploadPostImgCallback;
    })();
    Rmi.UploadPostImgCallback = UploadPostImgCallback; // end of UploadPostImgCallback
    //EndPostCallback
    var EndPostCallback = (function () {
        function EndPostCallback() {
        }
        EndPostCallback.prototype.__onResponse = function (__is) {
            var postId = 0;
            postId = __is.read(4);
            this.onResponse(postId);
        };
        EndPostCallback.prototype.__onError = function (what, code) {
            this.onError(what, code);
        };
        EndPostCallback.prototype.__onTimeout = function () {
            this.onTimeout();
        };
        return EndPostCallback;
    })();
    Rmi.EndPostCallback = EndPostCallback; // end of EndPostCallback
    //LikePostCallback
    var LikePostCallback = (function () {
        function LikePostCallback() {
        }
        LikePostCallback.prototype.__onResponse = function (__is) {
            this.onResponse();
        };
        LikePostCallback.prototype.__onError = function (what, code) {
            this.onError(what, code);
        };
        LikePostCallback.prototype.__onTimeout = function () {
            this.onTimeout();
        };
        return LikePostCallback;
    })();
    Rmi.LikePostCallback = LikePostCallback; // end of LikePostCallback
    //DislikePostCallback
    var DislikePostCallback = (function () {
        function DislikePostCallback() {
        }
        DislikePostCallback.prototype.__onResponse = function (__is) {
            this.onResponse();
        };
        DislikePostCallback.prototype.__onError = function (what, code) {
            this.onError(what, code);
        };
        DislikePostCallback.prototype.__onTimeout = function () {
            this.onTimeout();
        };
        return DislikePostCallback;
    })();
    Rmi.DislikePostCallback = DislikePostCallback; // end of DislikePostCallback
    //CommentPostCallback
    var CommentPostCallback = (function () {
        function CommentPostCallback() {
        }
        CommentPostCallback.prototype.__onResponse = function (__is) {
            this.onResponse();
        };
        CommentPostCallback.prototype.__onError = function (what, code) {
            this.onError(what, code);
        };
        CommentPostCallback.prototype.__onTimeout = function () {
            this.onTimeout();
        };
        return CommentPostCallback;
    })();
    Rmi.CommentPostCallback = CommentPostCallback; // end of CommentPostCallback
    //GetCommentsCallback
    var GetCommentsCallback = (function () {
        function GetCommentsCallback() {
        }
        GetCommentsCallback.prototype.__onResponse = function (__is) {
            var comments = [];
            comments = Rmi.readSeqComment(__is);
            this.onResponse(comments);
        };
        GetCommentsCallback.prototype.__onError = function (what, code) {
            this.onError(what, code);
        };
        GetCommentsCallback.prototype.__onTimeout = function () {
            this.onTimeout();
        };
        return GetCommentsCallback;
    })();
    Rmi.GetCommentsCallback = GetCommentsCallback; // end of GetCommentsCallback
    //Client Rmi Proxy
    var Proxy = (function () {
        function Proxy() {
        }
        Proxy.login = function (__cb, account, passwd) {
            var __os = new Rmi.SimpleSerializer();
            __os.startToWrite();
            Proxy.__msgIdBase += 1;
            __os.writeInt(Proxy.__msgIdBase);
            __os.writeInt(1);
            __os.write(8, account);
            __os.write(8, passwd);
            Rmi.RmiManager.invoke(Proxy.__msgIdBase, __os, __cb);
        };
        Proxy.signup = function (__cb, account, passwd, nickname) {
            var __os = new Rmi.SimpleSerializer();
            __os.startToWrite();
            Proxy.__msgIdBase += 1;
            __os.writeInt(Proxy.__msgIdBase);
            __os.writeInt(2);
            __os.write(8, account);
            __os.write(8, passwd);
            __os.write(8, nickname);
            Rmi.RmiManager.invoke(Proxy.__msgIdBase, __os, __cb);
        };
        Proxy.changeAvatar = function (__cb, sessionKey, avatar) {
            var __os = new Rmi.SimpleSerializer();
            __os.startToWrite();
            Proxy.__msgIdBase += 1;
            __os.writeInt(Proxy.__msgIdBase);
            __os.writeInt(3);
            __os.write(8, sessionKey);
            __os.write(10, avatar);
            Rmi.RmiManager.invoke(Proxy.__msgIdBase, __os, __cb);
        };
        Proxy.getPosts = function (__cb, lastPostId, forNew, requestNum) {
            var __os = new Rmi.SimpleSerializer();
            __os.startToWrite();
            Proxy.__msgIdBase += 1;
            __os.writeInt(Proxy.__msgIdBase);
            __os.writeInt(20);
            __os.write(4, lastPostId);
            __os.write(2, forNew);
            __os.write(4, requestNum);
            Rmi.RmiManager.invoke(Proxy.__msgIdBase, __os, __cb);
        };
        Proxy.getImage = function (__cb, imgId) {
            var __os = new Rmi.SimpleSerializer();
            __os.startToWrite();
            Proxy.__msgIdBase += 1;
            __os.writeInt(Proxy.__msgIdBase);
            __os.writeInt(21);
            __os.write(4, imgId);
            Rmi.RmiManager.invoke(Proxy.__msgIdBase, __os, __cb);
        };
        Proxy.getMyPosts = function (__cb, sessionKey, lastPostId, forNew) {
            var __os = new Rmi.SimpleSerializer();
            __os.startToWrite();
            Proxy.__msgIdBase += 1;
            __os.writeInt(Proxy.__msgIdBase);
            __os.writeInt(22);
            __os.write(8, sessionKey);
            __os.write(4, lastPostId);
            __os.write(2, forNew);
            Rmi.RmiManager.invoke(Proxy.__msgIdBase, __os, __cb);
        };
        Proxy.startPost = function (__cb, sessionKey, title, content) {
            var __os = new Rmi.SimpleSerializer();
            __os.startToWrite();
            Proxy.__msgIdBase += 1;
            __os.writeInt(Proxy.__msgIdBase);
            __os.writeInt(30);
            __os.write(8, sessionKey);
            __os.write(8, title);
            __os.write(8, content);
            Rmi.RmiManager.invoke(Proxy.__msgIdBase, __os, __cb);
        };
        Proxy.uploadPostImg = function (__cb, sessionKey, img, descrpt) {
            var __os = new Rmi.SimpleSerializer();
            __os.startToWrite();
            Proxy.__msgIdBase += 1;
            __os.writeInt(Proxy.__msgIdBase);
            __os.writeInt(31);
            __os.write(8, sessionKey);
            __os.write(10, img);
            __os.write(8, descrpt);
            Rmi.RmiManager.invoke(Proxy.__msgIdBase, __os, __cb);
        };
        Proxy.endPost = function (__cb, sessionKey) {
            var __os = new Rmi.SimpleSerializer();
            __os.startToWrite();
            Proxy.__msgIdBase += 1;
            __os.writeInt(Proxy.__msgIdBase);
            __os.writeInt(32);
            __os.write(8, sessionKey);
            Rmi.RmiManager.invoke(Proxy.__msgIdBase, __os, __cb);
        };
        Proxy.likePost = function (__cb, sessionKey, postId) {
            var __os = new Rmi.SimpleSerializer();
            __os.startToWrite();
            Proxy.__msgIdBase += 1;
            __os.writeInt(Proxy.__msgIdBase);
            __os.writeInt(40);
            __os.write(8, sessionKey);
            __os.write(4, postId);
            Rmi.RmiManager.invoke(Proxy.__msgIdBase, __os, __cb);
        };
        Proxy.dislikePost = function (__cb, sessionKey, postId) {
            var __os = new Rmi.SimpleSerializer();
            __os.startToWrite();
            Proxy.__msgIdBase += 1;
            __os.writeInt(Proxy.__msgIdBase);
            __os.writeInt(41);
            __os.write(8, sessionKey);
            __os.write(4, postId);
            Rmi.RmiManager.invoke(Proxy.__msgIdBase, __os, __cb);
        };
        Proxy.commentPost = function (__cb, sessionKey, postId, comments) {
            var __os = new Rmi.SimpleSerializer();
            __os.startToWrite();
            Proxy.__msgIdBase += 1;
            __os.writeInt(Proxy.__msgIdBase);
            __os.writeInt(42);
            __os.write(8, sessionKey);
            __os.write(4, postId);
            __os.write(8, comments);
            Rmi.RmiManager.invoke(Proxy.__msgIdBase, __os, __cb);
        };
        Proxy.getComments = function (__cb, sessionKey, postId) {
            var __os = new Rmi.SimpleSerializer();
            __os.startToWrite();
            Proxy.__msgIdBase += 1;
            __os.writeInt(Proxy.__msgIdBase);
            __os.writeInt(43);
            __os.write(8, sessionKey);
            __os.write(4, postId);
            Rmi.RmiManager.invoke(Proxy.__msgIdBase, __os, __cb);
        };
        Proxy.__msgIdBase = 0;
        return Proxy;
    })();
    Rmi.Proxy = Proxy; // end of Proxy
})(Rmi || (Rmi = {})); // end of Rmi
//# sourceMappingURL=rmiclient.js.map