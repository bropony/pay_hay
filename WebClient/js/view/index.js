/// <reference path="../rmi/serialize.ts" />
/// <reference path="../rmi/rmimanager.ts" />
/// <reference path="../rmi/rmiclient.ts" />
/// <reference path="../user/usermanager.ts" />
/// <reference path="postmanager.ts" />
var __extends = this.__extends || function (d, b) {
    for (var p in b) if (b.hasOwnProperty(p)) d[p] = b[p];
    function __() { this.constructor = d; }
    __.prototype = b.prototype;
    d.prototype = new __();
};
var View;
(function (View) {
    var userManager = User.UserManager;
    var Index;
    (function (Index) {
        function logout() {
            if (!confirm("您确定要 登出 吗？")) {
                return;
            }
            userManager.clear();
            var htmlNode = document.getElementById("user-center");
            htmlNode.innerHTML = '';
            var loginLink = document.createElement("a");
            loginLink.href = "/scene/login.html";
            loginLink.innerHTML = "登录";
            htmlNode.appendChild(loginLink);
            var signupLink = document.createElement("a");
            signupLink.href = "/scene/signup.html";
            signupLink.innerHTML = "注册";
            htmlNode.appendChild(signupLink);
        }
        function init() {
            if (userManager.hasLogin()) {
                var htmlNode = document.getElementById("user-center");
                htmlNode.innerHTML = '';
                var myEntrance = document.createElement("a");
                myEntrance.href = "/scene/my-info.html";
                myEntrance.innerHTML = "Hi " + userManager.nickname;
                myEntrance.style.color = "green";
                htmlNode.appendChild(myEntrance);
                var logoutLink = document.createElement("a");
                logoutLink.onclick = logout;
                logoutLink.id = "logout";
                logoutLink.innerHTML = "登出";
                logoutLink.href = "#logout";
                htmlNode.appendChild(logoutLink);
            }
        }
        Index.init = init;
        var LoadPostCBImpl = (function (_super) {
            __extends(LoadPostCBImpl, _super);
            function LoadPostCBImpl(isRefresh) {
                _super.call(this);
                this.onResponse = function (postList) {
                    console.log("[LoadPostCBImpl] Loading posts success: %d,  %s", postList.length, this._isRefresh ? "Refresh" : "GetMore");
                    var parentNode = document.getElementById("posts");
                    if (this._isRefresh) {
                        for (var i = postList.length - 1; i >= 0; i--) {
                            View.PostManager.addPost(postList[i], parentNode, true);
                        }
                    }
                    else {
                        for (var i = 0; i < postList.length; i++) {
                            View.PostManager.addPost(postList[i], parentNode, false);
                        }
                    }
                };
                this.onError = function (what, code) {
                    console.log("[LoadPostCBImpl] Error: %s, %d", what, code);
                };
                this.onTimeout = function () {
                    console.log("[LoadPostCBImpl] network timeout");
                };
                this._isRefresh = isRefresh;
            }
            return LoadPostCBImpl;
        })(Rmi.GetPostsCallback);
        function loadPosts(refresh) {
            var cb = new LoadPostCBImpl(refresh);
            Rmi.Proxy.getPosts(cb, View.PostManager.getLastPostId(refresh), refresh, 10);
        }
        Index.loadPosts = loadPosts;
        function onIndexLoad() {
            init();
            loadPosts(true);
        }
        Index.onIndexLoad = onIndexLoad;
    })(Index = View.Index || (View.Index = {}));
})(View || (View = {}));
//# sourceMappingURL=index.js.map