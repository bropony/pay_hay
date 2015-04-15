/// <reference path="../rmi/serialize.ts" />
/// <reference path="../rmi/rmimanager.ts" />
/// <reference path="../rmi/rmiclient.ts" />
/// <reference path="../user/usermanager.ts" />
/// <reference path="util.ts" />
var __extends = this.__extends || function (d, b) {
    for (var p in b) if (b.hasOwnProperty(p)) d[p] = b[p];
    function __() { this.constructor = d; }
    __.prototype = b.prototype;
    d.prototype = new __();
};
var View;
(function (View) {
    var userManager = User.UserManager;
    var LoginCBImpl = (function (_super) {
        __extends(LoginCBImpl, _super);
        function LoginCBImpl(acc, pwd) {
            _super.call(this);
            this.onResponse = function (userInfo) {
                userManager.userId = userInfo.userId;
                userManager.account = this.account;
                userManager.passwd = this.passwd;
                userManager.nickname = userInfo.nickname;
                userManager.sessionKey = userInfo.sessionKey;
                userManager.avatar = userInfo.avatar;
                console.log("Login Success");
                window.location.href = "/index.html";
            };
            this.onError = function (what, code) {
                alert("Login Error: " + what);
                console.log("What: %s, code:%d", what, code);
            };
            this.onTimeout = function () {
                alert("Login Timeout. Please Retry!");
            };
            this.account = acc;
            this.passwd = pwd;
        }
        return LoginCBImpl;
    })(Rmi.LoginCallback);
    View.login = function () {
        var username = document.getElementById("username")["value"];
        var passwd = document.getElementById("password")["value"];
        if (View.Util.alertEmptyString(username, "请填写账号")) {
            return;
        }
        if (View.Util.alertEmptyString(passwd, "请填写密码")) {
            return;
        }
        console.log("A:%s, p:%s", username, passwd);
        var cb = new LoginCBImpl(username, passwd);
        Rmi.Proxy.login(cb, username, passwd);
    };
})(View || (View = {}));
//# sourceMappingURL=login.js.map