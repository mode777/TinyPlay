#include <stdbool.h>

#include <SDL.h>
#include <duktape.h>

#include "font.h"
#include "kenney_1bit.h"
#include "kenney_pixel.h"

#define WIDTH 640
#define HEIGHT 360
#define COLORS 16
#define TILESIZE 16
#define TILES_X (IMAGE_WIDTH / TILESIZE)

static uint8_t* framebuffer;
static SDL_Renderer* renderer;
static SDL_Window* window;
static int bg = 0;
static int fg = 13;
static bool flipH = false;
static bool flipV = false;

static void decodeId(uint32_t id, int* out_ox, int* out_oy, int* out_fg, int* out_bg){
    *out_ox = ((id&0xFFFF)%TILES_X) * TILESIZE;
    *out_oy = ((id&0xFFFF)/TILES_X) * TILESIZE;
    *out_fg = (id&0x000F0000)>>16;
    *out_bg = (id&0x00F00000)>>20;
}

static uint32_t encodeId(uint32_t tileId, int fg, int bg){
    return tileId | (fg<<16) | (bg<<20);
}

static void plotSprite(int x, int y, uint32_t id){
    if(x+16<0 || x >= WIDTH || y+16<0 || y >= HEIGHT){
        return;
    }
    int ox, oy;
    ox = (id%TILES_X) * TILESIZE;
    oy = (id/TILES_X) * TILESIZE;

    for (size_t py = 0; py < TILESIZE; py++)
    {
        for (size_t px = 0; px < TILESIZE; px++)
        {
            int dx = x+px;
            int dy = y+py;
            if(dx < 0 || dx >= WIDTH || dy < 0 || dy >= HEIGHT) continue;
            int tx = px;
            int ty = py; 
            if(flipH) tx = 15-px;
            if(flipV) ty = 15-py;
            unsigned char val = IMAGE_ALPHA[(oy+ty)*IMAGE_WIDTH+ox+tx];
            int d = (y+py)*WIDTH+(x+px);
            if(val > 0){
                framebuffer[d] = fg;
            } else if(bg > 0) {
                framebuffer[d] = bg;
            }
        }
    }
}

static void plotGlyph(int x, int y, CharDescriptor* c){
    if(x+c->width<0 || x >= WIDTH || y+c->height<0 || y >= HEIGHT){
        return;
    }
    int ox = c->x, oy = c->y;

    for (size_t py = 0; py < c->height; py++)
    {
        for (size_t px = 0; px < c->width; px++)
        {
            int dx = x+px;
            int dy = y+py;
            if(dx < 0 || dx >= WIDTH || dy < 0 || dy >= HEIGHT) continue;
            unsigned char val = FONT_IMAGE_ALPHA[(oy+py)*FONT_IMAGE_WIDTH+ox+px];
            int d = (y+py)*WIDTH+(x+px);
            if(val > 0){
                framebuffer[d] = fg;
            } else if(bg > 0) {
                framebuffer[d] = bg;
            }
        }
    }
}

// Function to read a file into a string
static char* readFile(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "Failed to open file: %s\n", filename);
        return NULL;
    }

    // Get the file size
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    // Allocate a buffer to hold the file contents
    char* buffer = (char*) malloc(size + 1);
    if (!buffer) {
        fprintf(stderr, "Failed to allocate memory for file contents\n");
        fclose(file);
        return NULL;
    }

    // Read the file contents into the buffer
    size_t bytesRead = fread(buffer, 1, size, file);
    buffer[bytesRead] = '\0';

    // Clean up
    fclose(file);

    return buffer;
}

// Function to write a string to a file
static int writeFile(const char* filename, const char* content) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        fprintf(stderr, "Failed to open file: %s\n", filename);
        return 0;
    }

    // Write the string to the file
    size_t bytesWritten = fwrite(content, 1, strlen(content), file);
    if (bytesWritten != strlen(content)) {
        fprintf(stderr, "Failed to write to file: %s\n", filename);
        fclose(file);
        return 0;
    }

    // Clean up
    fclose(file);

    return 1;
}

