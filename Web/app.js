/// <reference path="rmi/rmimanager.ts" />
/// <reference path="rmi/rmiclient.ts" />
/// <reference path="rmi/rmidatastruct.ts" />
var __extends = this.__extends || function (d, b) {
    for (var p in b) if (b.hasOwnProperty(p)) d[p] = b[p];
    function __() { this.constructor = d; }
    __.prototype = b.prototype;
    d.prototype = new __();
};
var LoginCB = (function (_super) {
    __extends(LoginCB, _super);
    function LoginCB() {
        _super.apply(this, arguments);
        this.onResponse = function (userInfo) {
            console.log("onResponse: " + userInfo.sessionKey);
        };
        this.onError = function (what, code) {
            console.log("onError: " + what);
        };
        this.onTimeout = function () {
            console.log("Timeout");
        };
    }
    return LoginCB;
})(Rmi.LoginCallback);
window.onload = function () {
    var cb = new LoginCB();
    Rmi.Proxy.login(cb, "test", "test");
};
//# sourceMappingURL=app.js.map