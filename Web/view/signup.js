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
    var SignupCBImpl = (function (_super) {
        __extends(SignupCBImpl, _super);
        function SignupCBImpl() {
            _super.apply(this, arguments);
            this.onResponse = function (userInfo) {
                View.ViewManager.setItem(View.ViewManager.keyUserId, userInfo.userId);
                View.ViewManager.setItem(View.ViewManager.keyAccount, this.account);
                View.ViewManager.setItem(View.ViewManager.keyPasswd, this.passwd);
                View.ViewManager.setItem(View.ViewManager.keyNickname, userInfo.nickname);
                View.ViewManager.setItem(View.ViewManager.keySessionKey, userInfo.sessionKey);
                console.log("Signup Success");
                window.location.href = "index.html";
            };
            this.onError = function (what, code) {
                alert("Login Error: " + what);
                console.log("What: %s, code:%d", what, code);
            };
            this.onTimeout = function () {
                alert("Login Timeout. Please Retry!");
            };
        }
        return SignupCBImpl;
    })(Rmi.SignupCallback);
    View.signup = function () {
        var username = document.getElementById("username")["value"];
        var nickname = document.getElementById("nickname")["value"];
        var passwd = document.getElementById("password")["value"];
        var repasswd = document.getElementById("re-password")["value"];
        if (passwd != repasswd) {
            alert("Two passwords you input are NOT equivelant!");
            return;
        }
        var cb = new SignupCBImpl();
        cb["account"] = username;
        cb["passwd"] = passwd;
        Rmi.Proxy.signup(cb, username, passwd, nickname);
    };
})(View || (View = {}));
//# sourceMappingURL=signup.js.map