module Rmi {
    class StringCodec {
        static utf8ArrayToStr(array) {
            var out, i, len, c;
            var char2, char3;

            out = "";
            len = array.length;
            i = 0;
            while (i < len) {
                c = array[i++];
                switch (c >> 4) {
                    case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7:
                        // 0xxxxxxx
                        out += String.fromCharCode(c);
                        break;
                    case 12: case 13:
                        // 110x xxxx   10xx xxxx
                        char2 = array[i++];
                        out += String.fromCharCode(((c & 0x1F) << 6) | (char2 & 0x3F));
                        break;
                    case 14:
                        // 1110 xxxx  10xx xxxx  10xx xxxx
                        char2 = array[i++];
                        char3 = array[i++];
                        out += String.fromCharCode(((c & 0x0F) << 12) |
                            ((char2 & 0x3F) << 6) |
                            ((char3 & 0x3F) << 0));
                        break;
                }
            }

            return out;
        }

        static strToUtf8Array(str: string) {
            var utf8 = [];
            for (var i = 0; i < str.length; i++) {
                var charcode = str.charCodeAt(i);
                if (charcode < 0x80) utf8.push(charcode);
                else if (charcode < 0x800) {
                    utf8.push(0xc0 | (charcode >> 6),
                        0x80 | (charcode & 0x3f));
                }
                else if (charcode < 0xd800 || charcode >= 0xe000) {
                    utf8.push(0xe0 | (charcode >> 12),
                        0x80 | ((charcode >> 6) & 0x3f),
                        0x80 | (charcode & 0x3f));
                }
                // surrogate pair
                else {
                    i++;
                    // UTF-16 encodes 0x10000-0x10FFFF by
                    // subtracting 0x10000 and splitting the
                    // 20 bits of 0x0-0xFFFFF into two halves
                    charcode = 0x10000 + (((charcode & 0x3ff) << 10)
                        | (str.charCodeAt(i) & 0x3ff))
                    utf8.push(0xf0 | (charcode >> 18),
                        0x80 | ((charcode >> 12) & 0x3f),
                        0x80 | ((charcode >> 6) & 0x3f),
                        0x80 | (charcode & 0x3f));
                }
            }
            return utf8;
        }
    }

    export class EType {
        static BYTE = 1;
        static BOOL = 2;
        static SHORT = 3;
        static INT = 4;
        static LONG = 5;
        static FLOAT = 6;
        static DOUBLE = 7;
        static STRING = 8;
        static DATE = 9;
        static IMAGE = 10;
    }

    export class SimpleSerializer {
        private _buffer: ArrayBuffer;
        private _dataView: DataView;
        private _pos: number;

        constructor(data?: ArrayBuffer) {
            if (data) {
                this.initByData(data);
            }
            else {
                this.initBySize(1024);
            }
        }

        initBySize(size: number) {
            this._buffer = new ArrayBuffer(size);
            this._dataView = new DataView(this._buffer);
            this._pos = 0;
        }

        initByData(ab: ArrayBuffer) {
            this._buffer = ab;
            this._dataView = new DataView(this._buffer);
            this._pos = 0;
        }

        startToRead() {
            var ver = this.readByte();
            if (ver != 1) {
                throw "Serializing Version Error";
            }
        }

        startToWrite() {
            this.writeByte(1);
        }

        getBuffer(): ArrayBuffer {
            var res = this._buffer.slice(0, this._pos);
            return res;
        }

        increSize(offset: number) {
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
        }
        
        read(dataType: number): any | any[]{
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
        }

        write(dataType: number, data: any | any[]) {
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
        }

        readByte():number {
            if (this._pos >= this._buffer.byteLength) {
                throw "Serializing Error";
            }

            var res: number = this._dataView.getInt8(this._pos);
            this._pos += 1;

            return res;
        }

        writeByte(b: number) {
            this.increSize(1);

            this._dataView.setInt8(this._pos, b);
            this._pos += 1;
        }

