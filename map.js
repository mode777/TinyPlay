var ROT = require('rot')

function Map(w,h){
    __proto__ = Array.prototype
    this.width = w 
    this.height = h 
}
Map.prototype.get = function(x,y){
    if(x < 0 || x >= this.width || y < 0 || y >= this.height) return null
    return this[y*this.width+x]
}
Map.prototype.set = function(x,y,v){
    if(x < 0 || x >= this.width || y < 0 || y >= this.height) return
    this[y*this.width+x] = v
}
Map.prototype.create = function(){
    var orig = ROT.RNG.getSeed()
    for (var y=0;y<this.height;y++) {
        for (var x=0;x<this.width;x++) {
            var raw = noise.get(x/10, y/10)
            ROT.RNG.setSeed(Math.floor(Math.abs(raw*10000)))
            var val = Math.floor(raw * 50) + 50

            var id = null
    
            if(val > 80){
                var id = ROT.RNG.getWeightedValue({
                    PINE_TREE: 2,
                    TREE: 1
                })
            } else if(val > 60){
                var id = ROT.RNG.getWeightedValue({
                    PINE_TREE: 1,
                    TREE: 2,
                    GRASS: 1
                })
            } else if(val > 40){
                var id = ROT.RNG.getWeightedValue({
                    TREE: 1,
                    GRASS: 2,
                    NONE: 1
                })
            } else if(val > 0){
                var id = ROT.RNG.getWeightedValue({
                    GRASS: 1,
                    NONE: 1,
                })
            } else {
                var id = NONE 
            }
            this.set(x,y,DATA.TERRAIN[id].inst())
        }
    }
    ROT.RNG.setSeed(orig)
}
module.exports = Map;