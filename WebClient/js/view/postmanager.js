/// <reference path="../rmi/serialize.ts" />
/// <reference path="../rmi/rmimanager.ts" />
/// <reference path="../rmi/rmiclient.ts" />
/// <reference path="../user/usermanager.ts" />
var View;
(function (View) {
    var _PostManager_Cls_ = (function () {
        function _PostManager_Cls_() {
            this._maxPostId = 0;
            this._minPostId = 0;
            this._lastRefreshDt = new Date(0);
        }
        _PostManager_Cls_.prototype.updateRefreshDt = function () {
            this._lastRefreshDt = new Date();
        };
        _PostManager_Cls_.prototype.isInRefreshCd = function () {
            var now = new Date();
            var passedMills = now.getTime() - this._lastRefreshDt.getTime();
            if (passedMills < 5000) {
                return false;
            }
            return true;
        };
        _PostManager_Cls_.prototype.getImgUrl = function (imgId) {
            if (imgId <= 0) {
                return "/res/default-avatar.png";
            }
            else {
                var url = Rmi.RmiManager.getUrl();
                url = url.replace("ws://", "http://");
                if (url.lastIndexOf("/") == url.length - 1) {
                    return url + "image/" + imgId + "/";
                }
                else {
                    return url + "/image/" + imgId + "/";
                }
            }
        };
        _PostManager_Cls_.prototype.getLastPostId = function (maxId) {
            if (maxId) {
                return this._maxPostId;
            }
            return this._minPostId;
        };
        _PostManager_Cls_.prototype.getPassedTime = function (dt) {
            var now = new Date();
            var passedMills = now.getTime() - dt.getTime();
            passedMills = passedMills > 0 ? passedMills : 0;
            var secs = Math.floor(passedMills / 1000);
            var mins = Math.floor(secs / 60);
            var hrs = Math.floor(mins / 60);
            var days = Math.floor(hrs / 24);
            var res = " 于";
            if (days > 0) {
                res += days + "天前";
            }
            else if (hrs > 0) {
                res += hrs + "小时前";
            }
            else if (mins > 0) {
                res += mins + "分钟前";
            }
            else {
                res += secs + "秒钟前";
            }
            res += "发布";
            return res;
        };
        _PostManager_Cls_.prototype.addPost = function (post, parentNode, insertAsFirstElem) {
            var postId = post.postId;
            if (postId > this._maxPostId) {
                this._maxPostId = postId;
            }
            if (0 == this._minPostId || postId < this._minPostId) {
                this._minPostId = postId;
            }
            var fieldSet = document.createElement("fieldset");
            fieldSet.id = "p" + postId;
            if (insertAsFirstElem) {
                if (parentNode.hasChildNodes) {
                    var firstChild = parentNode.firstChild;
                    parentNode.insertBefore(fieldSet, firstChild);
                }
                else {
                    parentNode.appendChild(fieldSet);
                }
            }
            else {
                parentNode.appendChild(fieldSet);
            }
            var legend = document.createElement("legend");
            legend.innerHTML = post.title;
            fieldSet.appendChild(legend);
            //post basics
            var postBasic = document.createElement("div");
            fieldSet.appendChild(postBasic);
            postBasic.className = "postBasic";
            var avatar = document.createElement("img");
            avatar.className = "avatar";
            avatar.src = this.getImgUrl(post.authorAvatarImgId);
            postBasic.appendChild(avatar);
            var author = document.createElement("span");
            author.id = "" + post.authorUserId;
            author.className = "author";
            author.nodeName = post.authorAccount;
            author.innerHTML = post.authorNickname;
            postBasic.appendChild(author);
            var postDt = document.createElement("span");
            postDt.innerHTML = this.getPassedTime(post.postDt);
            postBasic.appendChild(postDt);
            //content
            var content = document.createElement("article");
            content.innerHTML = post.content;
            content.className = "post-content";
            fieldSet.appendChild(content);
            for (var i = 0; i < post.imgIdList.length; ++i) {
                var image = document.createElement("img");
                image.src = this.getImgUrl(post.imgIdList[i]);
                image.id = "" + post.imgIdList[i];
                image.className = "post-img";
                fieldSet.appendChild(image);
            }
            var social = document.createElement("div");
            social.className = "social";
            fieldSet.appendChild(social);
            var likes = document.createElement("div");
            likes.className = "likes";
            likes.id = "" + postId;
            likes.innerHTML = "" + post.likes;
            likes.onclick = this.onLike;
            social.appendChild(likes);
            var dislikes = document.createElement("div");
            dislikes.className = "dislikes";
            dislikes.id = "" + postId;
            dislikes.innerHTML = "" + post.dislikes;
            dislikes.onclick = this.onDislike;
            social.appendChild(dislikes);
            var comments = document.createElement("div");
            comments.className = "comments";
            comments.id = "" + postId;
            comments.innerHTML = "" + post.comments;
            comments.onclick = this.onComment;
            social.appendChild(comments);
        };
        _PostManager_Cls_.prototype.onLike = function (e) {
            var postId = parseInt(e.target["id"]);
            var likes = parseInt(e.target["innerHTML"]);
            e.target["innerHTML"] = likes + 1;
        };
        _PostManager_Cls_.prototype.onDislike = function (e) {
            var postId = parseInt(e.target["id"]);
            var dislikes = parseInt(e.target["innerHTML"]);
            e.target["innerHTML"] = dislikes + 1;
        };
        _PostManager_Cls_.prototype.onComment = function (e) {
        };
        return _PostManager_Cls_;
    })();
    View.PostManager = new _PostManager_Cls_();
})(View || (View = {}));
//# sourceMappingURL=postmanager.js.map