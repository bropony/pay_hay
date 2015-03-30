/// <reference path="../rmi/rmidatastruct.ts" />
/// <reference path="../rmi/rmiclient.ts" />
/// <reference path="../rmi/rmimanager.ts" /> 
/// <reference path="viewmanager.ts" />
var __extends = this.__extends || function (d, b) {
    for (var p in b) if (b.hasOwnProperty(p)) d[p] = b[p];
    function __() { this.constructor = d; }
    __.prototype = b.prototype;
    d.prototype = new __();
};
var View;
(function (View) {
    var images = [];
    var imgIdx = 0;
    View.onNewPostLoad = function () {
        var account = View.ViewManager.getItem(View.ViewManager.keyAccount);
        if (!account) {
            window.location.href = "login.html";
        }
        images = [];
        imgIdx = 0;
    };
    View.addImage = function () {
        var file = document.getElementById("add-image")["files"][0];
        var reader = new FileReader();
        reader.onload = function (e) {
            var bb = reader.result;
            var uri = URL.createObjectURL(file);
            var divImg = document.getElementById("images");
            if (images.length > 0) {
                var hr = document.createElement("hr");
                divImg.appendChild(hr);
            }
            var img = document.createElement("img");
            img.src = uri;
            divImg.appendChild(img);
            images.push(bb);
        };
        reader.readAsArrayBuffer(file);
    };
    var uploadPostImage = function () {
        if (imgIdx >= images.length) {
            return;
        }
        var cb = new UploadImgCBImpl();
        Rmi.Proxy.uploadPostImg(cb, View.ViewManager.getItem(View.ViewManager.keySessionKey), images[imgIdx], "Post Image");
        imgIdx += 1;
    };
    var EndPostCBImpl = (function (_super) {
        __extends(EndPostCBImpl, _super);
        function EndPostCBImpl() {
            _super.apply(this, arguments);
            this.onResponse = function (postId) {
                window.location.href = "index.html";
            };
        }
        return EndPostCBImpl;
    })(Rmi.EndPostCallback);
    var UploadImgCBImpl = (function (_super) {
        __extends(UploadImgCBImpl, _super);
        function UploadImgCBImpl() {
            _super.apply(this, arguments);
            this.onResponse = function (imgId) {
                console.log("upload img success: " + imgId);
                if (imgId >= images.length) {
                    var endCb = new EndPostCBImpl();
                    Rmi.Proxy.endPost(endCb, View.ViewManager.getItem(View.ViewManager.keySessionKey));
                }
                else {
                    uploadPostImage();
                }
            };
            this.onError = function (what, code) {
                alert("StartPost: " + what);
            };
            this.onTimeout = function () {
            };
        }
        return UploadImgCBImpl;
    })(Rmi.UploadPostImgCallback);
    var StartPostCBImpl = (function (_super) {
        __extends(StartPostCBImpl, _super);
        function StartPostCBImpl() {
            _super.apply(this, arguments);
            this.onResponse = function () {
                if (imgIdx < images.length) {
                    uploadPostImage();
                }
            };
            this.onError = function (what, code) {
                alert("StartPost: " + what);
            };
            this.onTimeout = function () {
                alert("Network Timeout");
            };
        }
        return StartPostCBImpl;
    })(Rmi.StartPostCallback);
    View.newPost = function () {
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
        var cb = new StartPostCBImpl();
        Rmi.Proxy.startPost(cb, View.ViewManager.getItem(View.ViewManager.keySessionKey), title, content);
    };
})(View || (View = {}));
//# sourceMappingURL=newpost.js.map