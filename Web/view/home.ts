/// <reference path="../rmi/rmidatastruct.ts" />
/// <reference path="../rmi/rmiclient.ts" />
/// <reference path="../rmi/rmimanager.ts" /> 

module View {
    var lastNewPostId = 0;
    var lastOldPostId = 0;

    class LoadPostCBImpl extends Rmi.GetPostsCallback {
        onResponse = function (postList: Rmi.SPost[]) {
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
        }

        onError = function (what: string, code: number) {
            alert("Exp: " + what);
        }

        onTimeout = function () {
            console.log("Load Post Timeout");
        }
    }

    class LoadImgCbImpl extends Rmi.GetImageCallback {
        private _postId: number;
        private _firstImg: boolean;

        constructor(pid: number, firstImg: boolean) {
            super();
            this._postId = pid;
            this._firstImg = firstImg;
        }

        onResponse = function (img: ArrayBuffer, shortDesc: string) {
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
        }

        onError = function (what: string, code: number) {
            console.log("LoadImgCbImpl Error: %s, %d", what, code);
        }

        onTimeout = function () {
        }
    }

    var processPost = function (post: Rmi.SPost) {
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
    }

    export var loadNewPost = function () {
        console.log("loading posts from server: %d", lastNewPostId);

        var cb = new LoadPostCBImpl();
        Rmi.Proxy.getPosts(cb, lastNewPostId, true, 10);
    }
}