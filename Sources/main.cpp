#include "../BMP_Modules/BITMAP_Image.hpp"
#include <string>
#include <iostream>


#define STEGANOGRAPHY
#define FILE_ "Images/FISH_TC.bmp"

#ifdef CONVERT
int main(){
    BITMAP_Image obj(FILE_);
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
    BMP_Viewer view(FILE_);
    view.draw(1);
    view.unloadFileImage("Images/test.bmp");
    return 0;
}
#endif

#ifdef STEGANOGRAPHY
#include "Steganography.hpp"
int main(){
    Steganography obj(FILE_);
    obj.encode("text");
    std::string test;
    obj.decode(test);
    std::cout << test << std::endl;
    obj.unloadFileImage("Images/test.bmp");
    return 0;
}
#endif