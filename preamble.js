if (typeof global === 'undefined') {
    (function () {
        var global = new Function('return this;')();
        Object.defineProperty(global, 'global', {
            value: global,
            writable: true,
            enumerable: false,
            configurable: true
        });
    })();
}

Duktape.modSearch = function (id) {
    /* readFile() reads a file from disk, and returns a string or undefined.
     * 'id' is in resolved canonical form so it only contains terms and
     * slashes, and no '.' or '..' terms.
     */
    var res;

    print('loading module:', id);

    res = load(id + '.js');
    if (typeof res === 'string') {
        return res;
    }

    throw new Error('module not found: ' + id);
}

__internal__ = {
    getFolder: function(path){
        
    }
}

var KEY_LEFT = 1073741904
var KEY_UP = 1073741906
var KEY_RIGHT = 1073741903
var KEY_DOWN = 1073741905

var BLACK = 0
var TRANSPARENT = 0
var PURPLE = 1
var RED = 2
var ORANGE = 3
var YELLOW = 4
var GREEN = 5
var DARK_GREEN = 6
var TEAL = 7
var DARK_BLUE = 8
var BLUE = 9
var SKY = 10
var AQUA = 11
var WHITE = 12
var GREY = 13
var DARK_GREY = 14
var GREY_BLUE = 15

var TILESIZE = 16
var SCREEN_WIDTH = 640
var SCREEN_HEIGHT = 360