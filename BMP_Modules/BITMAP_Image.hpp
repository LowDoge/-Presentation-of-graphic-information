#ifndef BITMAP_IMAGE
#define BITMAP_IMAGE

#include "BITMAP_Struct.hpp"
#include <string>
#define BITMAP_PALETTE 256

class BITMAP_Image{
private:
    BitMapFileHeader *f_header = new BitMapFileHeader;
    BitMapInfoHeader *inf_header = new BitMapInfoHeader;
    RGBQuad *palette = new RGBQuad[BITMAP_PALETTE];
    unsigned char *raster = nullptr;
    uint16_t widthInBytes, heightInBytes;
    unsigned char** rotateMatrix(unsigned char **matrix, uint16_t &width, uint16_t &height);
public:
    BITMAP_Image(void);
    BITMAP_Image(std::string file);
    ~BITMAP_Image();
    int loadFileImage(std::string file);
    int unloadFileImage(std::string file);
    void convertToGreyColor(void);
    void drawBorder(int size, uint8_t red, uint8_t green, uint8_t blue);
    void rotateImage(int angle);
    BitMapFileHeader* returnBitMapFileHeaderStruct(void);
    BitMapInfoHeader* returnBitMapInfoHeaderStruct(void);
};

#endif