CC=g++
CFLAGS=-c 
LFLAGS=-g
OBJ_FOLDER=Obj/
BIN_FOLDER=Bin/
SRC_FOLDER=Sources/
LIBS_FOLDER=BMP_Modules/
EXECUTABLE=main

all: $(EXECUTABLE)

main.o: OBJ_DIR $(SRC_FOLDER)main.cpp
	$(CC) $(CFLAGS) $(SRC_FOLDER)main.cpp -o $(OBJ_FOLDER)$@ 


bitmap_lib.o: OBJ_DIR $(LIBS_FOLDER)BITMAP_Image.cpp
	$(CC) $(CFLAGS) $(LIBS_FOLDER)BITMAP_Image.cpp -o $(OBJ_FOLDER)$@

$(EXECUTABLE): BIN_DIR main.o bitmap_lib.o
	$(CC) $(OBJ_FOLDER)main.o $(OBJ_FOLDER)bitmap_lib.o -o $(BIN_FOLDER)$@ -lm

BIN_DIR:
	@if [ ! -d $(BIN_FOLDER) ]; then mkdir $(BIN_FOLDER); fi

OBJ_DIR:
	@if [ ! -d $(OBJ_FOLDER) ]; then mkdir $(OBJ_FOLDER); fi

clean:
	@if [ -d $(OBJ_FOLDER) ]; then rm -r $(OBJ_FOLDER); fi
	@if [ -d $(BIN_FOLDER) ]; then rm -r $(BIN_FOLDER); fi

run: all
	./$(BIN_FOLDER)$(EXECUTABLE)

