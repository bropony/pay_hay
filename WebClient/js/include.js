/// <reference path="rmi/serialize.ts" />
/// <reference path="rmi/rmimanager.ts" />
/// <reference path="rmi/rmiclient.ts" />
/// <reference path="view/index.ts" />
var Main;
(function (Main) {
    function addScript(path) {
        var head = document.head;
        var script = document.createElement("script");
        script.src = path;
        head.appendChild(script);
    }
    function addCommonScripts() {
        addScript("/js/rmi/serialize.js");
        addScript("/js/rmi/rmimanager.js");
        addScript("/js/rmi/rmidatastruct.js");
        addScript("/js/rmi/rmiclient.js");
        addScript("/js/user/usermanager.js");
    }
    function initIndexHtmlScripts() {
        addCommonScripts();
        addScript("/js/view/postmanager.js");
        addScript("/js/view/index.js");
    }
    Main.initIndexHtmlScripts = initIndexHtmlScripts;
    function onIndexLoad() {
        View.Index.init();
        View.Index.loadPosts(true);
    }
    Main.onIndexLoad = onIndexLoad;
})(Main || (Main = {}));
//# sourceMappingURL=include.js.map