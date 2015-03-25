/// <reference path="../rmi/rmiclient.ts" />
/// <reference path="../rmi/rmidatastruct.ts" />
/// <reference path="../rmi/rmimanager.ts" />
var View;
(function (View) {
    var _ViewManager_cls = (function () {
        function _ViewManager_cls() {
            this.keyUserId = "userId";
            this.keyAccount = "account";
            this.keyNickname = "nickname";
            this.keyPasswd = "passwd";
            this.keySessionKey = "sessionKey";
        }
        _ViewManager_cls.prototype.getItem = function (key) {
            return localStorage.getItem(key);
        };
        _ViewManager_cls.prototype.setItem = function (key, value) {
            localStorage.setItem(key, value);
        };
        _ViewManager_cls.prototype.init = function () {
            this.userId = this.getItem(this.keyUserId);
            this.account = this.getItem(this.keyAccount);
            this.nickname = this.getItem(this.keyNickname);
            this.passwd = this.getItem(this.keyPasswd);
            this.sessionKey = this.getItem(this.keySessionKey);
            var elem = document.getElementById("user-entrance");
            if (this.nickname) {
                elem.innerHTML = '';
                var hi = document.createElement("code");
                hi.innerHTML = "Hi " + this.nickname;
                hi.addEventListener("click", View.ViewManager.onMine);
                hi.id = "a-hi";
                elem.appendChild(hi);
                var logout = document.createElement("code");
                logout.innerHTML = "Logout";
                logout.addEventListener("click", View.ViewManager.onLogout);
                logout.id = "a-logout";
                elem.appendChild(logout);
            }
            else {
                elem.innerHTML = '';
                var login = document.createElement("code");
                login.innerHTML = "Login";
                login.addEventListener("click", View.ViewManager.onLogin);
                login.id = "a-login";
                elem.appendChild(login);
                var signup = document.createElement("code");
                signup.innerHTML = "Signup";
                signup.addEventListener("click", View.ViewManager.onSignup);
                signup.id = "a-signup";
                elem.appendChild(signup);
            }
        };
        _ViewManager_cls.prototype.onMine = function () {
            alert("onMine");
        };
        _ViewManager_cls.prototype.onLogout = function () {
            alert("onLogout");
        };
        _ViewManager_cls.prototype.onLogin = function () {
            var elem = document.getElementById("login-popup");
        };
        _ViewManager_cls.prototype.onSignup = function () {
            alert("onSignup");
        };
        return _ViewManager_cls;
    })();
    View.ViewManager = new _ViewManager_cls();
})(View || (View = {}));
//# sourceMappingURL=viewmanager.js.map