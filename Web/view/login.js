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
    var LoginCBImpl = (function (_super) {
        __extends(LoginCBImpl, _super);
        function LoginCBImpl() {
            _super.apply(this, arguments);
            this.onResponse = function (userInfo) {
                alert("login success");
                View.ViewManager.setItem(View.ViewManager.keyUserId, userInfo.userId);
                View.ViewManager.setItem(View.ViewManager.keyAccount, this.account);
                View.ViewManager.setItem(View.ViewManager.keyPasswd, this.passwd);
                View.ViewManager.setItem(View.ViewManager.keyNickname, userInfo.nickname);
                View.ViewManager.setItem(View.ViewManager.keySessionKey, userInfo.sessionKey);
                console.log("Login Success");
                //document.body.innerHTML = "Login Success";
            };
            this.onError = function (what, code) {
                alert("Login Error: " + what);
                console.log("What: %s, code:%d", what, code);
            };
            this.onTimeout = function () {
                alert("Login Timeout. Please Retry!");
            };
        }
        return LoginCBImpl;
    })(Rmi.LoginCallback);
    View.login = function () {
        var username = document.getElementById("username")["value"];
        var passwd = document.getElementById("password")["value"];
        console.log("A:%s, p:%s", username, passwd);
        var cb = new LoginCBImpl();
        Rmi.Proxy.login(cb, username, passwd);
        alert("zzzzzzzzzzzzzzz");
    };
})(View || (View = {}));
;
//# sourceMappingURL=login.js.map