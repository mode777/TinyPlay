var ROT = require('rot')

var from = function (obj, n) {
    n = n || {}
    n.__proto__ = obj
    return n
}

var NONE = { 
    desc: [0],
    fg: 13,
    solid: false,
    tiles: [0],
    inst: function(){
        return {
            fg: this.fg,
            solid: this.solid,
            desc: this.getDesc(),
            tile: this.getTile()
        }
    },
    getDesc: function(){
      return ROT.RNG.getItem(this.desc)  
    },
    getTile: function(){
        return ROT.RNG.getItem(this.tiles)
    }
 }

var TREE = from(NONE, {
    fg: DARK_GREEN,
    desc: [1,2,3,4,5,6,7,8,9,10],
    solid: true,
    tiles: [52,53,54,102]
})
var PINE_TREE = from(TREE,{
    fg: TEAL,
    tiles: [49,50,51,101]
})
var GRASS = from(NONE, {
    fg: GREEN,
    desc: [11,12,13,14,15,16,17,18,19,20],
    tiles: [1,5,6,7,98,119]
})
var STONE = from(NONE, {
    fg: GREY, 
    desc: [21,22,23,24,25,26,27,28,30],
    solid: true,
    tiles: [103]
})


module.exports = {
    TERRAIN: {
        NONE: NONE,
        TREE: TREE,
        PINE_TREE: PINE_TREE,
        GRASS: GRASS,
        STONE: STONE
    }
}