#include "BITMAP_Image.hpp"

BITMAP_Image::BITMAP_Image(std::string file){
    if(loadFileImage(file) != 0){
        exit(-1);
    }

}

int BITMAP_Image::unloadFileImage(std::string file){
    FILE *image = fopen(file.c_str(), "wb");
    
    if(f_header == NULL || inf_header == NULL){
        return -1;
    }

    if(image == NULL){
        return -1;
    }

    if(fwrite(f_header, sizeof(BitMapFileHeader), 1, image)){
    }else{
        return -1;
    }

    if(fwrite(inf_header, sizeof(BitMapInfoHeader), 1, image)){
    }else{
        return -1;
    }

    if(fwrite(palette, sizeof(RGBQuad), BITMAP_PALETTE, image)){
    }else{
        return -1;
    }

    fwrite(raster, sizeof(unsigned char), widthInBytes * heightInBytes, image);
    
    fclose(image);
    return 0;
}

int BITMAP_Image::loadFileImage(std::string file){
    FILE *image = fopen(file.c_str(), "rb");

    if(image == NULL){
        return -1;
    }

    if(f_header == NULL || inf_header == NULL){
        return -1;
    }

    if(fread(f_header, sizeof(BitMapFileHeader), 1, image)){
        if(feof(image)){
            return -1;
        }
    }else{
        return -1;
    }

    if(fread(inf_header, sizeof(BitMapInfoHeader), 1, image)){
        if(feof(image)){
            return -1;
        }
    }else{
        return -1;
    }

    if(fread(palette, sizeof(RGBQuad), BITMAP_PALETTE, image)){
        if(feof(image)){
            return -1;
        }
    }else{
        return -1;
    }

    widthInBytes = inf_header->Width * inf_header->BitCount / 8;
    heightInBytes = inf_header->Height * inf_header->BitCount / 8;

    raster = new unsigned char[heightInBytes * widthInBytes];

    if(!raster){
        return -1;
    }else{
        fread(raster, sizeof(unsigned char), widthInBytes * heightInBytes, image);
    }
    fclose(image);
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
    for(int i = 0; i < size; i++){
        for(int j = 0; j < widthInBytes; j++){
            raster[i * widthInBytes + j] = RGB_TO_SINGLE_BYTE(red, green, blue);//down side
            raster[widthInBytes*heightInBytes - widthInBytes - i*widthInBytes + j] = RGB_TO_SINGLE_BYTE(red, green, blue);//up side
        }

        for(int j = 0; j < heightInBytes; j++){
            raster[widthInBytes*j + i] = RGB_TO_SINGLE_BYTE(red, green, blue);//left side
            raster[widthInBytes*j + widthInBytes -i] = RGB_TO_SINGLE_BYTE(red, green, blue); //right side
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

    unsigned char **rasterMatrix = new unsigned char*[heightInBytes];
    for(uint16_t i = 0; i < heightInBytes; i++){
        rasterMatrix[i] = new unsigned char[widthInBytes];
    }


    for(uint16_t i = 0; i < heightInBytes; i++){//convert to matrix
        for(uint16_t j = 0; j < widthInBytes; j++){
            rasterMatrix[i][j] = raster[i*widthInBytes + j];
        }
    }
    for(uint16_t i = 0; i < rotationsAmount; i++){
        rasterMatrix = rotateMatrix(rasterMatrix, widthInBytes, heightInBytes);
    }

    for(uint16_t i = 0; i < heightInBytes; i++){//convert to single array
        for(uint16_t j = 0; j < widthInBytes; j++){
            raster[i*widthInBytes + j] = rasterMatrix[i][j];
        }
    }
    
    for(uint16_t i = 0; i < heightInBytes; i++){//delete old matrix
        delete[] rasterMatrix[i];
    }
    delete[] rasterMatrix;

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
        delete[] raster;
    }
}