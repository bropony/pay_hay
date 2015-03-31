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
            this.keyAvatar = "avatar";
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
            if (!elem) {
                return;
            }
            if (this.nickname) {
                elem.innerHTML = '';
                var hi = document.createElement("a");
                hi.innerHTML = "Hi " + this.nickname;
                hi.href = "my.html";
                hi.id = "a-hi";
                elem.appendChild(hi);
                var logout = document.createElement("a");
                logout.innerHTML = "Logout";
                logout.href = "logout.html";
                logout.id = "a-logout";
                //logout.addEventListener("click", ViewManager.onLogout);
                elem.appendChild(logout);
            }
            else {
                elem.innerHTML = '';
                var login = document.createElement("a");
                login.innerHTML = "Login";
                login.href = "login.html";
                login.id = "a-login";
                elem.appendChild(login);
                var signup = document.createElement("a");
                signup.innerHTML = "Signup";
                signup.href = "signup.html";
                signup.id = "a-signup";
                elem.appendChild(signup);
            }
        };
        _ViewManager_cls.prototype.onMine = function () {
            alert("onMine");
        };
        _ViewManager_cls.prototype.onLogout = function () {
            View.ViewManager.setItem(View.ViewManager.keyAccount, '');
            View.ViewManager.setItem(View.ViewManager.keyNickname, '');
            View.ViewManager.setItem(View.ViewManager.keyPasswd, '');
            View.ViewManager.setItem(View.ViewManager.keySessionKey, '');
            window.location.href = "index.html";
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
    View.ViewManager.init();
})(View || (View = {}));
//# sourceMappingURL=viewmanager.js.map