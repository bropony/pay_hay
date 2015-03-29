﻿/// <reference path="../rmi/rmidatastruct.ts" />
/// <reference path="../rmi/rmiclient.ts" />
/// <reference path="../rmi/rmimanager.ts" /> 
/// <reference path="viewmanager.ts" />

module View {
    class LoginCBImpl extends Rmi.LoginCallback {
        onResponse = function (userInfo: Rmi.SLoginReturn) {
            alert("login success");
            ViewManager.setItem(ViewManager.keyUserId, userInfo.userId);
            ViewManager.setItem(ViewManager.keyAccount, this.account);
            ViewManager.setItem(ViewManager.keyPasswd, this.passwd);
            ViewManager.setItem(ViewManager.keyNickname, userInfo.nickname);
            ViewManager.setItem(ViewManager.keySessionKey, userInfo.sessionKey);

            console.log("Login Success");
            //document.body.innerHTML = "Login Success";
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

        console.log("A:%s, p:%s", username, passwd);
        var cb = new LoginCBImpl();
        Rmi.Proxy.login(cb, username, passwd);

        alert("zzzzzzzzzzzzzzz");
    }
};