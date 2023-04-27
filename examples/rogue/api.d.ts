declare module 'tinyplay' {
    
    global {
        function print(...params: any): void;
        function clear(color?: number): void;
        function tile(x: number, y: number, tile: number, fg?: number, bg?: number): void;
        function rect(x: number, y: number, w: number, h: number, fg?: number): void;
        function text(x: number, y: number, t: string): void;

        var draw: () => void;
        var keypress: (key: number) => void;
        
        const GREEN: number
        const BLACK: number
        const GREY: number
        const DARK_GREEN: number
        const AQUA: number
        const BLUE: number
        const TEAL: number
        const WHITE: number

        const KEY_UP: number
        const KEY_DOWN: number
        const KEY_LEFT: number
        const KEY_RIGHT: number

        const TILESIZE: number
    }
}
