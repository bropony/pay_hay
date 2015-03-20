/// <reference path="rmi/rmimanager.ts" />
/// <reference path="rmi/rmiclient.ts" />
/// <reference path="rmi/rmidatastruct.ts" />

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
    var cb: LoginCB = new LoginCB();

    Rmi.Proxy.login(cb, "test", "test");
};
