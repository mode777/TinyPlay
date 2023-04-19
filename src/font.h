#ifndef FONT_H
#define FONT_H

#include <stdlib.h>

#define NUM_CHARS 209

typedef struct {
    int id;
    int x;
    int y;
    int width;
    int height;
    int xoffset;
    int yoffset;
    int xadvance;
} CharDescriptor;

typedef struct {
    int lineHeight;
    int base;
    int scaleW;
    int scaleH;
    int pages;
    int packed;
    int alphaChnl;
    int redChnl;
    int greenChnl;
    int blueChnl;
} FontDescriptor;

FontDescriptor FontDesc = {
    10,
    8,
    128,
    128,
    1,
    0,
    0,
    0,
    0,
    0
};

static CharDescriptor chars[NUM_CHARS] = {
    // a.split('\n').map(x => x.split(' ').filter(y => y.includes('=')).map(z => z.split('=')[1])).map(x => '{' + x.join(',') + '}').join(',%')
    {32,12,27,3,1,-1,11,2},
    {33,127,32,1,7,0,3,2},
    {34,99,45,3,2,0,3,4},
    {35,5,28,5,7,0,3,6},
    {36,76,0,5,9,0,2,6},
    {37,10,28,5,7,0,3,6},
    {38,91,18,6,7,0,3,7},
    {39,113,45,1,2,0,3,2},
    {40,27,41,2,7,0,3,3},
    {41,126,14,2,7,0,3,3},
    {42,74,46,3,3,1,5,5},
    {43,17,48,5,5,0,4,6},
    {44,112,45,1,2,0,9,2},
    {45,115,45,5,1,0,6,6},
    {46,79,9,1,1,0,9,2},
    {47,110,25,5,7,0,3,6},
    {48,100,25,5,7,0,3,6},
    {49,24,41,3,7,0,3,4},
    {50,110,32,5,7,0,3,6},
    {51,95,25,5,7,0,3,6},
    {52,90,25,5,7,0,3,6},
    {53,80,26,5,7,0,3,6},
    {54,65,26,5,7,0,3,6},
    {55,60,26,5,7,0,3,6},
    {56,50,26,5,7,0,3,6},
    {57,45,26,5,7,0,3,6},
    {58,49,46,1,5,0,5,2},
    {59,120,39,1,6,0,5,2},
    {60,8,42,4,7,0,3,5},
    {61,66,46,5,3,0,5,6},
    {62,123,32,4,7,0,3,5},
    {63,105,32,5,7,0,3,6},
    {64,100,32,5,7,0,3,6},
    {65,95,32,5,7,0,3,6},
    {66,90,32,5,7,0,3,6},
    {67,85,32,5,7,0,3,6},
    {68,80,33,5,7,0,3,6},
    {69,75,33,5,7,0,3,6},
    {70,70,33,5,7,0,3,6},
    {71,65,33,5,7,0,3,6},
    {72,60,33,5,7,0,3,6},
    {73,21,41,3,7,0,3,4},
    {74,18,41,3,7,0,3,4},
    {75,55,33,5,7,0,3,6},
    {76,119,32,4,7,0,3,5},
    {77,60,19,7,7,0,3,8},
    {78,50,33,5,7,0,3,6},
    {79,40,33,5,7,0,3,6},
    {80,35,34,5,7,0,3,6},
    {81,32,19,5,8,0,3,6},
    {82,30,34,5,7,0,3,6},
    {83,25,34,5,7,0,3,6},
    {84,121,18,5,7,0,3,6},
    {85,20,34,5,7,0,3,6},
    {86,75,26,5,7,0,3,6},
    {87,53,19,7,7,0,3,8},
    {88,15,34,5,7,0,3,6},
    {89,5,35,5,7,0,3,6},
    {90,0,35,5,7,0,3,6},
    {91,126,7,2,7,0,3,3},
    {92,115,25,5,7,0,3,6},
    {93,126,0,2,7,0,3,3},
    {94,61,46,5,3,0,3,6},
    {95,86,45,5,1,0,9,6},
    {96,114,45,1,2,4,3,6},
    {97,61,40,5,6,0,4,6},
    {98,22,19,5,8,0,2,6},
    {99,66,40,5,6,0,4,6},
    {100,12,19,5,8,0,2,6},
    {101,71,40,5,6,0,4,6},
    {102,85,25,5,7,0,3,6},
    {103,15,27,5,7,0,4,6},
    {104,17,19,5,8,0,2,6},
    {105,121,39,1,6,0,4,2},
    {106,15,41,3,7,0,4,4},
    {107,76,40,5,6,0,4,6},
    {108,116,39,4,6,0,4,5},
    {109,39,41,7,6,0,4,8},
    {110,51,40,5,6,0,4,6},
    {111,81,40,5,6,0,4,6},
    {112,86,39,5,6,0,4,6},
    {113,30,27,5,7,0,4,6},
    {114,91,39,5,6,0,4,6},
    {115,96,39,5,6,0,4,6},
    {116,115,32,4,7,0,3,5},
    {117,101,39,5,6,0,4,6},
    {118,106,39,5,6,0,4,6},
    {119,32,41,7,6,0,4,8},
    {120,111,39,5,6,0,4,6},
    {121,70,26,5,7,0,4,6},
    {122,46,40,5,6,0,4,6},
    {123,125,25,3,7,0,3,4},
    {124,31,41,1,7,0,3,2},
    {125,12,42,3,7,0,3,4},
    {126,85,46,6,2,0,5,7},
    {161,30,41,1,7,0,3,2},
    {162,20,27,5,7,0,3,6},
    {163,25,27,5,7,0,3,6},
    {164,27,48,5,5,0,4,6},
    {165,40,26,5,7,0,3,6},
    {166,29,41,1,7,0,3,2},
    {167,55,26,5,7,0,3,6},
    {168,80,18,5,1,0,3,6},
    {169,97,18,6,7,0,3,7},
    {170,50,46,3,4,0,3,4},
    {171,0,49,6,5,0,4,7},
    {172,91,45,5,2,0,6,6},
    {173,76,9,3,1,0,6,4},
    {174,73,19,6,7,0,3,7},
    {175,120,45,5,1,0,3,6},
    {176,77,46,3,3,0,3,4},
    {177,12,49,5,5,0,4,6},
    {178,37,47,3,5,0,3,4},
    {179,40,47,3,5,0,3,4},
    {180,126,24,2,1,0,3,3},
    {181,56,40,5,6,0,6,6},
    {182,35,27,5,7,0,3,6},
    {183,37,26,1,1,0,6,2},
    {184,83,46,2,3,0,9,3},
    {185,126,21,2,3,0,3,3},
    {186,71,46,3,3,0,3,4},
    {187,122,39,6,5,0,4,7},
    {188,103,18,6,7,0,3,7},
    {189,67,19,6,7,0,3,7},
    {190,115,18,6,7,0,3,7},
    {191,105,25,5,7,0,3,6},
    {192,110,9,5,9,0,1,6},
    {193,105,9,5,9,0,1,6},
    {194,10,0,5,10,0,0,6},
    {195,25,0,5,10,0,0,6},
    {196,81,0,5,9,0,1,6},
    {197,25,10,5,9,0,1,6},
    {198,45,19,8,7,0,3,9},
    {199,111,0,5,9,0,3,6},
    {200,106,0,5,9,0,1,6},
    {201,101,0,5,9,0,1,6},
    {202,45,0,5,10,0,0,6},
    {203,86,0,5,9,0,1,6},
    {204,123,9,3,9,0,1,4},
    {205,3,19,3,9,0,1,4},
    {206,70,0,3,10,0,0,4},
    {207,6,19,3,9,0,1,4},
    {208,79,19,6,7,-1,3,6},
    {209,60,0,5,10,0,0,6},
    {210,100,9,5,9,0,1,6},
    {211,95,9,5,9,0,1,6},
    {212,65,0,5,10,0,0,6},
    {213,5,0,5,10,0,0,6},
    {214,85,9,5,9,0,1,6},
    {215,22,48,5,5,0,4,6},
    {216,10,35,5,7,0,3,6},
    {217,115,9,5,9,0,1,6},
    {218,75,10,5,9,0,1,6},
    {219,20,0,5,10,0,0,6},
    {220,70,10,5,9,0,1,6},
    {221,80,9,5,9,0,1,6},
    {222,0,42,4,7,0,3,5},
    {223,45,33,5,7,0,3,6},
    {224,65,10,5,9,0,1,6},
    {225,60,10,5,9,0,1,6},
    {226,15,0,5,10,0,0,6},
    {227,30,0,5,10,0,0,6},
    {228,55,10,5,9,0,1,6},
    {229,30,10,5,9,0,1,6},
    {230,37,19,8,7,0,3,9},
    {231,50,10,5,9,0,3,6},
    {232,45,10,5,9,0,1,6},
    {233,40,10,5,9,0,1,6},
    {234,40,0,5,10,0,0,6},
    {235,35,10,5,9,0,1,6},
    {236,9,19,3,9,0,1,4},
    {237,120,9,3,9,0,1,4},
    {238,73,0,3,10,0,0,4},
    {239,0,19,3,9,0,1,4},
    {240,27,19,5,8,0,2,6},
    {241,50,0,5,10,0,0,6},
    {242,20,10,5,9,0,1,6},
    {243,15,10,5,9,0,1,6},
    {244,0,0,5,10,0,0,6},
    {245,55,0,5,10,0,0,6},
    {246,10,10,5,9,0,1,6},
    {247,32,47,5,5,0,4,6},
    {248,0,28,5,7,0,3,6},
    {249,5,10,5,9,0,1,6},
    {250,0,10,5,9,0,1,6},
    {251,35,0,5,10,0,0,6},
    {252,121,0,5,9,0,1,6},
    {253,91,0,5,9,0,1,6},
    {254,4,42,4,7,0,3,5},
    {255,116,0,5,9,0,1,6},
    {376,96,0,5,9,0,1,6},
    {7838,120,25,5,7,0,3,6},
    {8212,40,40,6,1,0,6,7},
    {8216,108,45,1,2,0,3,2},
    {8217,110,45,1,2,0,3,2},
    {8218,111,45,1,2,0,9,2},
    {8219,109,45,1,2,0,3,2},
    {8220,96,45,3,2,0,3,4},
    {8221,102,45,3,2,0,3,4},
    {8222,105,45,3,2,0,9,4},
    {8224,90,9,5,9,0,3,6},
    {8226,80,46,3,3,0,5,4},
    {8230,17,53,5,1,0,9,6},
    {8249,43,47,3,5,0,4,4},
    {8250,46,46,3,5,0,4,4},
    {8364,6,49,6,5,-1,4,6},
    {8482,53,46,8,3,0,3,9},
    {64257,85,18,6,7,0,3,7},
    {64258,109,18,6,7,0,3,7}
};

CharDescriptor* getChar(int id) {
    int left = 0, right = (NUM_CHARS - 1);
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (chars[mid].id == id) {
            return &chars[mid];
        } else if (chars[mid].id < id) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return NULL;
}


#endif