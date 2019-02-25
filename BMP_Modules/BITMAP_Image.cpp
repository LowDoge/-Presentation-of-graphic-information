#include "BITMAP_Image.hpp"
#include <iostream>
#include <fstream>
BITMAP_Image::BITMAP_Image(std::string file){
    if(loadFileImage(file) != 0){
        exit(-1);
    }

}

int BITMAP_Image::unloadFileImage(std::string file){
    std::ofstream image(file, std::ios::binary);

    if(image.good()){
        image.write(reinterpret_cast<char*>(f_header), sizeof(BitMapFileHeader));
        image.write(reinterpret_cast<char*>(inf_header), sizeof(BitMapInfoHeader));
        image.write(reinterpret_cast<char*>(palette), sizeof(RGBQuad) * BITMAP_PALETTE);
        for(int i = 0; i < heightInBytes; i++){
            image.write(reinterpret_cast<char*>(raster[i]), sizeof(unsigned char) * widthInBytes);
        }
    }

    image.close();

    return 0;
}

int BITMAP_Image::loadFileImage(std::string file){
    std::ifstream image(file, std::ios::binary);

    if(image.good()){
        image.seekg(0, std::ios::beg);
        image.read(reinterpret_cast<char*>(f_header), sizeof(BitMapFileHeader));
        image.read(reinterpret_cast<char*>(inf_header), sizeof(BitMapInfoHeader));

        widthInBytes = inf_header->Width * inf_header->BitCount / 8;
        heightInBytes = inf_header->Height * inf_header->BitCount / 8;

        image.read(reinterpret_cast<char*>(palette), sizeof(RGBQuad) * BITMAP_PALETTE);

        raster = new unsigned char*[heightInBytes];
        for(int i = 0; i < heightInBytes; i++){
            raster[i] = new unsigned char[widthInBytes];
            image.read(reinterpret_cast<char*>(raster[i]), sizeof(unsigned char) * widthInBytes);
        }

    }

    image.close();

    return 0;
}

BitMapFileHeader* BITMAP_Image::returnBitMapFileHeaderStruct(){
    return f_header;
}

BitMapInfoHeader* BITMAP_Image::returnBitMapInfoHeaderStruct(){
    return inf_header;
}

void BITMAP_Image::convertToGreyColor(void){
    for(short i = 0; i < BITMAP_PALETTE; i++){
        int r = (int)palette[i].Red;
        int b = (int)palette[i].Blue;
        int g = (int)palette[i].Green;
        int y = Y_GREY(r,g,b);
        palette[i].Red = (unsigned char)y;
        palette[i].Green = (unsigned char)y;
        palette[i].Blue = (unsigned char)y;
    }
}

void BITMAP_Image::drawBorder(int size, uint8_t red, uint8_t green, uint8_t blue){
    for(int counter = 0; counter < size; counter++){
        for(int i = 0; i < heightInBytes; i++){
            raster[i][0 + counter] = RGB_TO_SINGLE_BYTE(red, green, blue);
            raster[i][widthInBytes - 1 - counter] = RGB_TO_SINGLE_BYTE(red, green, blue);
        }

        for(int i = 0; i < widthInBytes; i++){
            raster[0 + counter][i] = RGB_TO_SINGLE_BYTE(red, green, blue);
            raster[heightInBytes - 1 - counter][0] = RGB_TO_SINGLE_BYTE(red, green, blue);
        }
    }
}

unsigned char** BITMAP_Image::rotateMatrix(unsigned char **matrix, uint16_t &width, uint16_t &height){
    
    unsigned char **newMatrix = new unsigned char*[width];  
    for(uint16_t i = 0; i < width; i++){
        newMatrix[i] = new unsigned char[height];
    }
    
    for(uint16_t i = 0; i < width; i++){
        for(uint16_t j = 0; j < height; j++){
            //newMatrix[i][j] = matrix[height-1-j][i];//left
            newMatrix[i][j] = matrix[j][width-1-i];//right
        }
    }
    for(uint16_t i = 0; i < height; i++){//delete old matrix
        delete[] matrix[i];
    }
    delete[] matrix;
    
    uint16_t tempSideSize = height;//swap size
    height = width;
    width = tempSideSize;

    return newMatrix;
}

void BITMAP_Image::rotateImage(int angle){
    if(angle % 90 != 0){
        return;
    }
    int rotationsAmount = angle / 90;

    for(int i = 0; i < rotationsAmount; i++){
        raster = rotateMatrix(raster, widthInBytes, heightInBytes);
    }

    inf_header->Width = widthInBytes;
    inf_header->Height = heightInBytes;
}

BITMAP_Image::~BITMAP_Image(){
    if(f_header != NULL){
        delete f_header;
    }
    if(inf_header != NULL){
        delete inf_header;
    }
    if(palette != NULL){
        delete[] palette;
    }
    if(raster != NULL){
        for(int i = 0; i < heightInBytes; i++){
            delete[] raster[i];
        }
        delete[] raster;
    }
}