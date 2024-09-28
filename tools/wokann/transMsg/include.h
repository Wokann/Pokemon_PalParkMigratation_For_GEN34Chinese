#ifndef GUARD_INCLUDE_H
#define GUARD_INCLUDE_H

// 定义码表数据结构
struct CharMap{
    unsigned int hexValue;
    char* utf8Char;
};
void loadCharMap(char* charmapFile, struct CharMap** charmap, size_t* charmapSize);
void decodeBianryFileHeader(char* inputFile,char headerMode);
void decodeBinaryFileMain(char* inputFile, char* charmapFile, char headerMode, unsigned int endMarker);
void decodeBianryFileFooter(char* inputFile,char footerMode);
int joinMsg(char* inputFile);

void header_Mode_0(char* inputFile);
void header_Mode_1(char* inputFile);
void header_Mode_2(char* inputFile);
void header_Mode_3(char* inputFile);
void header_Mode_4(char* inputFile);
void header_Mode_5(char* inputFile);

void main_Mode_0(char* inputFile, char* charmapFile, unsigned int endMarker);
void main_Mode_1(char* inputFile, char* charmapFile, unsigned int endMarker);
void main_Mode_2(char* inputFile, char* charmapFile, unsigned int endMarker);
void main_Mode_3(char* inputFile, char* charmapFile, unsigned int endMarker);
void main_Mode_4(char* inputFile, char* charmapFile, unsigned int endMarker);
void main_Mode_5(char* inputFile, char* charmapFile, unsigned int endMarker);

void footer_Mode_0(char* inputFile);
void footer_Mode_1(char* inputFile);
void footer_Mode_2(char* inputFile);
void footer_Mode_3(char* inputFile);

#endif