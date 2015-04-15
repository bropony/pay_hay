/// <reference path="../rmi/serialize.ts" />
/// <reference path="../rmi/rmimanager.ts" />
/// <reference path="../rmi/rmiclient.ts" />
var User;
(function (User) {
    var _UserManager_Cls_ = (function () {
        function _UserManager_Cls_() {
            this.keyUserId = "userId";
            this.keyAccount = "account";
            this.keyNickname = "nickname";
            this.keyPasswd = "passwd";
            this.keySessionKey = "sessionKey";
            this.keyAvatar = "avatar";
        }
        _UserManager_Cls_.prototype.getItem = function (key) {
            return localStorage.getItem(key);
        };
        _UserManager_Cls_.prototype.setItem = function (key, value) {
            localStorage.setItem(key, value);
        };
        Object.defineProperty(_UserManager_Cls_.prototype, "userId", {
            get: function () {
                return this._userId;
            },
            set: function (uid) {
                this._userId = uid;
                this.setItem(this.keyUserId, uid);
            },
            enumerable: true,
            configurable: true
        });
        Object.defineProperty(_UserManager_Cls_.prototype, "account", {
            get: function () {
                return this._account;
            },
            set: function (act) {
                this._account = act;
                this.setItem(this.keyAccount, act);
            },
            enumerable: true,
            configurable: true
        });
        Object.defineProperty(_UserManager_Cls_.prototype, "nickname", {
            get: function () {
                return this._nickname;
            },
            set: function (nick) {
                this._nickname = nick;
                this.setItem(this.keyNickname, nick);
            },
            enumerable: true,
            configurable: true
        });
        Object.defineProperty(_UserManager_Cls_.prototype, "passwd", {
            get: function () {
                return this._passwd;
            },
            set: function (pwd) {
                this._passwd = pwd;
                this.setItem(this.keyPasswd, pwd);
            },
            enumerable: true,
            configurable: true
        });
        Object.defineProperty(_UserManager_Cls_.prototype, "sessionKey", {
            get: function () {
                return this._sessionKey;
            },
            set: function (sk) {
                this._sessionKey = sk;
                this.setItem(this.keySessionKey, sk);
            },
            enumerable: true,
            configurable: true
        });
        Object.defineProperty(_UserManager_Cls_.prototype, "avatar", {
            get: function () {
                return this._avatar;
            },
            set: function (at) {
                this._avatar = at;
                this.setItem(this.keyAvatar, at);
            },
            enumerable: true,
            configurable: true
        });
        _UserManager_Cls_.prototype.init = function () {
            this._account = this.getItem(this.keyAccount);
            this._userId = this.getItem(this.keyUserId);
            this._nickname = this.getItem(this.keyNickname);
            this._passwd = this.getItem(this.keyPasswd);
            this._sessionKey = this.getItem(this.keySessionKey);
            this._avatar = this.getItem(this.keyAvatar);
        };
        _UserManager_Cls_.prototype.clear = function () {
            this.userId = 0;
            this.account = "";
            this.nickname = "";
            this.passwd = "";
            this.avatar = null;
            this.sessionKey = "";
        };
        return _UserManager_Cls_;
    })();
    User.UserManager = new _UserManager_Cls_();
    User.UserManager.init();
})(User || (User = {}));
//# sourceMappingURL=usermanager.js.map