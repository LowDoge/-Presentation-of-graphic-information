#ifndef STEG
#define STEG

#include <bitset>
#include <string>
#include "../BMP_Modules/BITMAP_Image.hpp"

class Steganography : public BITMAP_Image
{
public:
    Steganography(std::string fileName) : BITMAP_Image(fileName){}
    void encode(std::string text);

    void decode(std::string &text);
};
#endif