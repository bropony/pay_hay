/// <reference path="../rmi/rmiclient.ts" />
/// <reference path="../rmi/rmidatastruct.ts" />
/// <reference path="../rmi/rmimanager.ts" />

module View {
    class _ViewManager_cls {
        private userId: number;
        private account: string;
        private nickname: string;
        private passwd: string;
        private sessionKey: string;
        private avatar: ArrayBuffer;

        public keyUserId = "userId";
        public keyAccount = "account";
        public keyNickname = "nickname";
        public keyPasswd = "passwd";
        public keySessionKey = "sessionKey";
        public keyAvatar = "avatar";

        constructor() {
        }

        getItem(key: string) {
            return localStorage.getItem(key);
        }

        setItem(key: string, value: any) {
            localStorage.setItem(key, value);
        }

        init() {
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

        }

        onMine() {
            alert("onMine");
        }
        
        onLogout() {
            ViewManager.setItem(ViewManager.keyAccount, '');
            ViewManager.setItem(ViewManager.keyNickname, '');
            ViewManager.setItem(ViewManager.keyPasswd, '');
            ViewManager.setItem(ViewManager.keySessionKey, '');

            window.location.href = "index.html";
        }

        onLogin() {
            var elem = document.getElementById("login-popup");
        }

        onSignup() {
            alert("onSignup");
        }
    }

    export var ViewManager: _ViewManager_cls = new _ViewManager_cls();
    ViewManager.init();
}