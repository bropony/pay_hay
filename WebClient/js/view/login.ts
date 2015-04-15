/// <reference path="../rmi/serialize.ts" />
/// <reference path="../rmi/rmimanager.ts" />
/// <reference path="../rmi/rmiclient.ts" />
/// <reference path="../user/usermanager.ts" />
/// <reference path="util.ts" />

module View {
    var userManager = User.UserManager;

    class LoginCBImpl extends Rmi.LoginCallback {
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
        }

        onError = function (what: string, code: number) {
            alert("Login Error: " + what);
            console.log("What: %s, code:%d", what, code);
        }

        onTimeout = function () {
            alert("Login Timeout. Please Retry!");
        }
    }

    export var login = function () {
        var username = document.getElementById("username")["value"];
        var passwd = document.getElementById("password")["value"];

        if (Util.alertEmptyString(username, "请填写账号")) {
            return;
        }

        if (Util.alertEmptyString(passwd, "请填写密码")) {
            return;
        }

        console.log("A:%s, p:%s", username, passwd);
        var cb = new LoginCBImpl(username, passwd);
        Rmi.Proxy.login(cb, username, passwd);
    }
}
