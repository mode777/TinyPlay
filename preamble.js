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

var KEY_LEFT = 1073741904
var KEY_UP = 1073741906
var KEY_RIGHT = 1073741903
var KEY_DOWN = 1073741905