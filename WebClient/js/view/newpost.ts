/// <reference path="../rmi/serialize.ts" />
/// <reference path="../rmi/rmimanager.ts" />
/// <reference path="../rmi/rmiclient.ts" />
/// <reference path="../user/usermanager.ts" />

module View {
    export module NewPost {

        var images = [];
        var uploadedImgNum = 0;

        export function onLoad() {
            User.UserManager.init();

            if (!User.UserManager.hasLogin()) {
                window.location.assign("/scene/login.html");
                return;
            }

            images = [];
            uploadedImgNum = 0;
        }

        export var addImage = function () {
            var file = document.getElementById("add-image")["files"][0];

            var reader = new FileReader();
            reader.onload = function (e) {
                var bb = reader.result;
                var uri = URL.createObjectURL(file);

                var divImg = document.getElementById("images");

                var img = document.createElement("img");
                img.className = "new-post-img";
                img.src = uri;
                divImg.appendChild(img);

                images.push(bb);
            };

            reader.readAsArrayBuffer(file);
        }

        class UploadImgCbImpl extends Rmi.UploadPostImgExCallback {
            onResponse = function (imgId: number) {
                console.log("Upload Img Success: %d", imgId);
                uploadedImgNum += 1;

                if (uploadedImgNum == images.length) {
                    window.location.assign("/index.html");
                }
            }

            onError = function (what: string, code: number) {
                console.log("Upload Img Error: %s, %d", what, code);
            }

            onTimeout = function () {
                console.log("Upload Img Timeout");
            }
        }

        class StartPostCbImpl extends Rmi.StartPostExCallback {
            onResponse = function (postId: number) {
                for (var idx: number = 0; idx < images.length; ++idx) {
                    var cb = new UploadImgCbImpl();
                    Rmi.Proxy.uploadPostImgEx(cb, User.UserManager.sessionKey, images[idx], "Web Image", postId, idx);
                }
            }

            onError = function (what: string, code: number) {
                console.log("Start Post Error: %s, %d", what, code);
            }

            onTimeout = function () {
                console.log("Start Post Timeout");
            }
        }

        export function newPost() {
            if (images.length <= 0) {
                alert("Please Add At Least One Image");
                return;
            }

            var title = document.getElementById("title")["value"];
            var content = document.getElementById("details")["value"];
            if (!title) {
                alert("Please Add a title");
                return;
            }

            var cb = new StartPostCbImpl();
            Rmi.Proxy.startPostEx(cb, User.UserManager.sessionKey, title, content, images.length);
        }
    }
} 