        readUB(): number {
            if (this._pos >= this._buffer.byteLength) {
                throw "Serializing Error";
            }

            var res: number = this._dataView.getUint8(this._pos);
            this._pos += 1;

            return res;
        }

        writeUB(b: number) {
            this.increSize(1);

            this._dataView.setUint8(this._pos, b);
            this._pos += 1;
        }

        readBool():boolean {
            if (this._pos >= this._buffer.byteLength) {
                throw "Serializing Error";
            }

            var res: number = this.readByte();
            if (res != 0) {
                return true;
            }
            else {
                return false;
            }
        }

        writeBool(data: boolean) {
            var b: number = 0;
            if (data) {
                b = 1;
            }

            this.writeByte(b);
        }

        readShort(): number{
            if (this._pos >= this._buffer.byteLength) {
                throw "Serializing Error";
            }

            var res = this._dataView.getInt16(this._pos, true);
            this._pos += 2;

            return res;
        }

        writeShort(data: number) {
            this.increSize(2);

            this._dataView.setInt16(this._pos, data, true);
            this._pos += 2;
        }

        readInt(): number {
            if (this._pos >= this._buffer.byteLength) {
                throw "Serializing Error";
            }

            var res = this._dataView.getInt32(this._pos, true);
            this._pos += 4;
            return res;
        }

        writeInt(data: number) {
            this.increSize(4);
            this._dataView.setInt32(this._pos, data, true);
            this._pos += 4;
        }

        readLong(): number {
            if (this._pos >= this._buffer.byteLength) {
                throw "Serializing Error";
            }

            var res = this._dataView.getFloat64(this._pos, true);
            this._pos += 8;

            return res;
        }

        writeLong(data: number) {
            this.increSize(8);
            this._dataView.setFloat64(this._pos, data, true);
            this._pos += 8;
        }

        readFloat(): number {
            if (this._pos >= this._buffer.byteLength) {
                throw "Serializing Error";
            }

            var res = this._dataView.getFloat32(this._pos, true);
            this._pos += 4;

            return res;
        }

        writeFloat(data: number) {
            this.increSize(4);

            this._dataView.setFloat32(this._pos, data, true);

            this._pos += 4;
        }

        readDouble(): number {
            if (this._pos >= this._buffer.byteLength) {
                throw "Serializing Error";
            }

            var res = this._dataView.getFloat64(this._pos, true);
            this._pos += 4;
            return res;
        }

        writeDouble(data: number) {
            this.increSize(8);

            this._dataView.setFloat64(this._pos, data, true);

            this._pos += 8;
        }

        readString(): string {
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
        }

        writeString(data: string) {
            var uintArray = StringCodec.strToUtf8Array(data);

            this.writeInt(uintArray.length);
            for (var i = 0; i < uintArray.length; i++) {
                this.writeUB(uintArray[i]);
            }
        }

        readDate(): Date {
            if (this._pos >= this._buffer.byteLength) {
                throw "Serializing Error";
            }

            var mills = this.readLong();
            var res = new Date(mills);

            return res;
        }

        writeDate(dt: Date) {
            var mills = dt.getTime();
            this.writeLong(mills);
        }

        readImage(): ArrayBuffer {
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
        }

        writeImage(img: ArrayBuffer) {
            var size = img.byteLength;
            this.writeInt(size);

            var ai = new Uint8Array(img);
            for (var i = 0; i < size; i++) {
                //var b = ai.get(i);
                var b = ai[i];
                this.writeUB(b);
            }
        }

        encrypt() {
            if (this._pos == 0) {
                return;
            }
            var mask: number = 108;
            var byteArray: Int8Array = new Int8Array(this._buffer);

            var maxIdx: number = this._pos - 1;

            for (var i = 0; i <= maxIdx; i += 2)
            {
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
        }

        decrypt() {
            this._pos = this._buffer.byteLength;
            this.encrypt();
            this._pos = 0;
        }
    };
};
