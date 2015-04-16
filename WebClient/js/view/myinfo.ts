/// <reference path="../rmi/serialize.ts" />
/// <reference path="../rmi/rmimanager.ts" />
/// <reference path="../rmi/rmiclient.ts" />
/// <reference path="postmanager.ts" />
/// <reference path="../user/usermanager.ts" />

module View {
    var userManager = User.UserManager;

    export module MyInfo {
        export function onLoad() {
            if (!userManager.hasLogin()) {
                window.location.assign("/scene/login.html");
                return;
            }

            if (userManager.avatarImgId > 0) {
                var imgUrl = PostManager.getImgUrl(userManager.avatarImgId);
                document.getElementById("avatar")["src"] = imgUrl;
            }

            document.getElementById("account").innerHTML = userManager.account;
            document.getElementById("nickname").innerHTML = userManager.nickname;
        }

        class ChangeAvatarCbImpl extends Rmi.ChangeAvatarCallback {
            onResponse = function (avatarImgId: number) {
                console.log("Avatar changed");
            }

            onError = function (what: string, code: number) {
                console.log("Change avatar error: %s, %d", what, code);
            }

            onTimeout = function () {
                console.log("Change avatar timeout");
            }
        }

        export function avatarSelected() {
            var file = document.getElementById('avatar-selector')["files"][0];
            var oldSrc = document.getElementById("avatar")["src"];

            var reader = new FileReader();
            reader.onload = function (e) {
                var bb = reader.result;
                var uri = URL.createObjectURL(file);
                document.getElementById("avatar")["src"] = uri;

                if (!confirm("确定要修改头像吗？")) {
                    document.getElementById("avatar")["src"] = oldSrc;
                    return;
                }

                Rmi.Proxy.changeAvatar(new ChangeAvatarCbImpl(), userManager.sessionKey, bb);
            };

            reader.readAsArrayBuffer(file);
        }
    }
} 