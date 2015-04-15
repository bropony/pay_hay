var View;
(function (View) {
    var Util;
    (function (Util) {
        function alertEmptyString(str, msg) {
            if (!str) {
                alert(msg);
                return true;
            }
            return false;
        }
        Util.alertEmptyString = alertEmptyString;
    })(Util = View.Util || (View.Util = {}));
})(View || (View = {}));
//# sourceMappingURL=util.js.map