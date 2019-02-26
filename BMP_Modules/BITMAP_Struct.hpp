#ifndef BMP_STRUCT
#define BMP_STRUCT
#include <stdint.h>

#define Y_GREY(R, G, B) (0.3 * R + 0.59 * G + 0.11 * B)
#define RGB_TO_SINGLE_BYTE(R, G, B)(((R/32) << 5) | ((G/32) << 2) | (B/64))

struct BitMapFileHeader{//14 bytes
    unsigned char Type[2];//Сигнатура ВМ
    unsigned char Size[4];//Размер файла
    unsigned char Reserved1[2];//Зарезервировано
    unsigned char Reserved2[2];//Зарезервировано
    unsigned char OffsetBits[4];//Смещение изображения от начала файла
};

struct BitMapInfoHeader{
    unsigned char Size[4];
    uint32_t Width;
    uint32_t Height;
    unsigned char Planes[2];
    uint16_t BitCount;
    unsigned char Compression[4];
    uint32_t SizeImage;
    unsigned char XpelsPerMeter[4];
    unsigned char YpelsPerMeter[4];
    unsigned char ColorsUsed[4];
    unsigned char ColorsImportant[4];
};

struct RGBQuad{
    unsigned char Blue;
    unsigned char Green;
    unsigned char Red;
    unsigned char Reserved;
};

#endif
