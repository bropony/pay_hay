/// <reference path="../rmi/serialize.ts" />
/// <reference path="../rmi/rmimanager.ts" />
/// <reference path="../rmi/rmiclient.ts" />
/// <reference path="../user/usermanager.ts" />
/// <reference path="postmanager.ts" />

module View {
    var userManager = User.UserManager;

    export module Index {
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

        export function init() {
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

        class LoadPostCBImpl extends Rmi.GetPostsCallback {
            private _isRefresh: boolean;

            constructor(isRefresh: boolean) {
                super();

                this._isRefresh = isRefresh;
            }

            onResponse = function (postList: Rmi.SPost[]) {
                console.log("[LoadPostCBImpl] Loading posts success: %d,  %s", postList.length, this._isRefresh ? "Refresh" : "GetMore");

                var parentNode = document.getElementById("posts");

                if (this._isRefresh) {
                    for (var i = postList.length - 1; i >= 0; i--) {
                        PostManager.addPost(postList[i], parentNode, true);
                    }
                }
                else {
                    for (var i = 0; i < postList.length; i++) {
                        PostManager.addPost(postList[i], parentNode, false);
                    }
                }
            }

            onError = function (what: string, code: number) {
                console.log("[LoadPostCBImpl] Error: %s, %d", what, code);
            }

            onTimeout = function () {
                console.log("[LoadPostCBImpl] network timeout");
            }
        }

        export function loadPosts(refresh: boolean) {
            var cb = new LoadPostCBImpl(refresh);

            Rmi.Proxy.getPosts(cb, PostManager.getLastPostId(refresh), refresh, 10);
        }

        export function onIndexLoad() {
            init();
            loadPosts(true);
        }
    }
}
