//RmiManager
/// <reference path="serialize.ts" />
var Rmi;
(function (Rmi) {
    ;
    var _RmiManager_cls = (function () {
        function _RmiManager_cls(wsUrl) {
            this._url = wsUrl;
            this._ws = null;
            this._cbs = {};
            this._ogs = [];
        }
        _RmiManager_cls.prototype.isOpen = function () {
            if (this._ws && this._ws.readyState == WebSocket.OPEN) {
                return true;
            }
            return false;
        };
        _RmiManager_cls.prototype.connect = function () {
            if (this.isOpen()) {
                return;
            }
            if (this._ws && this._ws.readyState == WebSocket.CONNECTING) {
                return;
            }
            this._ws = new WebSocket(this._url);
            this._ws.binaryType = "arraybuffer";
            this._ws.onopen = this.onOpen;
            this._ws.onclose = this.onClose;
            this._ws.onerror = this.onError;
            this._ws.onmessage = this.onMessage;
        };
        _RmiManager_cls.prototype.onOpen = function (e) {
            console.log("Connected to Server");
        };
        _RmiManager_cls.prototype.onClose = function (e) {
            console.log("Connection Closed: %d-%s", e.code, e.reason);
        };
        _RmiManager_cls.prototype.onError = function (e) {
            console.log("Connection Error: %s", e.message);
        };
        _RmiManager_cls.prototype.onResponse = function (buffer) {
            var __is = new Rmi.SimpleSerializer(buffer);
            __is.decrypt();
            __is.startToRead();
            var msgId = __is.readInt();
            var isOk = __is.readBool();
            var __cb = this._cbs[msgId];
            if (null == __cb) {
                return;
            }
            if (isOk) {
                console.log("%d is Ok", msgId);
                __cb.__onResponse(__is);
            }
            else {
                console.log("%d is not Ok", msgId);
                __cb.__onError(__is.readString(), __is.readInt());
            }
            delete this._cbs[msgId];
        };
        _RmiManager_cls.prototype.onMessage = function (e) {
            if (typeof (e.data) != 'string') {
                if (e.data instanceof Blob) {
                    var reader = new FileReader();
                    reader.onload = function () {
                        var buffer = reader.result;
                        Rmi.RmiManager.onResponse(buffer);
                    };
                    reader.readAsArrayBuffer(e.data);
                }
                else {
                    Rmi.RmiManager.onResponse(e.data);
                }
            }
            else {
                console.log("onMessage: unprocessed data");
            }
        };
        _RmiManager_cls.prototype.invoke = function (__msgId, __os, __cb) {
            __cb["__pushDt"] = new Date();
            var og = { __msgId: __msgId, __os: __os, __cb: __cb };
            this._ogs.push(og);
        };
        _RmiManager_cls.prototype.sendout = function () {
            if (this._ogs.length <= 0) {
                return;
            }
            if (!this.isOpen()) {
                this.connect();
                return;
            }
            while (this._ogs.length > 0) {
                if (!this.isOpen()) {
                    break;
                }
                var og = this._ogs.shift();
                og.__os.encrypt();
                this._cbs[og.__msgId] = og.__cb;
                this._ws.send(og.__os.getBuffer());
            }
            var now = new Date();
            for (var msgId in this._cbs) {
                var cb = this._cbs[msgId];
                var pushDt = cb["__pushDt"];
                var diff = now.getTime() - pushDt.getTime();
                if (diff > 5000) {
                    cb.__onTimeout();
                    delete this._cbs[msgId];
                }
            }
        };
        return _RmiManager_cls;
    })();
    Rmi.RmiManager = new _RmiManager_cls("ws://112.74.102.141:9600");
    function schedule() {
        Rmi.RmiManager.sendout();
    }
    setInterval(schedule, 30);
})(Rmi || (Rmi = {}));
//# sourceMappingURL=rmimanager.js.map