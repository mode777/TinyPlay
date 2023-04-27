
var ROT = require('rot')
var TERRAIN = require('terrain')

ROT.RNG.setSeed(123456)
var noise = new ROT.Noise.Simplex();


var info = ''
var player = { x: 15, y: 8 }


function keypress(k) {
    if (k === KEY_UP) player.y--;
    else if (k === KEY_DOWN) player.y++;
    else if (k === KEY_LEFT) player.x--;
    else if (k === KEY_RIGHT) player.x++;
    terrain_map.fill(player.x, player.y)
}

function hash(x, y) {
    var prime = 31;
    var hash = x * prime + y;
    hash = ((hash >> 16) ^ hash) * 0x45d9f3b;
    hash = ((hash >> 16) ^ hash) * 0x45d9f3b;
    hash = (hash >> 16) ^ hash;
    return hash & 0xffff;
}

var WIDTH = 21
var HEIGHT = 21

var terrain_map = new Uint8Array(WIDTH * HEIGHT)
terrain_map.fill = function (ox, oy) {
    var seed = ROT.RNG.getSeed()
    for (var y = 0; y < HEIGHT; y++) {
        for (var x = 0; x < WIDTH; x++) {
            var localSeed = seed + hash(ox+x, oy+y)
            ROT.RNG.setSeed(localSeed)

            var biome = (noise.get((ox + x) / 32, (oy + y) / 32) * 0.5) + 0.5
            if (biome < 0.3) {
                if (biome < 0.25) {
                    terrain_map[y * HEIGHT + x] = 5
                } else {
                    terrain_map[y * HEIGHT + x] = 4
                }
                continue
            }
            var raw = (noise.get((ox + x) / 8, (oy + y) / 8) * 0.5) + 0.5

            var i = raw * 4
            var t = 0
            if (i > 3) {
                t = ROT.RNG.getWeightedValue({
                    0: 1,
                    3: 1,
                    1: 2
                })
            } else if (i > 2) {
                t = ROT.RNG.getWeightedValue({
                    0: 1,
                    1: 3,
                    3: 1
                })
            } else if (i > 1) {
                t = ROT.RNG.getWeightedValue({
                    0: 3,
                    1: 1,
                    2: 1,
                    3: 1
                })
            }
            terrain_map[y * HEIGHT + x] = t
        }
    }
    ROT.RNG.setSeed(seed)
}

WINDOW_X = 10
WINDOW_Y = 1

function draw() {
    clear(BLACK)
    rect(WINDOW_X * TILESIZE, WINDOW_Y * TILESIZE, WIDTH * TILESIZE, HEIGHT * TILESIZE, TEAL)
    for (var y = 0; y < HEIGHT; y++) {
        for (var x = 0; x < WIDTH; x++) {
            var t = terrain_map[y * HEIGHT + x]
            var terrain = TERRAIN[t]
            tile(WINDOW_X + x, WINDOW_Y + y, terrain.tile, terrain.fg, terrain.bg || 0)
        }
    }
    tile(WINDOW_X + ((WIDTH / 2) >>> 0), WINDOW_Y + ((HEIGHT / 2) >>> 0), 77, WHITE)
    rect(0, 0, 640, 14, 1)
    text(12, 0, info)
}

terrain_map.fill(player.x, player.y)