static int js_draw_text(duk_context *ctx) {
    int ox = duk_require_int(ctx, 0);
    int y = duk_require_int(ctx, 1);
    
    CharDescriptor* cd;
    int i = 0;
    duk_codepoint_t codepoint;
    int x = ox;

    while((codepoint = duk_char_code_at(ctx, 2, i)) != 0) {
        i++;
        if (codepoint == '\n') {
            x = ox;
            y += FontDesc.lineHeight;
        } else {
            cd = getChar(codepoint);
            if (cd == NULL) {
                cd = getChar('?');
            }
            if(codepoint != ' ') plotGlyph(x + cd->xoffset, y + cd->yoffset, cd);
            x += cd->xadvance;
        }
    }

    return 0;
}

// Define a simple implementation of console.log() in C
static duk_ret_t native_print(duk_context *ctx) {
    duk_push_string(ctx, " ");
    duk_insert(ctx, 0);
    duk_join(ctx, duk_get_top(ctx) - 1);
    printf("%s\n", duk_to_string(ctx, -1));
    return 0;
}

static duk_ret_t js_get_id(duk_context *ctx) {
    uint32_t tileId = (uint32_t) duk_require_uint(ctx, 0);
    int fg = (int) duk_require_int(ctx, 1);
    int bg = (int) duk_require_int(ctx, 2);
    uint32_t id = encodeId(tileId, fg, bg);
    duk_push_uint(ctx, id);
    return 1;
}

static duk_ret_t js_sprite(duk_context *ctx) {
    int x = (int) duk_require_int(ctx, 0);
    int y = (int) duk_require_int(ctx, 1);
    uint32_t id = (uint32_t) duk_require_uint(ctx, 2);
    plotSprite(x, y, id);
    return 0;
}

static duk_ret_t js_tile(duk_context *ctx) {
    int x = (int) duk_require_int(ctx, 0);
    int y = (int) duk_require_int(ctx, 1);
    uint32_t id = (uint32_t) duk_require_uint(ctx, 2);
    plotSprite(x*TILESIZE, y*TILESIZE, id);
    return 0;
}

static duk_ret_t js_clear(duk_context *ctx) {
    memset((void*)framebuffer, bg, WIDTH*HEIGHT);
    return 0;
}

static duk_ret_t js_ticks(duk_context *ctx) {
    uint32_t ticks = SDL_GetTicks();
    duk_push_uint(ctx, ticks);
    return 1;
}

static duk_ret_t js_mouse(duk_context *ctx) {
    SDL_Rect rect;
    SDL_RenderGetViewport(renderer, &rect);

    int x, y;
    uint32_t state = SDL_GetMouseState(&x, &y);

    
    float sx, sy;
    SDL_RenderGetScale(renderer, &sx, &sy);
    int rw, rh;
    SDL_GetRendererOutputSize(renderer, &rw, &rh);
    int ww, wh;
    SDL_GetWindowSize(window, &ww, &wh);
    //printf("%d %d %f %f | %d %d | %d %d %d %d\n",rect.x,rect.y,sx,sy,x,y,rw,rh,ww,wh);
    sx /= (rw/ww);
    sy /= (rh/wh);

    x = (x - rect.x*sx) / sx;
    y = (y - rect.y*sy) / sy;

    duk_idx_t arr_idx = duk_push_array(ctx);
    duk_push_int(ctx, x);
    duk_put_prop_index(ctx, arr_idx, 0);
    duk_push_int(ctx, y);
    duk_put_prop_index(ctx, arr_idx, 1);

    return 1;
}

static int js_set_fg(duk_context *ctx) {
    int color = duk_require_int(ctx, 0);
    if (color < 0 || color > 15) {
        return duk_error(ctx, DUK_ERR_RANGE_ERROR, "Invalid color value");
    }
    fg = color;
    return 0;
}

static int js_set_bg(duk_context *ctx) {
    int color = duk_require_int(ctx, 0);
    if (color < 0 || color > 15) {
        return duk_error(ctx, DUK_ERR_RANGE_ERROR, "Invalid color value");
    }
    bg = color;
    return 0;
}

