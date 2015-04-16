/// <reference path="../rmi/serialize.ts" />
/// <reference path="../rmi/rmimanager.ts" />
/// <reference path="../rmi/rmiclient.ts" />
/// <reference path="postmanager.ts" />
/// <reference path="../user/usermanager.ts" />
var __extends = this.__extends || function (d, b) {
    for (var p in b) if (b.hasOwnProperty(p)) d[p] = b[p];
    function __() { this.constructor = d; }
    __.prototype = b.prototype;
    d.prototype = new __();
};
var View;
(function (View) {
    var userManager = User.UserManager;
    var MyInfo;
    (function (MyInfo) {
        function onLoad() {
            if (!userManager.hasLogin()) {
                window.location.assign("/scene/login.html");
                return;
            }
            if (userManager.avatarImgId > 0) {
                var imgUrl = View.PostManager.getImgUrl(userManager.avatarImgId);
                document.getElementById("avatar")["src"] = imgUrl;
            }
            document.getElementById("account").innerHTML = userManager.account;
            document.getElementById("nickname").innerHTML = userManager.nickname;
        }
        MyInfo.onLoad = onLoad;
        var ChangeAvatarCbImpl = (function (_super) {
            __extends(ChangeAvatarCbImpl, _super);
            function ChangeAvatarCbImpl() {
                _super.apply(this, arguments);
                this.onResponse = function (avatarImgId) {
                    console.log("Avatar changed");
                };
                this.onError = function (what, code) {
                    console.log("Change avatar error: %s, %d", what, code);
                };
                this.onTimeout = function () {
                    console.log("Change avatar timeout");
                };
            }
            return ChangeAvatarCbImpl;
        })(Rmi.ChangeAvatarCallback);
        function avatarSelected() {
            var file = document.getElementById('avatar-selector')["files"][0];
            var oldSrc = document.getElementById("avatar")["src"];
            var reader = new FileReader();
            reader.onload = function (e) {
                var bb = reader.result;
                var uri = URL.createObjectURL(file);
                document.getElementById("avatar")["src"] = uri;
                if (!confirm("确定要修改头像吗？")) {
                    document.getElementById("avatar")["src"] = oldSrc;
                    return;
                }
                Rmi.Proxy.changeAvatar(new ChangeAvatarCbImpl(), userManager.sessionKey, bb);
            };
            reader.readAsArrayBuffer(file);
        }
        MyInfo.avatarSelected = avatarSelected;
    })(MyInfo = View.MyInfo || (View.MyInfo = {}));
})(View || (View = {}));
//# sourceMappingURL=myinfo.js.map