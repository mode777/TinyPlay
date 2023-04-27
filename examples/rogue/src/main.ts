import * as ROT from 'rot-js'
import TERRAIN from './data/terrain'
import { Map } from './map';

ROT.RNG.setSeed(123456)
export const noise = new ROT.Noise.Simplex();

let info = ''
const player = { x: 15, y: 8 }

export function hash(x: number, y: number) {
    const prime = 31;
    let hash = x * prime + y;
    hash = ((hash >> 16) ^ hash) * 0x45d9f3b;
    hash = ((hash >> 16) ^ hash) * 0x45d9f3b;
    hash = (hash >> 16) ^ hash;
    return hash & 0xffff;
}

const WINDOW_X = 10
const WINDOW_Y = 1

global.keypress = (k) => {
    if (k === KEY_UP) player.y--;
    else if (k === KEY_DOWN) player.y++;
    else if (k === KEY_LEFT) player.x--;
    else if (k === KEY_RIGHT) player.x++;
    terrain_map.fill(player.x, player.y)
}

global.draw = () => {
    clear(BLACK)
    rect(WINDOW_X * TILESIZE, WINDOW_Y * TILESIZE, terrain_map.width * TILESIZE, terrain_map.height * TILESIZE, TEAL)
    for (let y = 0; y < terrain_map.height; y++) {
        for (let x = 0; x < terrain_map.width; x++) {
            const t = terrain_map.data[y * terrain_map.height + x]
            const terrain = TERRAIN[t]
            tile(WINDOW_X + x, WINDOW_Y + y, terrain.tile, terrain.fg, terrain.bg || 0)
        }
    }
    tile(WINDOW_X + ((terrain_map.width / 2) >>> 0), WINDOW_Y + ((terrain_map.height / 2) >>> 0), 77, WHITE)
    rect(0, 0, 640, 14, 1)
    text(12, 0, info)
}

const terrain_map = new Map(21,21)
terrain_map.fill(player.x, player.y)