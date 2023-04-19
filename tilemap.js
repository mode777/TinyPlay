var tileset = JSON.parse(load("assets/tileset.tsj"))

var colorLookup = tileset.tiles.reduce(function(p,c){
    p[c.id] = c.properties[0].value
    return p
},{})

var map = JSON.parse(load("assets/map1.tmj"))

var player = { x: 15, y: 8 } 

function keypress(k){
    if(k === KEY_UP) player.y--;
    if(k === KEY_DOWN) player.y++;
    if(k === KEY_LEFT) player.x--;
    if(k === KEY_RIGHT) player.x++;
}

function draw(){
    clear(0)
    var data = map.layers[0].data
    for (var y = 0; y < map.height; y++) {
        for (var x = 0; x < map.width; x++) {
            var t = data[y*map.width+x]-1
            if(t===0) continue;
            var c = colorLookup[t]
            if(c === undefined) c = 12
            tile(x,y,t,c)
        }   
    }
    tile(player.x,player.y,77,WHITE)
}