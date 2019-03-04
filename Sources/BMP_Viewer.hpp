#ifndef BMP_VIEWER
#define BMP_VIEWER
#include "../BMP_Modules/BITMAP_Image.hpp"
#include <string>
#include <GL/glut.h>
#include <GL/glu.h>

#define MAX_BYTE_VALUE 255

class BMP_Viewer : public BITMAP_Image{
private:
    int win = 0;
    int argc = 1;
    char *argv[1] = {(char*)"Some string"};
public:
    BMP_Viewer(std::string file);
    void draw(float scale);
    void putPixel(int X, int Y, float R, float G, float B);
};

#endif