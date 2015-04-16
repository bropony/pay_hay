/// <reference path="../rmi/serialize.ts" />
/// <reference path="../rmi/rmimanager.ts" />
/// <reference path="../rmi/rmiclient.ts" />
/// <reference path="../user/usermanager.ts" />
var __extends = this.__extends || function (d, b) {
    for (var p in b) if (b.hasOwnProperty(p)) d[p] = b[p];
    function __() { this.constructor = d; }
    __.prototype = b.prototype;
    d.prototype = new __();
};
var View;
(function (View) {
    var NewPost;
    (function (NewPost) {
        var images = [];
        var uploadedImgNum = 0;
        function onLoad() {
            User.UserManager.init();
            if (!User.UserManager.hasLogin()) {
                window.location.assign("/scene/login.html");
                return;
            }
            images = [];
            uploadedImgNum = 0;
        }
        NewPost.onLoad = onLoad;
        NewPost.addImage = function () {
            var file = document.getElementById("add-image")["files"][0];
            var reader = new FileReader();
            reader.onload = function (e) {
                var bb = reader.result;
                var uri = URL.createObjectURL(file);
                var divImg = document.getElementById("images");
                var img = document.createElement("img");
                img.className = "new-post-img";
                img.src = uri;
                divImg.appendChild(img);
                images.push(bb);
            };
            reader.readAsArrayBuffer(file);
        };
        var UploadImgCbImpl = (function (_super) {
            __extends(UploadImgCbImpl, _super);
            function UploadImgCbImpl() {
                _super.apply(this, arguments);
                this.onResponse = function (imgId) {
                    console.log("Upload Img Success: %d", imgId);
                    uploadedImgNum += 1;
                    if (uploadedImgNum == images.length) {
                        window.location.assign("/index.html");
                    }
                };
                this.onError = function (what, code) {
                    console.log("Upload Img Error: %s, %d", what, code);
                };
                this.onTimeout = function () {
                    console.log("Upload Img Timeout");
                };
            }
            return UploadImgCbImpl;
        })(Rmi.UploadPostImgExCallback);
        var StartPostCbImpl = (function (_super) {
            __extends(StartPostCbImpl, _super);
            function StartPostCbImpl() {
                _super.apply(this, arguments);
                this.onResponse = function (postId) {
                    for (var idx = 0; idx < images.length; ++idx) {
                        var cb = new UploadImgCbImpl();
                        Rmi.Proxy.uploadPostImgEx(cb, User.UserManager.sessionKey, images[idx], "Web Image", postId, idx);
                    }
                };
                this.onError = function (what, code) {
                    console.log("Start Post Error: %s, %d", what, code);
                };
                this.onTimeout = function () {
                    console.log("Start Post Timeout");
                };
            }
            return StartPostCbImpl;
        })(Rmi.StartPostExCallback);
        function newPost() {
            if (images.length <= 0) {
                alert("Please Add At Least One Image");
                return;
            }
            var title = document.getElementById("title")["value"];
            var content = document.getElementById("details")["value"];
            if (!title) {
                alert("Please Add a title");
                return;
            }
            var cb = new StartPostCbImpl();
            Rmi.Proxy.startPostEx(cb, User.UserManager.sessionKey, title, content, images.length);
        }
        NewPost.newPost = newPost;
    })(NewPost = View.NewPost || (View.NewPost = {}));
})(View || (View = {}));
//# sourceMappingURL=newpost.js.map