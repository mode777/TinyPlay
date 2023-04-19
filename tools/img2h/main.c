#define STB_IMAGE_IMPLEMENTATION
#include <stdio.h>
#include <stdlib.h>
#include "stb_image.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <input_png_file> <output_header_file>\n", argv[0]);
        return 1;
    }

    int width, height, channels;
    unsigned char *image = stbi_load(argv[1], &width, &height, &channels, STBI_rgb_alpha);
    if (image == NULL) {
        printf("Error loading image: %s\n", stbi_failure_reason());
        return 1;
    }

    FILE *fp = fopen(argv[2], "w");
    if (fp == NULL) {
        printf("Error opening output file\n");
        return 1;
    }

    // Write width and height to header file
    fprintf(fp, "const int IMAGE_WIDTH = %d;\n", width);
    fprintf(fp, "const int IMAGE_HEIGHT = %d;\n", height);

    // Write alpha channel data to header file
    fprintf(fp, "const unsigned char IMAGE_ALPHA[%d] = {", width * height);
    for (int i = 0; i < width * height; i++) {
        fprintf(fp, "%d", image[4 * i + 0]);
        if (i < width * height - 1) {
            fprintf(fp, ", ");
        }
    }
    fprintf(fp, "};\n");

    fclose(fp);
    stbi_image_free(image);

    printf("Image loaded and data written to %s\n", argv[2]);
    return 0;
}