static int js_set_color(duk_context *ctx) {
    int afg = duk_require_int(ctx, 0);
    int abg = duk_require_int(ctx, 1);
    if (afg < 0 || afg > 15 || abg < 0 || abg > 15) {
        return duk_error(ctx, DUK_ERR_RANGE_ERROR, "Invalid color value");
    }
    bg = abg;
    fg = afg;
    return 0;
}

static int js_set_flip(duk_context *ctx) {
    bool flip_h = duk_require_uint(ctx, 0);
    bool flip_v = duk_require_uint(ctx, 1);
    flipH = flip_h;
    flipV = flip_v;
    return 0;
}

// Function to bind the 'load' function to JavaScript
static duk_ret_t js_load(duk_context* ctx) {
    const char* filename = duk_require_string(ctx, 0);
    char* contents = readFile(filename);
    if (!contents) {
        return duk_error(ctx, DUK_ERR_ERROR, "Failed to read file: %s", filename);
    }
    duk_push_string(ctx, contents);
    free(contents);
    return 1;
}

// Function to bind the 'save' function to JavaScript
static duk_ret_t js_save(duk_context* ctx) {
    const char* filename = duk_require_string(ctx, 0);
    const char* content = duk_require_string(ctx, 1);
    int result = writeFile(filename, content);
    duk_push_boolean(ctx, result);
    return 1;
}


