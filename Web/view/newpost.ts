/// <reference path="../rmi/rmidatastruct.ts" />
/// <reference path="../rmi/rmiclient.ts" />
/// <reference path="../rmi/rmimanager.ts" /> 
/// <reference path="viewmanager.ts" />

module View {
    var images = [];
    var imgIdx = 0;

    export var onNewPostLoad = function () {
        var account = ViewManager.getItem(ViewManager.keyAccount);
        if (!account) {
            window.location.href = "login.html";
        }

        images = [];
        imgIdx = 0;
    }

    export var addImage = function (){
        var file = document.getElementById("add-image")["files"][0];
        
        var reader = new FileReader();
        reader.onload = function (e) {
            var bb = reader.result;
            var uri = URL.createObjectURL(file);

            var divImg = document.getElementById("images");

            if (images.length > 0) {
                var hr = document.createElement("hr");
                divImg.appendChild(hr);
            }

            var img = document.createElement("img");
            img.src = uri;
            divImg.appendChild(img);

            images.push(bb);
        };

        reader.readAsArrayBuffer(file);
    }

    var uploadPostImage = function () {
        if (imgIdx >= images.length) {
            return;
        }

        var cb: UploadImgCBImpl = new UploadImgCBImpl();
        Rmi.Proxy.uploadPostImg(cb, ViewManager.getItem(ViewManager.keySessionKey), images[imgIdx], "Post Image");
        imgIdx += 1;
    }

    class EndPostCBImpl extends Rmi.EndPostCallback {
        onResponse = function (postId: number) {
            window.location.href = "index.html";
        }
    }

    class UploadImgCBImpl extends Rmi.UploadPostImgCallback {
        onResponse = function (imgId: number) {
            console.log("upload img success: " + imgId);

            if (imgId >= images.length) {
                var endCb = new EndPostCBImpl();
                Rmi.Proxy.endPost(endCb, ViewManager.getItem(ViewManager.keySessionKey));
            }
            else {
                uploadPostImage();
            }
        }

        onError = function (what: string, code: number) {
            alert("StartPost: " + what);
        }

        onTimeout = function () {
        }
    }

    class StartPostCBImpl extends Rmi.StartPostCallback {
        onResponse = function () {
            if (imgIdx < images.length) {
                uploadPostImage();
            }
        }

        onError = function (what: string, code: number) {
            alert("StartPost: " + what);
        }

        onTimeout = function () {
            alert("Network Timeout");
        }
    }

    export var newPost = function () {
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

        var cb = new StartPostCBImpl();
        Rmi.Proxy.startPost(cb, ViewManager.getItem(ViewManager.keySessionKey), title, content);
    }
} 
