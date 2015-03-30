/// <reference path="../rmi/rmidatastruct.ts" />
/// <reference path="../rmi/rmiclient.ts" />
/// <reference path="../rmi/rmimanager.ts" /> 
/// <reference path="viewmanager.ts" />

module View {
    class SignupCBImpl extends Rmi.SignupCallback {
        onResponse = function (userInfo: Rmi.SLoginReturn) {
            ViewManager.setItem(ViewManager.keyUserId, userInfo.userId);
            ViewManager.setItem(ViewManager.keyAccount, this.account);
            ViewManager.setItem(ViewManager.keyPasswd, this.passwd);
            ViewManager.setItem(ViewManager.keyNickname, userInfo.nickname);
            ViewManager.setItem(ViewManager.keySessionKey, userInfo.sessionKey);

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

        if (passwd != repasswd) {
            alert("Two passwords you input are equivelant!");
            return;
        }

        var cb = new SignupCBImpl();
        cb["account"] = username;
        cb["passwd"] = passwd;

        Rmi.Proxy.signup(cb, username, passwd, nickname);
    }
}