int main(int argc, char* argv[]) {
    SDL_Surface* surface;
    SDL_Event event;
    SDL_Color palette[COLORS] = {
      { 0x1a, 0x1c, 0x2c, 0xff }, // dark blue
      { 0x5d, 0x27, 0x5d, 0xff }, // dark purple
      { 0xb1, 0x3e, 0x53, 0xff }, // red
      { 0xef, 0x7d, 0x57, 0xff }, // orange
      { 0xff, 0xcd, 0x75, 0xff }, // yellow
      { 0xa7, 0xf0, 0x70, 0xff }, // light green
      { 0x38, 0xb7, 0x64, 0xff }, // green
      { 0x25, 0x71, 0x79, 0xff }, // teal
      { 0x29, 0x36, 0x6f, 0xff }, // dark blue
      { 0x3b, 0x5d, 0xc9, 0xff }, // bright blue
      { 0x41, 0xa6, 0xf6, 0xff }, // sky blue
      { 0x73, 0xef, 0xf7, 0xff }, // light blue
      { 0xf4, 0xf4, 0xf4, 0xff }, // light grey
      { 0x94, 0xb0, 0xc2, 0xff }, // grey blue
      { 0x56, 0x6c, 0x86, 0xff }, // blue grey
      { 0x33, 0x3c, 0x57, 0xff }  // dark blue grey
    };
    SDL_Palette* sdl_palette;
    int quit = 0;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    // Create a window and renderer
    window = SDL_CreateWindow("Palette example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    if (!window) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to create window: %s", SDL_GetError());
        return 1;
    }
    SDL_ShowCursor(SDL_DISABLE);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to create renderer: %s", SDL_GetError());
        return 1;
    }
    SDL_RenderSetIntegerScale(renderer, 1);
    SDL_RenderSetLogicalSize(renderer, WIDTH, HEIGHT);

    // Create a palette and set the colors
    sdl_palette = SDL_AllocPalette(COLORS);
    if (!sdl_palette) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to allocate palette: %s", SDL_GetError());
        return 1;
    }
    SDL_SetPaletteColors(sdl_palette, palette, 0, COLORS);

    // Create a surface to render to with the palette
    surface = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 8, 0, 0, 0, 0);
    if (!surface) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to create surface: %s", SDL_GetError());
        return 1;
    }
    SDL_SetSurfacePalette(surface, sdl_palette);

    // Allocate memory for the framebuffer
    framebuffer = malloc(WIDTH * HEIGHT * sizeof(uint8_t));
    if (!framebuffer) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to allocate framebuffer memory");
        return 1;
    }

    // Initialize Duktape
    duk_context *ctx = duk_create_heap_default();

    duk_push_global_object(ctx);

    duk_push_c_function(ctx, native_print, DUK_VARARGS);
    duk_put_global_string(ctx, "print");

    duk_push_c_function(ctx, js_get_id, 3);
    duk_put_global_string(ctx, "getId");

    duk_push_c_function(ctx, js_sprite, 3);
    duk_put_global_string(ctx, "sprite");

    duk_push_c_function(ctx, js_tile, 3);
    duk_put_global_string(ctx, "tile");

    duk_push_c_function(ctx, js_clear, 0);
    duk_put_global_string(ctx, "clear");

    duk_push_number(ctx, TILESIZE);
    duk_put_global_string(ctx, "TILESIZE");

    duk_push_c_function(ctx, js_ticks, 0);
    duk_put_global_string(ctx, "ticks");

    duk_push_c_function(ctx, js_mouse, 0);
    duk_put_global_string(ctx, "mouse");

    duk_push_c_function(ctx, js_set_bg, 1);
    duk_put_global_string(ctx, "bg");

    duk_push_c_function(ctx, js_set_fg, 1);
    duk_put_global_string(ctx, "fg");

    duk_push_c_function(ctx, js_set_color, 2);
    duk_put_global_string(ctx, "color");

    duk_push_c_function(ctx, js_set_flip, 2);
    duk_put_global_string(ctx, "flip");

    duk_push_c_function(ctx, js_draw_text, 3);
    duk_put_global_string(ctx, "text");

    duk_push_c_function(ctx, js_load, 1);
    duk_put_global_string(ctx, "load");

    duk_push_c_function(ctx, js_save, 2);
    duk_put_global_string(ctx, "save");

    // Register the native_print() function as console.log()
    int objIndex = duk_push_object(ctx);
    duk_push_c_function(ctx, native_print, DUK_VARARGS);
    duk_put_prop_string(ctx, objIndex, "log");
    duk_push_c_function(ctx, native_print, DUK_VARARGS);
    duk_put_prop_string(ctx, objIndex, "warn");
    duk_push_c_function(ctx, native_print, DUK_VARARGS);
    duk_put_prop_string(ctx, objIndex, "error");
    duk_put_prop_string(ctx, objIndex-1, "console");

    duk_pop(ctx);

    // Load and evaluate a JavaScript file
    const char* filename = "main.js";
    const char* buf = readFile(filename);
    int rc = duk_peval_string(ctx, buf);
    if (rc != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error evaluating JavaScript: %s", duk_safe_to_string(ctx, -1));
        return 1;
    }
    free((void*)buf);

    // Find the draw() function in the global object
    duk_get_global_string(ctx, "draw");
    if (!duk_is_function(ctx, -1)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "No draw() function found");
        return 1;
    }

    // Main loop
    while (!quit) {
        Uint64 tStart = SDL_GetPerformanceCounter();
        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }
        
        // Call the draw() function
        duk_dup(ctx, -1);
        int rc = duk_pcall(ctx, 0);
        if (rc != 0) {
            duk_get_prop_string(ctx, -1, "stack");
            const char* stack = duk_get_string_default(ctx, -1, "");
            duk_pop(ctx);
            //const char* error = duk_safe_to_string(ctx, -1);
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error calling draw(): %s", stack);

            return 1;
        }
        duk_pop(ctx);

        // Copy the framebuffer data to the surface
        SDL_LockSurface(surface);
        memcpy(surface->pixels, framebuffer, WIDTH * HEIGHT * sizeof(uint8_t));
        SDL_UnlockSurface(surface);

        // Render the surface to the screen
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        Uint64 tEnd = SDL_GetPerformanceCounter();
        //printf("Time: %d\n", (tEnd-tStart)/(SDL_GetPerformanceFrequency()/1000));
        SDL_RenderPresent(renderer);
        SDL_DestroyTexture(texture);
    }

    // Clean up
    free(framebuffer);
    SDL_FreePalette(sdl_palette);
    SDL_FreeSurface(surface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
