/// <reference path="../rmi/rmidatastruct.ts" />
/// <reference path="../rmi/rmiclient.ts" />
/// <reference path="../rmi/rmimanager.ts" /> 
var __extends = this.__extends || function (d, b) {
    for (var p in b) if (b.hasOwnProperty(p)) d[p] = b[p];
    function __() { this.constructor = d; }
    __.prototype = b.prototype;
    d.prototype = new __();
};
var View;
(function (View) {
    var lastNewPostId = 0;
    var lastOldPostId = 0;
    var LoadPostCBImpl = (function (_super) {
        __extends(LoadPostCBImpl, _super);
        function LoadPostCBImpl() {
            _super.apply(this, arguments);
            this.onResponse = function (postList) {
                console.log("%d post loaded", postList.length);
                for (var i = 0; i < postList.length; ++i) {
                    processPost(postList[i]);
                    var postId = postList[i].postId;
                    if (lastNewPostId == 0) {
                        lastNewPostId = postId;
                    }
                    if (lastOldPostId == 0) {
                        lastOldPostId = postId;
                    }
                    if (lastNewPostId < postId) {
                        lastNewPostId = postId;
                    }
                    if (lastOldPostId > postId) {
                        lastOldPostId = postId;
                    }
                }
            };
            this.onError = function (what, code) {
                alert("Exp: " + what);
            };
            this.onTimeout = function () {
                console.log("Load Post Timeout");
            };
        }
        return LoadPostCBImpl;
    })(Rmi.GetPostsCallback);
    var LoadImgCbImpl = (function (_super) {
        __extends(LoadImgCbImpl, _super);
        function LoadImgCbImpl(pid, firstImg) {
            _super.call(this);
            this.onResponse = function (img, shortDesc) {
                var bytes = new Uint8Array(img);
                var blob = new Blob([bytes.buffer]);
                var uri = URL.createObjectURL(blob);
                if (this._firstImg) {
                    var summary = document.getElementById("s" + this._postId);
                    summary.style.backgroundImage = "url(" + uri + ")";
                }
                else {
                    var imgDiv = document.getElementById("i" + this._postId);
                    var newImg = document.createElement("img");
                    newImg.src = uri;
                    imgDiv.appendChild(newImg);
                }
            };
            this.onError = function (what, code) {
                console.log("LoadImgCbImpl Error: %s, %d", what, code);
            };
            this.onTimeout = function () {
            };
            this._postId = pid;
            this._firstImg = firstImg;
        }
        return LoadImgCbImpl;
    })(Rmi.GetImageCallback);
    var processPost = function (post) {
        var postParent = document.getElementById("post-list");
        if (!postParent) {
            alert("Oops");
        }
        var postId = post.postId;
        var details = document.createElement("details");
        details.id = "p" + postId;
        postParent.appendChild(details);
        var summary = document.createElement("summary");
        summary.id = "s" + postId;
        var h2 = document.createElement("h2");
        h2.innerHTML = post.title;
        summary.appendChild(h2);
        var author = document.createElement("h3");
        author.innerHTML = post.authorNickname;
        summary.appendChild(author);
        var postDt = document.createElement("h3");
        postDt.innerHTML = post.postDt.toDateString();
        summary.appendChild(postDt);
        details.appendChild(summary);
        var div = document.createElement("div");
        div.id = "i" + postId;
        details.appendChild(div);
        var content = document.createElement("p");
        content.innerHTML = post.content;
        details.appendChild(content);
        for (var i = 0; i < post.imgIdList.length; i++) {
            var imgCb = new LoadImgCbImpl(postId, i == 0);
            Rmi.Proxy.getImage(imgCb, post.imgIdList[i]);
        }
    };
    View.loadNewPost = function () {
        console.log("loading posts from server: %d", lastNewPostId);
        var cb = new LoadPostCBImpl();
        Rmi.Proxy.getPosts(cb, lastNewPostId, true, 10);
    };
})(View || (View = {}));
//# sourceMappingURL=home.js.map