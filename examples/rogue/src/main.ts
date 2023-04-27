import * as ROT from 'rot-js'
import { Map, Chunk } from './map';

ROT.RNG.setSeed(123456)
const noise = new ROT.Noise.Simplex();

let info = ''
const player = { x: 15, y: 8 }


global.keypress = (k) => {
    if (k === KEY_UP) player.y--;
    else if (k === KEY_DOWN) player.y++;
    else if (k === KEY_LEFT) player.x--;
    else if (k === KEY_RIGHT) player.x++;
    chunk.fill(player.x, player.y)
}

var cam = { x: 0, y: 0 }

global.draw = () => {
    clear(BLACK)
    chunk.draw(cam.x,cam.y)
    sprite(cam.x + chunk.centerX,cam.y + chunk.centerY, 77, WHITE)
    rect(0, 0, 640, 14, 1)
    text(12, 0, info)
}

const p = Promise.resolve('string');

async function f(){
    const v = await p;
    print(v)
}

f()
const chunk = new Chunk(32,22, noise)
chunk.fill(player.x, player.y)
