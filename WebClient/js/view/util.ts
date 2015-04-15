module View {
    export module Util {
        export function alertEmptyString(str: string, msg: string) {
            if (!str) {
                alert(msg);
                return true;
            }

            return false;
        }
    }
} 