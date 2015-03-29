/// <reference path="rmi/rmimanager.ts" />
/// <reference path="rmi/rmiclient.ts" />
/// <reference path="rmi/rmidatastruct.ts" />
/// <reference path="view/viewmanager.ts" />
function addScript(path) {
    var head = document.head;
    var script = document.createElement("script");
    script.src = path;
    head.appendChild(script);
}
function preloadScripts() {
    addScript("rmi/serialize.js");
    addScript("rmi/rmimanager.js");
    addScript("rmi/rmidatastruct.js");
    addScript("rmi/rmiclient.js");
    addScript("view/viewmanager.js");
    addScript("view/home.js");
    addScript("view/login.js");
}
preloadScripts();
window.onload = function () {
    View.ViewManager.init();
};
//# sourceMappingURL=app.js.map