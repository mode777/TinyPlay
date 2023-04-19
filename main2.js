function drawPal(x,y){
    for (var c = 0; c < 16; c++) {
        tile((x+c),y, 0, 0, c)
        tile((x+c),y, 725, (c+1)%16, 0)
    }
}

function drawWin(x,y,w,h){
    var corner = 155
    var side = 154
    tile(x,y,corner, WHITE)
    tile(x+w,y,corner, WHITE, 0, true, false)
    tile(x,y+h,corner, WHITE, 0, false, true)
    tile(x+w,y+h,corner, WHITE, 0, true, true)
}

var str = load("lorem.txt")
save("test.json", JSON.stringify({ hello: 'world' }))

function draw(){
    var mpos = mouse();
    //print(mpos[0],mpos[1])
    var mx = Math.floor((mpos[0]+8)/16)*16
    var my = Math.floor((mpos[1]+8)/16)*16
    clear(0)
    tile(0,0,761)
    tile(1,0,922)
    tile(2,0,923)
    tile(21,0,761)
    tile(22,0,918)
    tile(23,0,923)
    drawPal(3,0)
    drawPal(24,0)

    drawWin(0,1,16,16)

    sprite(mpos[0],mpos[1], 1007, RED)
    sprite(mx,my,623, RED)
    text(200,200,str, WHITE)
}



// Specs
// Resolution: 640x360
// Tilesize: 16x16
// Viewport Size: 40x23
// Map Size: 64x32
// Sprites 64
// Tiles: https://kenney.nl/assets/1-bit-pack
// Colors: https://lospec.com/palette-list/sweetie-16