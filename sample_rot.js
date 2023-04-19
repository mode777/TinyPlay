var ROT = require('rot')

ROT.RNG.setSeed(19865);

function draw(){
    clear()
}

var digger = new ROT.Map.Digger(c.WIDTH,c.HEIGHT);

var map = new Array(c.WIDTH,c.HEIGHT)
var graphics = new Array(c.WIDTH,c.HEIGHT)
digger.create(function(x,y,v){
    map[y*c.WIDTH+x] = v
})
for (var y = 0; y < c.HEIGHT; y++) {
    for (var x = 0; x < c.WIDTH; x++) {
        var cur = map[y*c.WIDTH+x]
        if(cur === c.TYPE.wall){
            if(map[y*c.WIDTH+x+1] === c.TYPE.floor){

            }
            else if(map[y*c.WIDTH+x-1] === c.TYPE.floor){

            }
            else if(map[(y+1)*c.WIDTH+x] === c.TYPE.floor){
                
            }
            else if(map[(y-1)*c.WIDTH+x] === c.TYPE.floor){

            }
            else if(map[(y-1)*c.WIDTH+x] === c.TYPE.floor){
                
            }
        }
    }
    
}