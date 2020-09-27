#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "ellipse.h"
#include "graphics.h"

void ppmRead(char* filename, unsigned char* data, int* w, int* h) {
    char header[1024];
    FILE* fp = NULL;
    int line = 0;

    fp = fopen(filename, "rb");
    while (line < 2) {
        fgets(header, 1024, fp);
        if (header[0] != '#') {
            ++line;
        }
    }
    sscanf(header, "%d %d\n", w, h);
    fgets(header, 20, fp);
    fread(data, (*w) * (*h) * 3, 1, fp);

    fclose(fp);
}
void ppmWrite(const char* filename, unsigned char* data, int w, int h) {
    /**
     * writes data as an 2D array into a ppm picture with filename
     * */
    FILE* fp;
    fp = fopen(filename, "wb");

    fprintf(fp, "P6\n%d %d\n255\n", w, h);
    fwrite(data, w * h * 3, 1, fp);

    fclose(fp);
}

int sample(unsigned char* data, int const Width, int const Height){
    // Drawing sample, draws a square with side length of 100 pixels. Helps you understand the mechanism.
    for (int i = 100; i < 200; i++)
        for (int j = 100; j < 200; j++) {
            int index = 3 * (i * Width + j);
            data[index] = 255;
            data[index + 1] = 255;
            data[index + 2] = 255;
        }
    return 0;
}

int main() {
    const int Width = 400, Height = 300;
    // unsigned char data[Width * Height * 3] = {0};
    // sample(data,Width,Height);
    // ppmWrite("test.ppm", data, Width, Height);

    Canvas canvas(Width,Height);
    int a, b, cx, cy;
    double theta;
    std::cin >>a >>b >>cx >>cy >>theta;
    canvas.drawOutline(ellipse(a,b,Point(cx,cy),theta));
    canvas.show("test.ppm");
    return 0;
}