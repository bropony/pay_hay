/// <reference path="../rmi/serialize.ts" />
/// <reference path="../rmi/rmimanager.ts" />
/// <reference path="../rmi/rmiclient.ts" />
/// <reference path="../user/usermanager.ts" />

module View {
    export module NewPost {
        export function onLoad() {
            User.UserManager.init();

            if (!User.UserManager.hasLogin()) {
                window.location.assign("/scene/login.html");
                return;
            }
        }

        class StartPostCbImpl extends Rmi.StartPostCallback {
            onResponse = function () {
            }

            onError = function (what: string, code: number) {
            }

            onTimeout = function () {
            }
        }

        export function newPost() {

        }
    }
} 