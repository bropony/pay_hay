/// <reference path="rmi/rmimanager.ts" />
/// <reference path="rmi/rmiclient.ts" />
/// <reference path="rmi/rmidatastruct.ts" />
/// <reference path="view/viewmanager.ts" />

class LoginCB extends Rmi.LoginCallback {
    onResponse = function (userInfo: Rmi.SLoginReturn): void {
        console.log("onResponse: " + userInfo.sessionKey);
    };

    onError = function (what: string, code: number): void {
        console.log("onError: " + what);
    }

    onTimeout = function (): void {
        console.log("Timeout");
    }
}

window.onload = () => {

    var elm = document.getElementById("content");

    for (var i = 0; i < 200; i++) {
        elm.innerHTML += "I: " + i + "<br />";
        //document.writeln("I: " + i + "<br />");
    }

    var cb: LoginCB = new LoginCB();
    Rmi.Proxy.login(cb, "test", "test");
    View.ViewManager.init();
};
