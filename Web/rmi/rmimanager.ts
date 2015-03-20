//RmiManager
/// <reference path="serialize.ts" />

module Rmi {
    export interface CallbackBase {
        __onResponse: (__is: SimpleSerializer) => void;
        __onError: (what: string, code: number) => void;
        __onTimeout: () => void;
    }; 

    interface OutGoing {
        __os: SimpleSerializer;
        __msgId: number;
        __cb: CallbackBase;
    }

    class _RmiManager_cls {
        private _url: string;
        private _ws: WebSocket;
        private _cbs: { [index: number]: CallbackBase };
        private _ogs: OutGoing[];

        constructor(wsUrl: string) {
            this._url = wsUrl;
            this._ws = null;

            this._cbs = {};
            this._ogs = [];
        }

        isOpen(): boolean {
            if (this._ws && this._ws.readyState == WebSocket.OPEN) {
                return true;
            }

            return false;
        }

        connect(): void {
            if (this.isOpen()) {
                return;
            }

            if (this._ws && this._ws.readyState == WebSocket.CONNECTING) {
                return;
            }

            this._ws = new WebSocket(this._url);

            this._ws.onopen = this.onOpen;
            this._ws.onclose = this.onClose;
            this._ws.onerror = this.onError;
            this._ws.onmessage = this.onMessage;
        }

        onOpen(e: Event) {
            console.log("Connected to Server");
        }

        onClose(e: CloseEvent) {
            console.log("Connection Closed: %d-%s", e.code, e.reason);
        }

        onError(e: ErrorEvent) {
            console.log("Connection Error: %s", e.message)
        }

        onResponse(buffer: ArrayBuffer) {
            var __is: SimpleSerializer = new SimpleSerializer(buffer);
            __is.startToRead();
            var msgId: number = __is.readInt();
            var isOk: boolean = __is.readBool();

            console.log("Msg is %d", msgId);
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
        }

        onMessage(e: MessageEvent) {
            if (typeof (e.data) != 'string') {

                if (e.data instanceof Blob) {
                    var reader = new FileReader();
                    reader.onload = function () {
                        var buffer = reader.result;

                        RmiManager.onResponse(buffer);
                    };
                    reader.readAsArrayBuffer(e.data);
                }
                else {
                    this.onResponse(e.data);
                }
            }
            else {
                console.log("onMessage: unprocessed data");
            }
        }

        invoke(__msgId: number, __os: SimpleSerializer, __cb: CallbackBase) {
            __cb["__pushDt"] = new Date();

            var og = { __msgId: __msgId, __os: __os, __cb: __cb };
            this._ogs.push(og);
        }

        sendout() {
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
        }
    }

    export var RmiManager: _RmiManager_cls = new _RmiManager_cls("ws://112.74.102.141:9600");

    function schedule() {
        RmiManager.sendout();
    }

    setInterval(schedule, 30);
}
