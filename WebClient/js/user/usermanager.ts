/// <reference path="../rmi/serialize.ts" />
/// <reference path="../rmi/rmimanager.ts" />
/// <reference path="../rmi/rmiclient.ts" />

module User {
    class _UserManager_Cls_ {
        private _userId: number;
        private _account: string;
        private _nickname: string;
        private _passwd: string;
        private _sessionKey: string;
        private _avatar: ArrayBuffer;

        public keyUserId = "userId";
        public keyAccount = "account";
        public keyNickname = "nickname";
        public keyPasswd = "passwd";
        public keySessionKey = "sessionKey";
        public keyAvatar = "avatar";

        getItem(key: string) {
            return localStorage.getItem(key);
        }

        setItem(key: string, value: any) {
            localStorage.setItem(key, value);
        }

        get userId():number {
            return this._userId;
        }

        set userId(uid: number) {
            this._userId = uid;
            this.setItem(this.keyUserId, uid);
        }
        
        get account(): string {
            return this._account;
        }

        set account(act: string) {
            this._account = act;
            this.setItem(this.keyAccount, act);
        }

        get nickname(): string {
            return this._nickname;
        }

        set nickname(nick: string) {
            this._nickname = nick;
            this.setItem(this.keyNickname, nick);
        }

        get passwd(): string {
            return this._passwd;
        }

        set passwd(pwd: string) {
            this._passwd = pwd;
            this.setItem(this.keyPasswd, pwd);
        }

        get sessionKey(): string {
            return this._sessionKey;
        }

        set sessionKey(sk: string) {
            this._sessionKey = sk;
            this.setItem(this.keySessionKey, sk);
        }

        get avatar(): ArrayBuffer{
            return this._avatar;
        }

        set avatar(at: ArrayBuffer) {
            this._avatar = at;
            this.setItem(this.keyAvatar, at);
        }

        init() {
            this._account = this.getItem(this.keyAccount);
            this._userId = this.getItem(this.keyUserId);
            this._nickname = this.getItem(this.keyNickname);
            this._passwd = this.getItem(this.keyPasswd);
            this._sessionKey = this.getItem(this.keySessionKey);
            this._avatar = this.getItem(this.keyAvatar);
        }

        clear() {
            this.userId = 0;
            this.account = "";
            this.nickname = "";
            this.passwd = "";
            this.avatar = null;
            this.sessionKey = "";
        }
    }

    export var UserManager = new _UserManager_Cls_();
    UserManager.init();
}
