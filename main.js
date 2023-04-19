var adder = require('module')
var rot = require('rot')

for (var key in rot) {
    print(key)
}

print(adder(2,3))

var tileset = JSON.parse(load("assets/tileset.tsj"))

var colorLookup = tileset.tiles.reduce(function(p,c){
    p[c.id] = c.properties[0].value
    return p
},{})

var map = JSON.parse(load("assets/map1.tmj"))

function draw(){
    color(12,0)
    clear()
    var data = map.layers[0].data
    for (var y = 0; y < map.height; y++) {
        for (var x = 0; x < map.width; x++) {
            var t = data[y*map.width+x]-1
            if(t===0) continue;
            var c = colorLookup[t]
            if(c === undefined) c = 12
            flip(x%2,0)
            color(c,0)
            tile(x,y,t)
        }   
    }
    fg(12)
    tile(15,8,77)
}