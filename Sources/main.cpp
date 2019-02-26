#include "../BMP_Modules/BITMAP_Image.hpp"
#include <iostream>
#include <stdint.h>

int main(){
    BITMAP_Image obj("Images/FISH_256.bmp");
    //obj.convertToGreyColor();
    //obj.drawBorder(15, 157, 220, 98);
    //obj.rotateImage(90);
    obj.unloadFileImage("Images/test.bmp");
    return 0;
}
