#include "BMP_Viewer.hpp"

BMP_Viewer::BMP_Viewer(std::string file) : BITMAP_Image(file){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
}

void BMP_Viewer::draw(float scale){
    glutInitWindowSize(widthInBytes, heightInBytes);
    glutInitWindowPosition(100, 100);
    win = glutCreateWindow(fileName.c_str());

    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, widthInBytes, 0, heightInBytes);
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    switch (BITMAP_PALETTE)
    {
        case 16:
            for(int i = 0; i < heightInBytes; i++){
                for(int j = 0; j < widthInBytes; j++){
                    int index = (int)raster[i][j];
                    float red = palette[index].Red;
                    float green = palette[index].Green;
                    float blue = palette[index].Blue;
                    putPixel(i, j, red/255, green/255, blue/255);
                }
            }
            break;
        case 256:
            for(int i = 0; i < heightInBytes; i++){
                for(int j = 0; j < widthInBytes; j++){
                    int index = (int)raster[i][j];
                    float red = palette[index].Red;
                    float green = palette[index].Green;
                    float blue = palette[index].Blue;
                    putPixel(i, j, red/255, green/255, blue/255);
                }
            }
            break;
        default:
            for(int i = 0; i < heightInBytes; i++){
                for(int j = 0; j < widthInBytes; j++){
                    float red = raster[i][j * 3 + 2];
                    float green = raster[i][j * 3 + 1];
                    float blue = raster[i][j * 3];
                    putPixel(i, j, red / 255, green / 255, blue / 255);
                }
            }
            break;
    }
    glEnd();
    glFlush();
    glutMainLoop();
}

void BMP_Viewer::putPixel(int X, int Y, float R, float G, float B){
    glColor3f(R, G, B);
    glVertex2i(Y, X);
}