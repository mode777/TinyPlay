var ROT = require('rot')
ROT.RNG.setSeed(19865);

var noise = new ROT.Noise.Simplex();

var trees1 = [49,50,51,52,53,54]
var trees2 = [102,103,6,98,1,50,53]
var trees3 = [5,0,6,98,7,0,0]
var trees4 = [5,0,1,0,7,0,0,0,0,0]

var map = []

for (var y=0;y<24;y++) {
    for (var x=0;x<40;x++) {
        var val = Math.floor(noise.get(x/8, y/8) * 50) + 50
        
        if(val > 80){
            map[y*40+x] = ROT.RNG.getItem(trees1) 
        } else if(val > 60){
            map[y*40+x] = ROT.RNG.getItem(trees2) 
        } else if(val > 40){
            map[y*40+x] = ROT.RNG.getItem(trees3) 
        } else if(val > 0){
            map[y*40+x] = ROT.RNG.getItem(trees4)
        } else {
            map[y*40+x] = 0
        }
    }
}

var player = { x: 15, y: 8 } 

function keypress(k){
    if(k === KEY_UP) player.y--;
    if(k === KEY_DOWN) player.y++;
    if(k === KEY_LEFT) player.x--;
    if(k === KEY_RIGHT) player.x++;
}

function draw(){
    clear()
    for (var y=0;y<24;y++) {
        for (var x=0;x<40;x++) {
            tile(x,y,map[y*40+x],6)
        }
    }
    tile(player.x,player.y,77,WHITE)
}