/// <reference path="../rmi/serialize.ts" />
/// <reference path="../rmi/rmimanager.ts" />
/// <reference path="../rmi/rmiclient.ts" />
/// <reference path="../user/usermanager.ts" />
/// <reference path="util.ts" />

module View {
    var userManager = User.UserManager;

    class SignupCBImpl extends Rmi.SignupCallback {
        private account: string;
        private passwd: string;

        constructor(acc: string, pwd: string) {
            super();

            this.account = acc;
            this.passwd = pwd;
        }

        onResponse = function (userInfo: Rmi.SLoginReturn) {
            userManager.userId = userInfo.userId;
            userManager.account = this.account;
            userManager.passwd = this.passwd;
            userManager.nickname = userInfo.nickname;
            userManager.sessionKey = userInfo.sessionKey;
            userManager.avatar = userInfo.avatar;

            console.log("Login Success");
            window.location.href = "/index.html";

            console.log("Signup Success");
            window.location.href = "index.html";
        }

        onError = function (what: string, code: number) {
            alert("Login Error: " + what);
            console.log("What: %s, code:%d", what, code);
        }

        onTimeout = function () {
            alert("Login Timeout. Please Retry!");
        }
    }

    export var signup = function () {
        var username = document.getElementById("username")["value"];
        var nickname = document.getElementById("nickname")["value"];
        var passwd = document.getElementById("password")["value"];
        var repasswd = document.getElementById("re-password")["value"];

        if (Util.alertEmptyString(username, "请填写账号")) {
            return;
        }

        if (Util.alertEmptyString(nickname, "请填写昵称")) {
            return;
        }

        if (Util.alertEmptyString(passwd, "请填写密码")) {
            return;
        }

        if (passwd != repasswd) {
            alert("Two passwords you input are NOT equivelant!");
            return;
        }

        var cb = new SignupCBImpl(username, passwd);
        Rmi.Proxy.signup(cb, username, passwd, nickname);
    }
}
