import * as ROT from 'rot-js';
import { hash, noise } from './main';

export class Map {
    data: Uint8Array;

    constructor(public readonly width: number, public readonly height: number) {
        this.data = new Uint8Array(width * height);
    }

    fill(ox: number, oy: number) {
        const seed = ROT.RNG.getSeed();
        for (let y = 0; y < this.height; y++) {
            for (let x = 0; x < this.width; x++) {
                const localSeed = seed + hash(ox + x, oy + y);
                ROT.RNG.setSeed(localSeed);

                const biome = (noise.get((ox + x) / 32, (oy + y) / 32) * 0.5) + 0.5;
                if (biome < 0.3) {
                    if (biome < 0.25) {
                        this.data[y * this.width + x] = 5;
                    } else {
                        this.data[y * this.width + x] = 4;
                    }
                    continue;
                }
                const raw = (noise.get((ox + x) / 8, (oy + y) / 8) * 0.5) + 0.5;

                const i = raw * 4;
                let t = 0;
                if (i > 3) {
                    t = ROT.RNG.getWeightedValue({
                        0: 1,
                        3: 1,
                        1: 2
                    }) as any;
                } else if (i > 2) {
                    t = ROT.RNG.getWeightedValue({
                        0: 1,
                        1: 3,
                        3: 1
                    }) as any;
                } else if (i > 1) {
                    t = ROT.RNG.getWeightedValue({
                        0: 3,
                        1: 1,
                        2: 1,
                        3: 1
                    }) as any;
                }
                this.data[y * this.height + x] = t;
            }
        }
        ROT.RNG.setSeed(seed);
    }
}
