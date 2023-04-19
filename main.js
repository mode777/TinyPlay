var ROT = require('rot')

var Game = {
    display: null,

    init: function() {
        this._generateMap();
    }
}

Game.map = {}
Game._generateMap = function() {
    var digger = new ROT.Map.Digger();

    var digCallback = function(x, y, value) {
        if (value) { return; } /* do not store walls */

        var key = x+","+y;
        this.map[key] = ".";
    }
    digger.create(digCallback.bind(this));
}
Game._drawWholeMap = function() {
    for (var key in this.map) {
        var parts = key.split(",")
        var x = parseInt(parts[0])
        var y = parseInt(parts[1])
        tile(x, y, 1)
    }
}

function draw(){
    clear()
    Game._drawWholeMap()
}

Game.init()