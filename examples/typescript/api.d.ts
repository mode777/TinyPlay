declare module 'tinyplay' {
    
    global {
        function print(...params: any): void;
        var draw: () => void;
        function clear(color?: number): void;
    }
}
