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
                        out += String.fromCharCode(c);
                        break;
                    case 12:
                    case 13:
                        char2 = array[i++];
                        out += String.fromCharCode(((c & 0x1F) << 6) | (char2 & 0x3F));
                        break;
                    case 14:
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
                    charcode = 0x10000 + (((charcode & 0x3ff) << 10) | (str.charCodeAt(i) & 0x3ff));
                    utf8.push(0xf0 | (charcode >> 18), 0x80 | ((charcode >> 12) & 0x3f), 0x80 | ((charcode >> 6) & 0x3f), 0x80 | (charcode & 0x3f));
                }
            }
            return utf8;
        };
        return StringCodec;
    })();
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
            if (dataType == "byte") {
                return this.readByte();
            }
            if (dataType == "bool") {
                return this.readBool();
            }
            if (dataType == "short") {
                return this.readShort();
            }
            if (dataType == "int") {
                return this.readInt();
            }
            if (dataType == "long") {
                return this.readLong();
            }
            if (dataType == "float") {
                return this.readFloat();
            }
            if (dataType == "double") {
                return this.readDouble();
            }
            if (dataType == "string") {
                return this.readString();
            }
            if (dataType == "date") {
                return this.readDate();
            }
            if (dataType == "image") {
                return this.readImage();
            }
            throw "InRead: Unknow Data Type " + dataType;
        };
        SimpleSerializer.prototype.write = function (dataType, data) {
            if (dataType == "byte") {
                this.writeByte(data);
            }
            if (dataType == "bool") {
                this.writeBool(data);
            }
            if (dataType == "short") {
                this.writeShort(data);
            }
            if (dataType == "int") {
                this.writeInt(data);
            }
            if (dataType == "long") {
                this.writeLong(data);
            }
            if (dataType == "float") {
                this.writeFloat(data);
            }
            if (dataType == "double") {
                this.writeDouble(data);
            }
            if (dataType == "string") {
                this.writeString(data);
            }
            if (dataType == "date") {
                this.writeDate(data);
            }
            if (dataType == "image") {
                this.writeString(data);
            }
            throw "InRead: Unknow Data Type " + dataType;
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
            var secs = this.readLong();
            var res = new Date(secs * 1000);
            return res;
        };
        SimpleSerializer.prototype.writeDate = function (dt) {
            var secs = dt.getTime() / 1000;
            this.writeLong(secs);
        };
        SimpleSerializer.prototype.readImage = function () {
            if (this._pos >= this._buffer.byteLength) {
                throw "Serializing Error";
            }
            var size = this.readInt();
            var ab = new ArrayBuffer(size);
            var ai = new Uint8Array(ab);
            for (var i = 0; i < size; i++) {
                ai.set(i, this.readUB());
            }
            return ab;
        };
        SimpleSerializer.prototype.writeImage = function (img) {
            var size = img.byteLength;
            this.writeInt(size);
            var ai = new Uint8Array(img);
            for (var i = 0; i < size; i++) {
                this.writeUB(ai.get(i));
            }
        };
        return SimpleSerializer;
    })();
    Rmi.SimpleSerializer = SimpleSerializer;
    ;
})(Rmi || (Rmi = {}));
;
