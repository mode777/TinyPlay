import { RNG } from 'rot-js'
import Simplex from 'rot-js/lib/noise/simplex';
import TERRAIN from './data/terrain'

function hash(x: number, y: number) {
    const prime = 31;
    let hash = x * prime + y;
    hash = ((hash >> 16) ^ hash) * 0x45d9f3b;
    hash = ((hash >> 16) ^ hash) * 0x45d9f3b;
    hash = (hash >> 16) ^ hash;
    return hash & 0xffff;
}

export class Chunk {
    terrain: Map;
    constructor(
        public readonly width: number, 
        public readonly height: number, 
        private noise: Simplex){
        this.terrain = new Map(width, height)
    }

    get centerX() { return ((this.width/2) >>> 0) * TILESIZE }
    get centerY() { return ((this.height/2) >>> 0) * TILESIZE }
    
    fill(ox: number, oy: number) {
        const seed = RNG.getSeed();
        for (let y = 0; y < this.height; y++) {
            for (let x = 0; x < this.width; x++) {
                const localSeed = seed + hash(ox + x, oy + y);
                RNG.setSeed(localSeed);

                const biome = (this.noise.get((ox + x) / 32, (oy + y) / 32) * 0.5) + 0.5;
                if (biome < 0.3) {
                    if (biome < 0.25) {
                        this.terrain.set(x,y,5);
                    } else {
                        this.terrain.set(x,y,4);
                    }
                    continue;
                }
                const raw = (this.noise.get((ox + x) / 8, (oy + y) / 8) * 0.5) + 0.5;

                const i = raw * 4;
                let t = 0;
                if (i > 3) {
                    t = RNG.getWeightedValue({
                        0: 1,
                        3: 1,
                        1: 2
                    }) as any;
                } else if (i > 2) {
                    t = RNG.getWeightedValue({
                        0: 1,
                        1: 3,
                        3: 1
                    }) as any;
                } else if (i > 1) {
                    t = RNG.getWeightedValue({
                        0: 3,
                        1: 1,
                        2: 1,
                        3: 1
                    }) as any;
                }
                this.terrain.set(x,y,t);
            }
        }
        RNG.setSeed(seed);
    }

    draw(px: number, py: number) {
        rect(px, py, this.width * TILESIZE, this.height * TILESIZE, TEAL)
        for (let y = 0; y < this.height; y++) {
            for (let x = 0; x < this.width; x++) {
                const t = this.terrain.get(x,y)
                const terrain = TERRAIN[t]
                sprite(px + (x*TILESIZE), py + (y*TILESIZE), terrain.tile, terrain.fg, terrain.bg || 0)
            }
        }
    }
}

export class Map {
    data: Uint8Array;

    constructor(public readonly width: number, public readonly height: number) {
        this.data = new Uint8Array(width * height);
    }

    get centerX() { return (this.width/2) >>> 0 }
    get centerY() { return (this.height/2) >>> 0 }

    public get(x: number,y: number){
        return this.data[y * this.width + x]
    }

    public set(x: number,y: number,value: number){
        this.data[y*this.width+x] = value
    }


}
