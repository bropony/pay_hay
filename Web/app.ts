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
    //addScript("view/home.js");
    //addScript("view/login.js");
    //addScript("view/signup.js");
    //addScript("view/newpost.js");
}

preloadScripts();

//window.onload = () => {
//    View.ViewManager.init();
//};
