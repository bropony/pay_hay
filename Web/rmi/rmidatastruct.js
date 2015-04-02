/// <reference path="serialize.ts" />
var Rmi;
(function (Rmi) {
    //Read SeqInt
    Rmi.readSeqInt = function (__is) {
        var size = __is.readInt();
        var res = [];
        for (var i = 0; i < size; i++) {
            var val = 0;
            val = __is.read(4);
            res.push(val);
        }
        return res;
    };
    //Write SeqInt
    Rmi.writeSeqInt = function (__os, data) {
        var size = data.length;
        __os.writeInt(size);
        for (var i = 0; i < size; i++) {
            __os.write(4, data[i]);
        }
    };
    //Read SeqString
    Rmi.readSeqString = function (__is) {
        var size = __is.readInt();
        var res = [];
        for (var i = 0; i < size; i++) {
            var val = "";
            val = __is.read(8);
            res.push(val);
        }
        return res;
    };
    //Write SeqString
    Rmi.writeSeqString = function (__os, data) {
        var size = data.length;
        __os.writeInt(size);
        for (var i = 0; i < size; i++) {
            __os.write(8, data[i]);
        }
    };
    //Read SeqDate
    Rmi.readSeqDate = function (__is) {
        var size = __is.readInt();
        var res = [];
        for (var i = 0; i < size; i++) {
            var val = new Date();
            val = __is.read(9);
            res.push(val);
        }
        return res;
    };
    //Write SeqDate
    Rmi.writeSeqDate = function (__os, data) {
        var size = data.length;
        __os.writeInt(size);
        for (var i = 0; i < size; i++) {
            __os.write(9, data[i]);
        }
    };
    //Read SeqBool
    Rmi.readSeqBool = function (__is) {
        var size = __is.readInt();
        var res = [];
        for (var i = 0; i < size; i++) {
            var val = false;
            val = __is.read(2);
            res.push(val);
        }
        return res;
    };
    //Write SeqBool
    Rmi.writeSeqBool = function (__os, data) {
        var size = data.length;
        __os.writeInt(size);
        for (var i = 0; i < size; i++) {
            __os.write(2, data[i]);
        }
    };
    //Read SeqByte
    Rmi.readSeqByte = function (__is) {
        var size = __is.readInt();
        var res = [];
        for (var i = 0; i < size; i++) {
            var val = 0;
            val = __is.read(1);
            res.push(val);
        }
        return res;
    };
    //Write SeqByte
    Rmi.writeSeqByte = function (__os, data) {
        var size = data.length;
        __os.writeInt(size);
        for (var i = 0; i < size; i++) {
            __os.write(1, data[i]);
        }
    };
    //Read SeqShort
    Rmi.readSeqShort = function (__is) {
        var size = __is.readInt();
        var res = [];
        for (var i = 0; i < size; i++) {
            var val = 0;
            val = __is.read(3);
            res.push(val);
        }
        return res;
    };
    //Write SeqShort
    Rmi.writeSeqShort = function (__os, data) {
        var size = data.length;
        __os.writeInt(size);
        for (var i = 0; i < size; i++) {
            __os.write(3, data[i]);
        }
    };
    //Read SeqDouble
    Rmi.readSeqDouble = function (__is) {
        var size = __is.readInt();
        var res = [];
        for (var i = 0; i < size; i++) {
            var val = 0;
            val = __is.read(7);
            res.push(val);
        }
        return res;
    };
    //Write SeqDouble
    Rmi.writeSeqDouble = function (__os, data) {
        var size = data.length;
        __os.writeInt(size);
        for (var i = 0; i < size; i++) {
            __os.write(7, data[i]);
        }
    };
    //Read SeqLong
    Rmi.readSeqLong = function (__is) {
        var size = __is.readInt();
        var res = [];
        for (var i = 0; i < size; i++) {
            var val = 0;
            val = __is.read(5);
            res.push(val);
        }
        return res;
    };
    //Write SeqLong
    Rmi.writeSeqLong = function (__os, data) {
        var size = data.length;
        __os.writeInt(size);
        for (var i = 0; i < size; i++) {
            __os.write(5, data[i]);
        }
    };
    //Read SeqImage
    Rmi.readSeqImage = function (__is) {
        var size = __is.readInt();
        var res = [];
        for (var i = 0; i < size; i++) {
            var val = new ArrayBuffer(0);
            val = __is.read(10);
            res.push(val);
        }
        return res;
    };
    //Write SeqImage
    Rmi.writeSeqImage = function (__os, data) {
        var size = data.length;
        __os.writeInt(size);
        for (var i = 0; i < size; i++) {
            __os.write(10, data[i]);
        }
    };
    var SLoginReturn = (function () {
        function SLoginReturn() {
            this.userId = 0;
            this.nickname = "";
            this.avatar = new ArrayBuffer(0);
            this.avatarImgId = 0;
            this.sessionKey = "";
        }
        SLoginReturn.prototype.__read = function (__is) {
            this.userId = __is.read(4);
            this.nickname = __is.read(8);
            this.avatar = __is.read(10);
            this.avatarImgId = __is.read(4);
            this.sessionKey = __is.read(8);
        };
        SLoginReturn.prototype.__write = function (__os) {
            __os.write(4, this.userId);
            __os.write(8, this.nickname);
            __os.write(10, this.avatar);
            __os.write(4, this.avatarImgId);
            __os.write(8, this.sessionKey);
        };
        return SLoginReturn;
    })();
    Rmi.SLoginReturn = SLoginReturn; // end of SLoginReturn
    var SPost = (function () {
        function SPost() {
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
        SPost.prototype.__read = function (__is) {
            this.postId = __is.read(4);
            this.title = __is.read(8);
            this.content = __is.read(8);
            this.authorUserId = __is.read(4);
            this.authorAccount = __is.read(8);
            this.authorNickname = __is.read(8);
            this.imgIdList = Rmi.readSeqInt(__is);
            this.postDt = __is.read(9);
            this.likes = __is.read(4);
            this.dislikes = __is.read(4);
            this.comments = __is.read(4);
        };
        SPost.prototype.__write = function (__os) {
            __os.write(4, this.postId);
            __os.write(8, this.title);
            __os.write(8, this.content);
            __os.write(4, this.authorUserId);
            __os.write(8, this.authorAccount);
            __os.write(8, this.authorNickname);
            Rmi.writeSeqInt(__os, this.imgIdList);
            __os.write(9, this.postDt);
            __os.write(4, this.likes);
            __os.write(4, this.dislikes);
            __os.write(4, this.comments);
        };
        return SPost;
    })();
    Rmi.SPost = SPost; // end of SPost
    //Read SeqPost
    Rmi.readSeqPost = function (__is) {
        var size = __is.readInt();
        var res = [];
        for (var i = 0; i < size; i++) {
            var val = new SPost();
            val.__read(__is);
            res.push(val);
        }
        return res;
    };
    //Write SeqPost
    Rmi.writeSeqPost = function (__os, data) {
        var size = data.length;
        __os.writeInt(size);
        for (var i = 0; i < size; i++) {
            data[i].__write(__os);
        }
    };
    var SComment = (function () {
        function SComment() {
            this.userId = 0;
            this.nickname = "";
            this.content = "";
            this.commentDt = new Date();
        }
        SComment.prototype.__read = function (__is) {
            this.userId = __is.read(4);
            this.nickname = __is.read(8);
            this.content = __is.read(8);
            this.commentDt = __is.read(9);
        };
        SComment.prototype.__write = function (__os) {
            __os.write(4, this.userId);
            __os.write(8, this.nickname);
            __os.write(8, this.content);
            __os.write(9, this.commentDt);
        };
        return SComment;
    })();
    Rmi.SComment = SComment; // end of SComment
    //Read SeqComment
    Rmi.readSeqComment = function (__is) {
        var size = __is.readInt();
        var res = [];
        for (var i = 0; i < size; i++) {
            var val = new SComment();
            val.__read(__is);
            res.push(val);
        }
        return res;
    };
    //Write SeqComment
    Rmi.writeSeqComment = function (__os, data) {
        var size = data.length;
        __os.writeInt(size);
        for (var i = 0; i < size; i++) {
            data[i].__write(__os);
        }
    };
})(Rmi || (Rmi = {})); //end of module Rmi
//# sourceMappingURL=rmidatastruct.js.map