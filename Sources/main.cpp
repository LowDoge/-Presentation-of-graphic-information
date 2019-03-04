#include "../BMP_Modules/BITMAP_Image.hpp"

#define FILE "Images/FISH_TC.bmp"

#define GL_WINDOW
#ifndef GL_WINDOW
int main(){
    BITMAP_Image obj(FILE);
    //obj.convertToGreyColor();
    //obj.drawBorder(15, 157, 220, 98);//not work with TC
    //obj.rotateImage(90);//not work with TC
    obj.unloadFileImage("Images/test.bmp");
    return 0;
}
#endif
#ifdef GL_WINDOW

#include "BMP_Viewer.hpp"
static int win(0);
int main(int argc, char **argv){
    BMP_Viewer view(FILE);
    view.draw(1);
    view.unloadFileImage("Images/test.bmp");
    return 0;
}
#endif