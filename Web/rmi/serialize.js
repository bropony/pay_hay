var Rmi;
(function (Rmi) {
    var StringCodec = (function () {
        function StringCodec() {
        }
        StringCodec.utf8ArrayToStr = function (array) {
            var out, i, len, c;
            var char2, char3;
            out = "";
            len = array.length;
            i = 0;
            while (i < len) {
                c = array[i++];
                switch (c >> 4) {
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                        // 0xxxxxxx
                        out += String.fromCharCode(c);
                        break;
                    case 12:
                    case 13:
                        // 110x xxxx   10xx xxxx
                        char2 = array[i++];
                        out += String.fromCharCode(((c & 0x1F) << 6) | (char2 & 0x3F));
                        break;
                    case 14:
                        // 1110 xxxx  10xx xxxx  10xx xxxx
                        char2 = array[i++];
                        char3 = array[i++];
                        out += String.fromCharCode(((c & 0x0F) << 12) | ((char2 & 0x3F) << 6) | ((char3 & 0x3F) << 0));
                        break;
                }
            }
            return out;
        };
        StringCodec.strToUtf8Array = function (str) {
            var utf8 = [];
            for (var i = 0; i < str.length; i++) {
                var charcode = str.charCodeAt(i);
                if (charcode < 0x80)
                    utf8.push(charcode);
                else if (charcode < 0x800) {
                    utf8.push(0xc0 | (charcode >> 6), 0x80 | (charcode & 0x3f));
                }
                else if (charcode < 0xd800 || charcode >= 0xe000) {
                    utf8.push(0xe0 | (charcode >> 12), 0x80 | ((charcode >> 6) & 0x3f), 0x80 | (charcode & 0x3f));
                }
                else {
                    i++;
                    // UTF-16 encodes 0x10000-0x10FFFF by
                    // subtracting 0x10000 and splitting the
                    // 20 bits of 0x0-0xFFFFF into two halves
                    charcode = 0x10000 + (((charcode & 0x3ff) << 10) | (str.charCodeAt(i) & 0x3ff));
                    utf8.push(0xf0 | (charcode >> 18), 0x80 | ((charcode >> 12) & 0x3f), 0x80 | ((charcode >> 6) & 0x3f), 0x80 | (charcode & 0x3f));
                }
            }
            return utf8;
        };
        return StringCodec;
    })();
    var EType = (function () {
        function EType() {
        }
        EType.BYTE = 1;
        EType.BOOL = 2;
        EType.SHORT = 3;
        EType.INT = 4;
        EType.LONG = 5;
        EType.FLOAT = 6;
        EType.DOUBLE = 7;
        EType.STRING = 8;
        EType.DATE = 9;
        EType.IMAGE = 10;
        return EType;
    })();
    Rmi.EType = EType;
    var SimpleSerializer = (function () {
        function SimpleSerializer(data) {
            if (data) {
                this.initByData(data);
            }
            else {
                this.initBySize(1024);
            }
        }
        SimpleSerializer.prototype.initBySize = function (size) {
            this._buffer = new ArrayBuffer(size);
            this._dataView = new DataView(this._buffer);
            this._pos = 0;
        };
        SimpleSerializer.prototype.initByData = function (ab) {
            this._buffer = ab;
            this._dataView = new DataView(this._buffer);
            this._pos = 0;
        };
        SimpleSerializer.prototype.startToRead = function () {
            var ver = this.readByte();
            if (ver != 1) {
                throw "Serializing Version Error";
            }
        };
        SimpleSerializer.prototype.startToWrite = function () {
            this.writeByte(1);
        };
        SimpleSerializer.prototype.getBuffer = function () {
            var res = this._buffer.slice(0, this._pos);
            return res;
        };
        SimpleSerializer.prototype.increSize = function (offset) {
            var newPos = this._pos + offset;
            if (newPos > this._buffer.byteLength) {
                var newBuffer = new ArrayBuffer(newPos * 2);
                var srcBB = new Int8Array(this._buffer);
                var dstBB = new Int8Array(newBuffer);
                for (var i = 0; i <= this._pos; i++) {
                    dstBB[i] = srcBB[i];
                }
                this._buffer = newBuffer;
                this._dataView = new DataView(this._buffer);
            }
        };
        SimpleSerializer.prototype.read = function (dataType) {
            if (dataType == EType.BYTE) {
                return this.readByte();
            }
            if (dataType == EType.BOOL) {
                return this.readBool();
            }
            if (dataType == EType.SHORT) {
                return this.readShort();
            }
            if (dataType == EType.INT) {
                return this.readInt();
            }
            if (dataType == EType.LONG) {
                return this.readLong();
            }
            if (dataType == EType.FLOAT) {
                return this.readFloat();
            }
            if (dataType == EType.DOUBLE) {
                return this.readDouble();
            }
            if (dataType == EType.STRING) {
                return this.readString();
            }
            if (dataType == EType.DATE) {
                return this.readDate();
            }
            if (dataType == EType.IMAGE) {
                return this.readImage();
            }
            throw "[In SimpleSerializer.read] Unknow Data Type " + dataType;
        };
        SimpleSerializer.prototype.write = function (dataType, data) {
            if (dataType == EType.BYTE) {
                this.writeByte(data);
            }
            else if (dataType == EType.BOOL) {
                this.writeBool(data);
            }
            else if (dataType == EType.SHORT) {
                this.writeShort(data);
            }
            else if (dataType == EType.INT) {
                this.writeInt(data);
            }
            else if (dataType == EType.LONG) {
                this.writeLong(data);
            }
            else if (dataType == EType.FLOAT) {
                this.writeFloat(data);
            }
            else if (dataType == EType.DOUBLE) {
                this.writeDouble(data);
            }
            else if (dataType == EType.STRING) {
                this.writeString(data);
            }
            else if (dataType == EType.DATE) {
                this.writeDate(data);
            }
            else if (dataType == EType.IMAGE) {
                this.writeImage(data);
            }
            else {
                throw "[In SimpleSerializer.write] Unknow Data Type " + dataType;
            }
        };
        SimpleSerializer.prototype.readByte = function () {
            if (this._pos >= this._buffer.byteLength) {
                throw "Serializing Error";
            }
            var res = this._dataView.getInt8(this._pos);
            this._pos += 1;
            return res;
        };
        SimpleSerializer.prototype.writeByte = function (b) {
            this.increSize(1);
            this._dataView.setInt8(this._pos, b);
            this._pos += 1;
        };
        SimpleSerializer.prototype.readUB = function () {
            if (this._pos >= this._buffer.byteLength) {
                throw "Serializing Error";
            }
            var res = this._dataView.getUint8(this._pos);
            this._pos += 1;
            return res;
        };
        SimpleSerializer.prototype.writeUB = function (b) {
            this.increSize(1);
            this._dataView.setUint8(this._pos, b);
            this._pos += 1;
        };
        SimpleSerializer.prototype.readBool = function () {
            if (this._pos >= this._buffer.byteLength) {
                throw "Serializing Error";
            }
            var res = this.readByte();
            if (res != 0) {
                return true;
            }
            else {
                return false;
            }
        };
        SimpleSerializer.prototype.writeBool = function (data) {
            var b = 0;
            if (data) {
                b = 1;
            }
            this.writeByte(b);
        };
        SimpleSerializer.prototype.readShort = function () {
            if (this._pos >= this._buffer.byteLength) {
                throw "Serializing Error";
            }
            var res = this._dataView.getInt16(this._pos, true);
            this._pos += 2;
            return res;
        };
        SimpleSerializer.prototype.writeShort = function (data) {
            this.increSize(2);
            this._dataView.setInt16(this._pos, data, true);
            this._pos += 2;
        };
        SimpleSerializer.prototype.readInt = function () {
            if (this._pos >= this._buffer.byteLength) {
                throw "Serializing Error";
            }
            var res = this._dataView.getInt32(this._pos, true);
            this._pos += 4;
            return res;
        };
        SimpleSerializer.prototype.writeInt = function (data) {
            this.increSize(4);
            this._dataView.setInt32(this._pos, data, true);
            this._pos += 4;
        };
        SimpleSerializer.prototype.readLong = function () {
            if (this._pos >= this._buffer.byteLength) {
                throw "Serializing Error";
            }
            var res = this._dataView.getFloat64(this._pos, true);
            this._pos += 8;
            return res;
        };
        SimpleSerializer.prototype.writeLong = function (data) {
            this.increSize(8);
            this._dataView.setFloat64(this._pos, data, true);
            this._pos += 8;
        };
        SimpleSerializer.prototype.readFloat = function () {
            if (this._pos >= this._buffer.byteLength) {
                throw "Serializing Error";
            }
            var res = this._dataView.getFloat32(this._pos, true);
            this._pos += 4;
            return res;
        };
        SimpleSerializer.prototype.writeFloat = function (data) {
            this.increSize(4);
            this._dataView.setFloat32(this._pos, data, true);
            this._pos += 4;
        };
        SimpleSerializer.prototype.readDouble = function () {
            if (this._pos >= this._buffer.byteLength) {
                throw "Serializing Error";
            }
            var res = this._dataView.getFloat64(this._pos, true);
            this._pos += 4;
            return res;
        };
        SimpleSerializer.prototype.writeDouble = function (data) {
            this.increSize(8);
            this._dataView.setFloat64(this._pos, data, true);
            this._pos += 8;
        };
        SimpleSerializer.prototype.readString = function () {
            if (this._pos >= this._buffer.byteLength) {
                throw "Serializing Error";
            }
            var size = this.readInt();
            var uintArray = [];
            for (var i = 0; i < size; i++) {
                uintArray.push(this.readUB());
            }
            var res = StringCodec.utf8ArrayToStr(uintArray);
            return res;
        };
        SimpleSerializer.prototype.writeString = function (data) {
            var uintArray = StringCodec.strToUtf8Array(data);
            this.writeInt(uintArray.length);
            for (var i = 0; i < uintArray.length; i++) {
                this.writeUB(uintArray[i]);
            }
        };
        SimpleSerializer.prototype.readDate = function () {
            if (this._pos >= this._buffer.byteLength) {
                throw "Serializing Error";
            }
            var mills = this.readLong();
            var res = new Date(mills);
            return res;
        };
        SimpleSerializer.prototype.writeDate = function (dt) {
            var mills = dt.getTime();
            this.writeLong(mills);
        };
        SimpleSerializer.prototype.readImage = function () {
            if (this._pos >= this._buffer.byteLength) {
                throw "Serializing Error";
            }
            var size = this.readInt();
            var ab = new ArrayBuffer(size);
            var ai = new Uint8Array(ab);
            for (var i = 0; i < size; i++) {
                //ai.set(i, this.readUB());
                ai[i] = this.readUB();
            }
            return ab;
        };
        SimpleSerializer.prototype.writeImage = function (img) {
            var size = img.byteLength;
            this.writeInt(size);
            var ai = new Uint8Array(img);
            for (var i = 0; i < size; i++) {
                //var b = ai.get(i);
                var b = ai[i];
                this.writeUB(b);
            }
        };
        SimpleSerializer.prototype.encrypt = function () {
            if (this._pos == 0) {
                return;
            }
            var mask = 108;
            var byteArray = new Int8Array(this._buffer);
            var maxIdx = this._pos - 1;
            for (var i = 0; i <= maxIdx; i += 2) {
                if (i == maxIdx) {
                    byteArray[i] ^= mask;
                    return;
                }
                var bi = byteArray[i];
                var bj = byteArray[i + 1];
                bi ^= mask;
                bj ^= mask;
                byteArray[i] = bj;
                byteArray[i + 1] = bi;
            }
        };
        SimpleSerializer.prototype.decrypt = function () {
            this._pos = this._buffer.byteLength;
            this.encrypt();
            this._pos = 0;
        };
        return SimpleSerializer;
    })();
    Rmi.SimpleSerializer = SimpleSerializer;
    ;
})(Rmi || (Rmi = {}));
;
//# sourceMappingURL=serialize.js.map