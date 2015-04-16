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
        function onLoad() {
            User.UserManager.init();
            if (!User.UserManager.hasLogin()) {
                window.location.assign("/scene/login.html");
                return;
            }
        }
        NewPost.onLoad = onLoad;
        var StartPostCbImpl = (function (_super) {
            __extends(StartPostCbImpl, _super);
            function StartPostCbImpl() {
                _super.apply(this, arguments);
                this.onResponse = function () {
                };
                this.onError = function (what, code) {
                };
                this.onTimeout = function () {
                };
            }
            return StartPostCbImpl;
        })(Rmi.StartPostCallback);
        function newPost() {
        }
        NewPost.newPost = newPost;
    })(NewPost = View.NewPost || (View.NewPost = {}));
})(View || (View = {}));
//# sourceMappingURL=newpost.js.map