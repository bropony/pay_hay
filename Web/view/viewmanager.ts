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

        private keyUserId = "userId";
        private keyAccount = "account";
        private keyNickname = "nickname";
        private keyPasswd = "passwd";
        private keySessionKey = "sessionKey";

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
            if (this.nickname) {
                elem.innerHTML = '';
                var hi = document.createElement("code");
                hi.innerHTML = "Hi " + this.nickname;
                hi.addEventListener("click", ViewManager.onMine);
                hi.id = "a-hi";
                elem.appendChild(hi);

                var logout = document.createElement("code");
                logout.innerHTML = "Logout";
                logout.addEventListener("click", ViewManager.onLogout);
                logout.id = "a-logout";
                elem.appendChild(logout);
            }
            else {
                elem.innerHTML = '';

                var login = document.createElement("code");
                login.innerHTML = "Login";
                login.addEventListener("click", ViewManager.onLogin);
                login.id = "a-login";
                elem.appendChild(login);

                var signup = document.createElement("code");
                signup.innerHTML = "Signup";
                signup.addEventListener("click", ViewManager.onSignup);
                signup.id = "a-signup";
                elem.appendChild(signup);
            }

        }

        onMine() {
            alert("onMine");
        }
        
        onLogout() {
            alert("onLogout");
        }

        onLogin() {
            var elem = document.getElementById("login-popup");
        }

        onSignup() {
            alert("onSignup");
        }
    }

    export var ViewManager: _ViewManager_cls = new _ViewManager_cls();
}