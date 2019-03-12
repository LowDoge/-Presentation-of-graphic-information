#include "Steganography.hpp"

void Steganography::decode(std::string &text){
    text.clear();
    for(int i = 0; i < heightInBytes; i++){
        for(int j = 0; j < widthInBytes * 3; j += 8){
            std::bitset<8> textChar;
            for(int c = 0; c < 8; c++){
                std::bitset<8> rasterChar(raster[i][c + j]);
                textChar[c] = rasterChar[0];
            }
            text += static_cast<unsigned char> (textChar.to_ulong());
            if(text.length() == f_header->Reserved1){
                return;
            }
        }
    }
}

void Steganography::encode(std::string text){
    if(text.length() > widthInBytes * heightInBytes * 3){
        exit(-1);
    }

    f_header->Reserved1 = text.length();
    int counter = 0;
    for(int i = 0; i < heightInBytes; i++){
        for(int j = 0; j < widthInBytes * 3; j += 8){
            std::bitset<8> textChar(text[j/8]);
            for(int c = 0; c < 8; c++){
                std::bitset<8> rasterChar(raster[i][c + j]);
                rasterChar[0] = textChar[c];
                raster[i][c + j] = static_cast<unsigned char> (rasterChar.to_ulong());
            }
            counter++;
            if(counter == text.length()){
                return;
            }
        }
    }
}