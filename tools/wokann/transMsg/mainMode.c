#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include ".\include.h"

// 模式0：
// 头文件无数据
// 纯文本文件，以文本结束符为依据截断子文本
void main_Mode_0(char* inputFile, char* charmapFile, unsigned int endMarker){
    // 打开文本文件
    FILE* input = fopen(inputFile, "rb");
    if (input == NULL){
        perror("Input File open error.");
        return;
    }
    // 获得文本文件名并创建临时正文文件"*_main.temp"
    char inputFileName[256];
    char mainTempFile[256];
    strcpy(inputFileName, inputFile);           // 获取bin文件名
    inputFileName[strlen(inputFile)-4]=0;       // 去掉.bin后缀，获得纯文件名
    strcpy(mainTempFile,inputFileName);         // 拷贝至新文件名
    strcat(mainTempFile,"_main.temp");          // 添加后缀
    FILE* mainTemp = fopen(mainTempFile, "w");  // 创建并打开临时文件
    if (mainTemp == NULL){
        perror("mainTemp File create error.");
        return;
    }
    //去除inputFileName的路径
    char* lastSlash = strrchr(inputFileName, '/'); // 找到最后一个 '/'
    char* lastBackslash = strrchr(inputFileName, '\\'); // 找到最后一个 '\'
    char* tempfileName = lastSlash > lastBackslash ? lastSlash : lastBackslash; // 选择最后一个分隔符
    if (tempfileName != NULL) {
        tempfileName++;                         // 将指针移动到文件名的起始位置（跳过路径分隔符）
        strcpy(inputFileName, tempfileName); // 将文件名部分复制回原始数组
    }

    //文件正文
    fprintf(mainTemp, "\n;文件正文\n");
    fprintf(mainTemp, "MainOf_%s:\n",inputFileName);

    // 加载码表
    size_t charmapSize;
    struct CharMap* charmap;
    loadCharMap(charmapFile, &charmap, &charmapSize);   // 读取码表，存入码值及对应字符

    // 制作文本指针列表
    unsigned int fileSize, textsCount, textsstarttemp;
    unsigned int *textsPointer = NULL;
    fseek(input, 0, SEEK_END);
    fileSize = ftell(input);
    fseek(input, 0, SEEK_SET);
    textsCount = 0;
    textsstarttemp = 0;
    while (ftell(input) < fileSize){
        // 读取多字节
        unsigned char buffer[3];
        size_t bytesRead = fread(buffer, sizeof(buffer[0]), sizeof(buffer), input);
        // hex检索码表
        unsigned int hexValueByte = 0, hexValueHalfWord = 0, hexValueWord = 0;
        unsigned int hexValue = 0;
        unsigned int Length = 1;// 未寻到码表时，步进1字节继续读取
        unsigned int select[3]={0,0,0}, temp[3]={0,0,0};
        hexValueByte = buffer[0];
        hexValueHalfWord = (buffer[0] << 8) | buffer[1];
        hexValueWord = (buffer[0] << 16) | (buffer[1] << 8) | buffer[2];
        // 检索单双三字节等码表
        for (size_t j = 0; j < charmapSize; j++){
            if (charmap[j].hexValue == hexValueByte && bytesRead >= 1){
                temp[0] = hexValueByte;
                select[0] = 1;
            }
            else if (charmap[j].hexValue == hexValueHalfWord && bytesRead >= 2){
                temp[1] = hexValueHalfWord;
                select[1] = 1;
            }
            else if (charmap[j].hexValue == hexValueWord && bytesRead >= 3){
                temp[2] = hexValueWord;
                select[2] = 1;
            }
            // 单双三字节等码表选择优先级别：
            // 单>双>三>……。用于应对诸如0x8B,0x008B,0x00008B等整数化后数值相同的值
            for (char m = 0; m < 3;m++){
                if(select[m] == 1){
                    hexValue = temp[m];
                    Length = m + 1;
                    break;
                }
            }
        }
        // 矫正指针位置
        fseek(input, Length - bytesRead, SEEK_CUR);
        if ((select[0]|select[1]|select[2] == 1) && (hexValue == endMarker)){
            textsCount++;
            textsPointer = realloc(textsPointer, (textsCount + 1) * sizeof(unsigned int));
            textsPointer[(textsCount - 1)] = textsstarttemp;    // 存入本条文本地址
            textsstarttemp = ftell(input);                      // 暂存下一条文本地址
            //printf("%d: %04x,%x.",textsCount,textsPointer[(textsCount - 1)],hexValue);
        }
    }
    textsPointer[textsCount] = fileSize;                    // 存入文件末尾字节
    //for(unsigned int i = 0; i < textsCount; i++) {
    //    printf("%d: %04x.",i,textsPointer[i]);
    //}
    // 根据文本指针列表提取子文本明文
    for (unsigned int i = 0; i < textsCount; i++) {
        // 转码第i条文本并暂存
        unsigned int OffsetNow,OffsetNext;
        unsigned char textBuffer[65536]={0};
        OffsetNow = textsPointer[i];
        OffsetNext = textsPointer[i+1];
        fseek(input,OffsetNow,SEEK_SET);
        while ((ftell(input) < OffsetNext) && (OffsetNow < fileSize)){  // 文本索引未指向下一文本地址
            // 读取多字节
            unsigned char buffer[3];
            size_t bytesRead = fread(buffer, sizeof(buffer[0]), sizeof(buffer), input);
            // hex检索码表
            unsigned int hexValueByte = 0, hexValueHalfWord = 0, hexValueWord = 0;
            unsigned int hexValue = 0;
            unsigned int Length = 1;// 未寻到码表时，步进1字节继续读取
            unsigned int select[3]={0,0,0}, temp[3]={0,0,0};
            hexValueByte = buffer[0];
            hexValueHalfWord = (buffer[0] << 8) | buffer[1];
            hexValueWord = (buffer[0] << 16) | (buffer[1] << 8) | buffer[2];
            char* utf8Char = NULL;
            // 检索单双三字节等码表
            for (size_t j = 0; j < charmapSize; j++){
                if (charmap[j].hexValue == hexValueByte && bytesRead >= 1){
                    utf8Char = charmap[j].utf8Char;
                    temp[0] = hexValueByte;
                    select[0] = 1;
                }
                else if (charmap[j].hexValue == hexValueHalfWord && bytesRead >= 2){
                    utf8Char = charmap[j].utf8Char;
                    temp[1] = hexValueHalfWord;
                    select[1] = 1;
                }
                else if (charmap[j].hexValue == hexValueWord && bytesRead >= 3){
                    utf8Char = charmap[j].utf8Char;
                    temp[2] = hexValueWord;
                    select[2] = 1;
                }
                // 单双三字节等码表选择优先级别：
                // 单>双>三>……。用于应对诸如0x8B,0x008B,0x00008B等整数化后数值相同的值
                for (char m = 0; m < 3;m++){
                    if(select[m] == 1){
                        hexValue = temp[m];
                        Length = m + 1;
                        break;
                    }
                }
            }
            // 存在码表
            if (utf8Char != NULL)
                strcat(textBuffer, utf8Char);
            // 不存在码表
            else{
                unsigned char nocharmap[1024]={0};
                sprintf(nocharmap, "[NoCharmap:0x%02X,or 0x%04X,or 0x%06X]",hexValueByte,hexValueHalfWord,hexValueWord);
                strcat(textBuffer,nocharmap);
            }
            // 长度检测
            if (strlen(textBuffer)>= 65536) {
                printf("textBuffer may Data overflow! Offset:%X\n",OffsetNow);
                break;
            }
            // 矫正指针位置
            fseek(input, Length - bytesRead, SEEK_CUR);
            // 文本检索到的hex值为文本结束符时，进行截断（可选）
            if ((select[0]|select[1]|select[2] == 1) && (hexValue == endMarker))
                break;
        }
        // 子文本标签，将第i条暂存文本写入原文区和译文区
        fprintf(mainTemp, "%s_%03d:\n", inputFileName,i);
        fprintf(mainTemp, ";原文－－－－－－－－－－－－－－－－－－－－－－\n");
        fprintf(mainTemp, ";   .strn \"%s\"\n",textBuffer);
        fprintf(mainTemp, ";译文－－－－－－－－－－－－－－－－－－－－－－\n");
        fprintf(mainTemp, "    .strn \"%s\"\n",textBuffer);
        fprintf(mainTemp, ";结束－－－－－－－－－－－－－－－－－－－－－－\n\n\n");
    }
    free(textsPointer);
    fclose(input);
    fclose(mainTemp);
    free(charmap);
}

// 模式1：
// 对应header_Mode1的文件头模式提取文本指针并输出文本
// 已知适用游戏：Rockman_ZX_Advent_(jp)
void main_Mode_1(char* inputFile, char* charmapFile, unsigned int endMarker){
    // 打开文本文件
    FILE* input = fopen(inputFile, "rb");
    if (input == NULL){
        perror("Input File open error.");
        return;
    }
    // 获得文本文件名并创建临时正文文件"*_main.temp"
    char inputFileName[256];
    char mainTempFile[256];
    strcpy(inputFileName, inputFile);           // 获取bin文件名
    inputFileName[strlen(inputFile)-4]=0;       // 去掉.bin后缀，获得纯文件名
    strcpy(mainTempFile,inputFileName);         // 拷贝至新文件名
    strcat(mainTempFile,"_main.temp");          // 添加后缀
    FILE* mainTemp = fopen(mainTempFile, "w");  // 创建并打开临时文件
    if (mainTemp == NULL){
        perror("mainTemp File create error.");
        return;
    }
    //去除inputFileName的路径
    char* lastSlash = strrchr(inputFileName, '/'); // 找到最后一个 '/'
    char* lastBackslash = strrchr(inputFileName, '\\'); // 找到最后一个 '\'
    char* tempfileName = lastSlash > lastBackslash ? lastSlash : lastBackslash; // 选择最后一个分隔符
    if (tempfileName != NULL) {
        tempfileName++;                         // 将指针移动到文件名的起始位置（跳过路径分隔符）
        strcpy(inputFileName, tempfileName); // 将文件名部分复制回原始数组
    }

    //文件正文
    fprintf(mainTemp, "\n;文件正文\n");
    fprintf(mainTemp, "MainOf_%s:\n",inputFileName);

    // 加载码表
    size_t charmapSize;
    struct CharMap* charmap;
    loadCharMap(charmapFile, &charmap, &charmapSize);   // 读取码表，存入码值及对应字符
    
    // 获得子文本数量
    unsigned int textsPointerDataSize, textsCount;
    fseek(input, 2, SEEK_SET);
    fread(&textsPointerDataSize,sizeof(unsigned short),1,input);
    textsCount = textsPointerDataSize / 2;
    // 获得子文本指针，并转为绝对地址
    unsigned int fileSize, textsBaseOffset;
    unsigned int *textsPointer = NULL;
    fseek(input, 0, SEEK_END);
    fileSize = ftell(input);
    textsBaseOffset = textsPointerDataSize + 4;
    textsPointer = malloc((textsCount + 1) * sizeof(unsigned short));
    if (textsPointer == NULL) {
        perror("Error allocating memory for textsPointer");
        exit(EXIT_FAILURE);
    }
    fseek(input, 4, SEEK_SET);
    fread(textsPointer, sizeof(unsigned short), textsCount, input);
    for (int i = 0; i < textsCount; i++) {
        textsPointer[i] += textsBaseOffset;
    }
    textsPointer[textsCount] = fileSize;
    // 根据文本指针列表提取子文本明文
    for (unsigned int i = 0; i < textsCount; i++) {
        // 转码第i条文本并暂存
        unsigned int OffsetNow,OffsetNext;
        unsigned char textBuffer[65536]={0};
        OffsetNow = textsPointer[i];
        OffsetNext = textsPointer[i+1];
        fseek(input,OffsetNow,SEEK_SET);
        while ((ftell(input) < OffsetNext) && (OffsetNow < fileSize)){  // 文本索引未指向下一文本地址
            // 读取多字节
            unsigned char buffer[3];
            size_t bytesRead = fread(buffer, sizeof(buffer[0]), sizeof(buffer), input);
            // hex检索码表
            unsigned int hexValueByte = 0, hexValueHalfWord = 0, hexValueWord = 0;
            unsigned int hexValue = 0;
            unsigned int Length = 1;// 未寻到码表时，步进1字节继续读取
            unsigned int select[3]={0,0,0}, temp[3]={0,0,0};
            hexValueByte = buffer[0];
            hexValueHalfWord = (buffer[0] << 8) | buffer[1];
            hexValueWord = (buffer[0] << 16) | (buffer[1] << 8) | buffer[2];
            char* utf8Char = NULL;
            // 检索单双三字节等码表
            for (size_t j = 0; j < charmapSize; j++){
                if (charmap[j].hexValue == hexValueByte && bytesRead >= 1){
                    utf8Char = charmap[j].utf8Char;
                    temp[0] = hexValueByte;
                    select[0] = 1;
                }
                else if (charmap[j].hexValue == hexValueHalfWord && bytesRead >= 2){
                    utf8Char = charmap[j].utf8Char;
                    temp[1] = hexValueHalfWord;
                    select[1] = 1;
                }
                else if (charmap[j].hexValue == hexValueWord && bytesRead >= 3){
                    utf8Char = charmap[j].utf8Char;
                    temp[2] = hexValueWord;
                    select[2] = 1;
                }
                // 单双三字节等码表选择优先级别：
                // 单>双>三>……。用于应对诸如0x8B,0x008B,0x00008B等整数化后数值相同的值
                for (char m = 0; m < 3;m++){
                    if(select[m] == 1){
                        hexValue = temp[m];
                        Length = m + 1;
                        break;
                    }
                }
            }
            // 存在码表
            if (utf8Char != NULL)
                strcat(textBuffer, utf8Char);
            // 不存在码表
            else{
                unsigned char nocharmap[1024]={0};
                sprintf(nocharmap, "[NoCharmap:0x%02X,or 0x%04X,or 0x%06X]",hexValueByte,hexValueHalfWord,hexValueWord);
                strcat(textBuffer,nocharmap);
            }
            // 长度检测
            if (strlen(textBuffer)>= 65536) {
                printf("textBuffer may Data overflow! Offset:%X\n",OffsetNow);
                break;
            }
            // 矫正指针位置
            fseek(input, Length - bytesRead, SEEK_CUR);
            // 文本检索到的hex值为文本结束符时，进行截断（可选）
            if ((select[0]|select[1]|select[2] == 1) && (hexValue == endMarker))
                break;
        }
        // 子文本标签，将第i条暂存文本写入原文区和译文区
        fprintf(mainTemp, "%s_%03d:\n", inputFileName,i);
        fprintf(mainTemp, ";原文－－－－－－－－－－－－－－－－－－－－－－\n");
        fprintf(mainTemp, ";   .strn \"%s\"\n",textBuffer);
        fprintf(mainTemp, ";译文－－－－－－－－－－－－－－－－－－－－－－\n");
        fprintf(mainTemp, "    .strn \"%s\"\n",textBuffer);
        fprintf(mainTemp, ";结束－－－－－－－－－－－－－－－－－－－－－－\n\n\n");
    }
    free(textsPointer);
    fclose(input);
    fclose(mainTemp);
    free(charmap);
}

// 模式2：
// 对应header_Mode2的文件头模式提取文本指针并输出文本
// 已知适用游戏：RuneFactory1_(jp)
void main_Mode_2(char* inputFile, char* charmapFile, unsigned int endMarker){
    // 打开文本文件
    FILE* input = fopen(inputFile, "rb");
    if (input == NULL){
        perror("Input File open error.");
        return;
    }
    // 获得文本文件名并创建临时正文文件"*_main.temp"
    char inputFileName[256];
    char mainTempFile[256];
    strcpy(inputFileName, inputFile);           // 获取bin文件名
    inputFileName[strlen(inputFile)-4]=0;       // 去掉.bin后缀，获得纯文件名
    strcpy(mainTempFile,inputFileName);         // 拷贝至新文件名
    strcat(mainTempFile,"_main.temp");          // 添加后缀
    FILE* mainTemp = fopen(mainTempFile, "w");  // 创建并打开临时文件
    if (mainTemp == NULL){
        perror("mainTemp File create error.");
        return;
    }
    //去除inputFileName的路径
    char* lastSlash = strrchr(inputFileName, '/'); // 找到最后一个 '/'
    char* lastBackslash = strrchr(inputFileName, '\\'); // 找到最后一个 '\'
    char* tempfileName = lastSlash > lastBackslash ? lastSlash : lastBackslash; // 选择最后一个分隔符
    if (tempfileName != NULL) {
        tempfileName++;                         // 将指针移动到文件名的起始位置（跳过路径分隔符）
        strcpy(inputFileName, tempfileName); // 将文件名部分复制回原始数组
    }

    //文件正文
    fprintf(mainTemp, "\n;文件正文\n");
    fprintf(mainTemp, "MainOf_%s:\n",inputFileName);

    // 加载码表
    size_t charmapSize;
    struct CharMap* charmap;
    loadCharMap(charmapFile, &charmap, &charmapSize);   // 读取码表，存入码值及对应字符
    
    // 获得子文本数量
    unsigned int textsPointerDataSize, textsCount;
    fseek(input, 4, SEEK_SET);
    fread(&textsPointerDataSize,sizeof(unsigned int),1,input);
    textsCount = textsPointerDataSize / 8;
    // 获得子文本指针，并转为绝对地址
    unsigned int fileSize, textsBaseOffset;
    unsigned int *textsPointer = NULL;
    fseek(input, 0, SEEK_END);
    fileSize = ftell(input);
    textsBaseOffset = 0;
    textsPointer = malloc((textsCount + 1) * sizeof(unsigned int));
    if (textsPointer == NULL) {
        perror("Error allocating memory for textsPointer");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < textsCount; i++) {
        fseek(input, (i * 8) + 4, SEEK_SET);
        fread(&textsPointer[i], sizeof(unsigned int), 1, input);
        textsPointer[i] += textsBaseOffset;
    }
    textsPointer[textsCount] = fileSize;
    //for(unsigned int i = 0; i <= textsCount; i++) {
    //    printf("%d: %04x,",i,textsPointer[i]);
    //}
    // 根据文本指针列表提取子文本明文
    for (unsigned int i = 0; i < textsCount; i++) {
        // 转码第i条文本并暂存
        unsigned int OffsetNow,OffsetNext;
        unsigned char textBuffer[65536]={0};
        OffsetNow = textsPointer[i];
        OffsetNext = textsPointer[i+1];
        fseek(input,OffsetNow,SEEK_SET);
        while ((ftell(input) < OffsetNext) && (OffsetNow < fileSize)){  // 文本索引未指向下一文本地址
            // 读取多字节
            unsigned char buffer[3];
            size_t bytesRead = fread(buffer, sizeof(buffer[0]), sizeof(buffer), input);
            // hex检索码表
            unsigned int hexValueByte = 0, hexValueHalfWord = 0, hexValueWord = 0;
            unsigned int hexValue = 0;
            unsigned int Length = 1;// 未寻到码表时，步进1字节继续读取
            unsigned int select[3]={0,0,0}, temp[3]={0,0,0};
            hexValueByte = buffer[0];
            hexValueHalfWord = (buffer[0] << 8) | buffer[1];
            hexValueWord = (buffer[0] << 16) | (buffer[1] << 8) | buffer[2];
            char* utf8Char = NULL;
            // 检索单双三字节等码表
            for (size_t j = 0; j < charmapSize; j++){
                if (charmap[j].hexValue == hexValueByte && bytesRead >= 1){
                    utf8Char = charmap[j].utf8Char;
                    temp[0] = hexValueByte;
                    select[0] = 1;
                }
                else if (charmap[j].hexValue == hexValueHalfWord && bytesRead >= 2){
                    utf8Char = charmap[j].utf8Char;
                    temp[1] = hexValueHalfWord;
                    select[1] = 1;
                }
                else if (charmap[j].hexValue == hexValueWord && bytesRead >= 3){
                    utf8Char = charmap[j].utf8Char;
                    temp[2] = hexValueWord;
                    select[2] = 1;
                }
                // 单双三字节等码表选择优先级别：
                // 单>双>三>……。用于应对诸如0x8B,0x008B,0x00008B等整数化后数值相同的值
                for (char m = 0; m < 3;m++){
                    if(select[m] == 1){
                        hexValue = temp[m];
                        Length = m + 1;
                        break;
                    }
                }
            }
            // 存在码表
            if (utf8Char != NULL)
                strcat(textBuffer, utf8Char);
            // 不存在码表
            else{
                unsigned char nocharmap[1024]={0};
                sprintf(nocharmap, "[NoCharmap:0x%02X,or 0x%04X,or 0x%06X]",hexValueByte,hexValueHalfWord,hexValueWord);
                strcat(textBuffer,nocharmap);
            }
            // 长度检测
            if (strlen(textBuffer)>= 65536) {
                printf("textBuffer may Data overflow! Offset:%X\n",OffsetNow);
                break;
            }
            // 矫正指针位置
            fseek(input, Length - bytesRead, SEEK_CUR);
            // 文本检索到的hex值为文本结束符时，进行截断（可选）
            if ((select[0]|select[1]|select[2] == 1) && (hexValue == endMarker))
                break;
        }
        // 子文本标签，将第i条暂存文本写入原文区和译文区
        fprintf(mainTemp, "%s_%03d:\n", inputFileName,i);
        fprintf(mainTemp, ";原文－－－－－－－－－－－－－－－－－－－－－－\n");
        fprintf(mainTemp, ";   .strn \"%s\"\n",textBuffer);
        fprintf(mainTemp, ";译文－－－－－－－－－－－－－－－－－－－－－－\n");
        fprintf(mainTemp, "    .strn \"%s\"\n",textBuffer);
        fprintf(mainTemp, ";结束－－－－－－－－－－－－－－－－－－－－－－\n\n\n");
    }
    free(textsPointer);
    fclose(input);
    fclose(mainTemp);
    free(charmap);
}

// 模式3：
// 对应header_Mode3的文件头模式提取文本指针并输出文本
// 已知适用游戏：RuneFactory1_(jp)-rfItemHelp.bin
void main_Mode_3(char* inputFile, char* charmapFile, unsigned int endMarker){
    // 打开文本文件
    FILE* input = fopen(inputFile, "rb");
    if (input == NULL){
        perror("Input File open error.");
        return;
    }
    // 获得文本文件名并创建临时正文文件"*_main.temp"
    char inputFileName[256];
    char mainTempFile[256];
    strcpy(inputFileName, inputFile);           // 获取bin文件名
    inputFileName[strlen(inputFile)-4]=0;       // 去掉.bin后缀，获得纯文件名
    strcpy(mainTempFile,inputFileName);         // 拷贝至新文件名
    strcat(mainTempFile,"_main.temp");          // 添加后缀
    FILE* mainTemp = fopen(mainTempFile, "w");  // 创建并打开临时文件
    if (mainTemp == NULL){
        perror("mainTemp File create error.");
        return;
    }
    //去除inputFileName的路径
    char* lastSlash = strrchr(inputFileName, '/'); // 找到最后一个 '/'
    char* lastBackslash = strrchr(inputFileName, '\\'); // 找到最后一个 '\'
    char* tempfileName = lastSlash > lastBackslash ? lastSlash : lastBackslash; // 选择最后一个分隔符
    if (tempfileName != NULL) {
        tempfileName++;                         // 将指针移动到文件名的起始位置（跳过路径分隔符）
        strcpy(inputFileName, tempfileName); // 将文件名部分复制回原始数组
    }

    //文件正文
    fprintf(mainTemp, "\n;文件正文\n");
    fprintf(mainTemp, "MainOf_%s:\n",inputFileName);

    // 加载码表
    size_t charmapSize;
    struct CharMap* charmap;
    loadCharMap(charmapFile, &charmap, &charmapSize);   // 读取码表，存入码值及对应字符
    
    //获得子文本数量
    unsigned int textsPointerDataSize, textsCount;
    fseek(input, 0, SEEK_SET);
    fread(&textsPointerDataSize,sizeof(unsigned int),1,input);
    textsCount = (textsPointerDataSize / 16) * 3;
    // 获得子文本指针，并转为绝对地址
    unsigned int fileSize, textsBaseOffset;
    unsigned int *textsPointer = NULL;
    fseek(input, 0, SEEK_END);
    fileSize = ftell(input);
    textsBaseOffset = 0;
    textsPointer = malloc((textsCount + 1) * sizeof(unsigned int));
    if (textsPointer == NULL) {
        perror("Error allocating memory for textsPointer");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < textsCount; i++) {
        fseek(input, (i/3) * 0x10, SEEK_SET);
        fread(&textsPointer[i], sizeof(unsigned int), 1, input);
        textsPointer[i] += textsBaseOffset;
        fseek(input, (i/3) * 0x10 + 4, SEEK_SET);
        fread(&textsPointer[i+1], sizeof(unsigned int), 1, input);
        textsPointer[i+1] += textsBaseOffset;
        textsPointer[i+1] += textsPointer[i];
        fseek(input, (i/3) * 0x10 + 8, SEEK_SET);
        fread(&textsPointer[i+2], sizeof(unsigned int), 1, input);
        textsPointer[i+2] += textsBaseOffset;
        textsPointer[i+2] += textsPointer[i+1];
        i += 2;
    }
    textsPointer[textsCount] = fileSize;
    //for(unsigned int i = 0; i <= textsCount; i++) {
    //    printf("%d: %04x,",i,textsPointer[i]);
    //}
    // 根据文本指针列表提取子文本明文
    unsigned char textBuffer[3][1024]={0};
    for (unsigned int i = 0; i < textsCount; i++) {
        if (i % 3 == 0)
            memset(textBuffer, 0, sizeof(textBuffer));
        // 转码第i条文本并暂存
        unsigned int OffsetNow,OffsetNext;
        OffsetNow = textsPointer[i];
        OffsetNext = textsPointer[i+1];
        fseek(input,OffsetNow,SEEK_SET);
        while ((ftell(input) < OffsetNext) && (OffsetNow < fileSize)){  // 文本索引未指向下一文本地址
            // 读取多字节
            unsigned char buffer[3];
            size_t bytesRead = fread(buffer, sizeof(buffer[0]), sizeof(buffer), input);
            // hex检索码表
            unsigned int hexValueByte = 0, hexValueHalfWord = 0, hexValueWord = 0;
            unsigned int hexValue = 0;
            unsigned int Length = 1;// 未寻到码表时，步进1字节继续读取
            unsigned int select[3]={0,0,0}, temp[3]={0,0,0};
            hexValueByte = buffer[0];
            hexValueHalfWord = (buffer[0] << 8) | buffer[1];
            hexValueWord = (buffer[0] << 16) | (buffer[1] << 8) | buffer[2];
            char* utf8Char = NULL;
            // 检索单双三字节等码表
            for (size_t j = 0; j < charmapSize; j++){
                if (charmap[j].hexValue == hexValueByte && bytesRead >= 1){
                    utf8Char = charmap[j].utf8Char;
                    temp[0] = hexValueByte;
                    select[0] = 1;
                }
                else if (charmap[j].hexValue == hexValueHalfWord && bytesRead >= 2){
                    utf8Char = charmap[j].utf8Char;
                    temp[1] = hexValueHalfWord;
                    select[1] = 1;
                }
                else if (charmap[j].hexValue == hexValueWord && bytesRead >= 3){
                    utf8Char = charmap[j].utf8Char;
                    temp[2] = hexValueWord;
                    select[2] = 1;
                }
                // 单双三字节等码表选择优先级别：
                // 单>双>三>……。用于应对诸如0x8B,0x008B,0x00008B等整数化后数值相同的值
                for (char m = 0; m < 3;m++){
                    if(select[m] == 1){
                        hexValue = temp[m];
                        Length = m + 1;
                        break;
                    }
                }
            }
            // 存在码表
            if (utf8Char != NULL)
                strcat(textBuffer[(i%3)], utf8Char);
            // 不存在码表
            else{
                unsigned char nocharmap[1024]={0};
                sprintf(nocharmap, "[NoCharmap:0x%02X,or 0x%04X,or 0x%06X]",hexValueByte,hexValueHalfWord,hexValueWord);
                strcat(textBuffer[(i%3)],nocharmap);
            }
            // 长度检测
            if (strlen(textBuffer[(i%3)])>= 1024) {
                system("chcp 65001");
                printf("textBuffer[%d] may Data overflow! Offset:%X\n",i%3,OffsetNow);
                printf("textBuffer[%d]:%s\n",i%3,textBuffer[(i%3)]);
                break;
            }
            // 矫正指针位置
            fseek(input, Length - bytesRead, SEEK_CUR);
            // 文本检索到的hex值为文本结束符时，进行截断（可选）
            if ((select[0]|select[1]|select[2] == 1) && (hexValue == endMarker))
                break;
        }
        // 子文本标签，将第i条暂存文本写入原文区和译文区
        if(i%3 == 2){
            fprintf(mainTemp, "%s_%03d:\n", inputFileName,i/3);
            fprintf(mainTemp, ";原文－－－－－－－－－－－－－－－－－－－－－－\n");
            fprintf(mainTemp, ";%s_%03d_0:\n", inputFileName,i/3);
            fprintf(mainTemp, ";   .strn \"%s\"\n",textBuffer[0]);
            fprintf(mainTemp, ";%s_%03d_1:\n", inputFileName,i/3);
            fprintf(mainTemp, ";   .strn \"%s\"\n",textBuffer[1]);
            fprintf(mainTemp, ";%s_%03d_2:\n", inputFileName,i/3);
            fprintf(mainTemp, ";   .strn \"%s\"\n",textBuffer[2]);
            fprintf(mainTemp, ";译文－－－－－－－－－－－－－－－－－－－－－－\n");
            fprintf(mainTemp, " %s_%03d_0:\n", inputFileName,i/3);
            fprintf(mainTemp, "    .strn \"%s\"\n",textBuffer[0]);
            fprintf(mainTemp, " %s_%03d_1:\n", inputFileName,i/3);
            fprintf(mainTemp, "    .strn \"%s\"\n",textBuffer[1]);
            fprintf(mainTemp, " %s_%03d_2:\n", inputFileName,i/3);
            fprintf(mainTemp, "    .strn \"%s\"\n",textBuffer[2]);
            fprintf(mainTemp, ";结束－－－－－－－－－－－－－－－－－－－－－－\n\n\n");
        }
    }
    free(textsPointer);
    fclose(input);
    fclose(mainTemp);
    free(charmap);
}

// 模式4：
// 对应header_Mode4的文件头模式提取文本指针并输出文本
// 已知适用游戏：RuneFactory1_(jp)-rfTxtSchedule.bin
void main_Mode_4(char* inputFile, char* charmapFile, unsigned int endMarker){
    // 打开文本文件
    FILE* input = fopen(inputFile, "rb");
    if (input == NULL){
        perror("Input File open error.");
        return;
    }
    // 获得文本文件名并创建临时正文文件"*_main.temp"
    char inputFileName[256];
    char mainTempFile[256];
    strcpy(inputFileName, inputFile);           // 获取bin文件名
    inputFileName[strlen(inputFile)-4]=0;       // 去掉.bin后缀，获得纯文件名
    strcpy(mainTempFile,inputFileName);         // 拷贝至新文件名
    strcat(mainTempFile,"_main.temp");          // 添加后缀
    FILE* mainTemp = fopen(mainTempFile, "w");  // 创建并打开临时文件
    if (mainTemp == NULL){
        perror("mainTemp File create error.");
        return;
    }
    //去除inputFileName的路径
    char* lastSlash = strrchr(inputFileName, '/'); // 找到最后一个 '/'
    char* lastBackslash = strrchr(inputFileName, '\\'); // 找到最后一个 '\'
    char* tempfileName = lastSlash > lastBackslash ? lastSlash : lastBackslash; // 选择最后一个分隔符
    if (tempfileName != NULL) {
        tempfileName++;                         // 将指针移动到文件名的起始位置（跳过路径分隔符）
        strcpy(inputFileName, tempfileName); // 将文件名部分复制回原始数组
    }

    //文件正文
    fprintf(mainTemp, "\n;文件正文\n");
    fprintf(mainTemp, "MainOf_%s:\n",inputFileName);

    // 加载码表
    size_t charmapSize;
    struct CharMap* charmap;
    loadCharMap(charmapFile, &charmap, &charmapSize);   // 读取码表，存入码值及对应字符
    
    // 获得子文本数量
    unsigned int textsPointerDataSize, textsCount;
    fseek(input, 4, SEEK_SET);
    fread(&textsPointerDataSize,sizeof(unsigned int),1,input);
    textsCount = textsPointerDataSize / 16;
    // 获得子文本指针，并转为绝对地址
    unsigned int fileSize, textsBaseOffset;
    unsigned int *textsPointer = NULL;
    fseek(input, 0, SEEK_END);
    fileSize = ftell(input);
    textsBaseOffset = 0;
    textsPointer = malloc((textsCount + 1) * sizeof(unsigned int));
    if (textsPointer == NULL) {
        perror("Error allocating memory for textsPointer");
        exit(EXIT_FAILURE);
    }
    for (unsigned int i = 0; i < textsCount; i++) {
        fseek(input, (i * 0x10) + 4, SEEK_SET);
        fread(&textsPointer[i], sizeof(unsigned int), 1, input);
        textsPointer[i] += textsBaseOffset;
    }
    textsPointer[textsCount] = fileSize;
    //for(unsigned int i = 0; i <= textsCount; i++) {
    //    printf("%d: %04x,",i,textsPointer[i]);
    //}
    // 根据文本指针列表提取子文本明文
    for (unsigned int i = 0; i < textsCount; i++) {
        // 转码第i条文本并暂存
        unsigned int OffsetNow,OffsetNext;
        unsigned char textBuffer[65536]={0};
        OffsetNow = textsPointer[i];
        OffsetNext = textsPointer[i+1];
        unsigned int textNext = 0;
        for (unsigned int j = 0;j < (textsCount - i);j++){
            if(textsPointer[i+1+j] != 0){
                textNext = textsPointer[i+1+j];
                break;
            }
        }
        //printf("%d: %04x,",i,textNext);
        fseek(input,OffsetNow,SEEK_SET);
        while ((ftell(input) < textNext) && (OffsetNow < fileSize)){  // 文本索引未指向下一文本地址
            if(OffsetNow == 0)
                break;
            // 读取多字节
            unsigned char buffer[3];
            size_t bytesRead = fread(buffer, sizeof(buffer[0]), sizeof(buffer), input);
            // hex检索码表
            unsigned int hexValueByte = 0, hexValueHalfWord = 0, hexValueWord = 0;
            unsigned int hexValue = 0;
            unsigned int Length = 1;// 未寻到码表时，步进1字节继续读取
            unsigned int select[3]={0,0,0}, temp[3]={0,0,0};
            hexValueByte = buffer[0];
            hexValueHalfWord = (buffer[0] << 8) | buffer[1];
            hexValueWord = (buffer[0] << 16) | (buffer[1] << 8) | buffer[2];
            char* utf8Char = NULL;
            // 检索单双三字节等码表
            for (size_t j = 0; j < charmapSize; j++){
                if (charmap[j].hexValue == hexValueByte && bytesRead >= 1){
                    utf8Char = charmap[j].utf8Char;
                    temp[0] = hexValueByte;
                    select[0] = 1;
                }
                else if (charmap[j].hexValue == hexValueHalfWord && bytesRead >= 2){
                    utf8Char = charmap[j].utf8Char;
                    temp[1] = hexValueHalfWord;
                    select[1] = 1;
                }
                else if (charmap[j].hexValue == hexValueWord && bytesRead >= 3){
                    utf8Char = charmap[j].utf8Char;
                    temp[2] = hexValueWord;
                    select[2] = 1;
                }
                // 单双三字节等码表选择优先级别：
                // 单>双>三>……。用于应对诸如0x8B,0x008B,0x00008B等整数化后数值相同的值
                for (char m = 0; m < 3;m++){
                    if(select[m] == 1){
                        hexValue = temp[m];
                        Length = m + 1;
                        break;
                    }
                }
            }
            // 存在码表
            if (utf8Char != NULL)
                strcat(textBuffer, utf8Char);
            // 不存在码表
            else{
                unsigned char nocharmap[1024]={0};
                sprintf(nocharmap, "[NoCharmap:0x%02X,or 0x%04X,or 0x%06X]",hexValueByte,hexValueHalfWord,hexValueWord);
                strcat(textBuffer,nocharmap);
            }
            // 长度检测
            if (strlen(textBuffer)>= 65536) {
                printf("textBuffer may Data overflow! Offset:%X\n",OffsetNow);
                break;
            }
            // 矫正指针位置
            fseek(input, Length - bytesRead, SEEK_CUR);
            // 文本检索到的hex值为文本结束符时，进行截断（可选）
            if ((select[0]|select[1]|select[2] == 1) && (hexValue == endMarker))
                break;
        }
        // 子文本标签，将第i条暂存文本写入原文区和译文区
        fprintf(mainTemp, "%s_%03d:\n", inputFileName,i);
        fprintf(mainTemp, ";原文－－－－－－－－－－－－－－－－－－－－－－\n");
        fprintf(mainTemp, ";   .strn \"%s\"\n",textBuffer);
        fprintf(mainTemp, ";译文－－－－－－－－－－－－－－－－－－－－－－\n");
        fprintf(mainTemp, "    .strn \"%s\"\n",textBuffer);
        fprintf(mainTemp, ";结束－－－－－－－－－－－－－－－－－－－－－－\n\n\n");
    }
    free(textsPointer);
    fclose(input);
    fclose(mainTemp);
    free(charmap);
}

// 模式5：
// 此模式为未解析清楚RuneFactory1_(jp)-event.bin的脚本语言的情况下
// 仅解码文本部分内容的模式，为固定地址，有限长度，暂不可动态变化。
// 以0x09为文本起始符，0x01为结束符（必定存在0x03 0x01结构）
// 已知适用游戏：RuneFactory1_(jp)-event.bin
void main_Mode_5(char* inputFile, char* charmapFile, unsigned int endMarker){
    // 打开文本文件
    FILE* input = fopen(inputFile, "rb");
    if (input == NULL){
        perror("Input File open error.");
        return;
    }
    // 获得文本文件名并创建临时正文文件"*_main.temp"
    char inputFileName[256];
    char mainTempFile[256];
    strcpy(inputFileName, inputFile);           // 获取bin文件名
    inputFileName[strlen(inputFile)-4]=0;       // 去掉.bin后缀，获得纯文件名
    strcpy(mainTempFile,inputFileName);         // 拷贝至新文件名
    strcat(mainTempFile,"_main.temp");          // 添加后缀
    FILE* mainTemp = fopen(mainTempFile, "w");  // 创建并打开临时文件
    if (mainTemp == NULL){
        perror("mainTemp File create error.");
        return;
    }
    //去除inputFileName的路径
    char* lastSlash = strrchr(inputFileName, '/'); // 找到最后一个 '/'
    char* lastBackslash = strrchr(inputFileName, '\\'); // 找到最后一个 '\'
    char* tempfileName = lastSlash > lastBackslash ? lastSlash : lastBackslash; // 选择最后一个分隔符
    if (tempfileName != NULL) {
        tempfileName++;                         // 将指针移动到文件名的起始位置（跳过路径分隔符）
        strcpy(inputFileName, tempfileName); // 将文件名部分复制回原始数组
    }

    //文件正文
    fprintf(mainTemp, "\n;文件正文\n");
    fprintf(mainTemp, "MainOf_%s:\n",inputFileName);

    // 加载码表
    size_t charmapSize;
    struct CharMap* charmap;
    loadCharMap(charmapFile, &charmap, &charmapSize);   // 读取码表，存入码值及对应字符
    
    // 制作文本指针列表
    unsigned int fileSize, textsCount, pointertemp, textcountstart;
    unsigned int *textsPointer = NULL;
    unsigned int *textsPointerEnd = NULL;
    fseek(input, 0, SEEK_END);
    fileSize = ftell(input);
    fseek(input, 0x60C, SEEK_SET);
    textsCount = 0;
    pointertemp = 0;
    textcountstart = 0;
    while (ftell(input) < fileSize){
        // 读取单字节
        unsigned char buffer[1];
        size_t bytesRead = fread(buffer, sizeof(buffer[0]), sizeof(buffer), input);
        unsigned int hexValueByte, hexValueHalfWord;
        hexValueByte = buffer[0];

        // 检查是否是0x09
        if (hexValueByte == 0x09){
            // 读取下一字节是否处于可取值范围
            bytesRead = fread(buffer, sizeof(buffer[0]), sizeof(buffer), input);
            hexValueByte = buffer[0];
            bytesRead = fread(buffer, sizeof(buffer[0]), sizeof(buffer), input);
            hexValueHalfWord = buffer[0] + (hexValueByte << 8);
            char* utf8Char = NULL;
            
            for (size_t j = 0; j < charmapSize; j++){
                if ((charmap[j].hexValue == hexValueHalfWord || charmap[j].hexValue == hexValueByte)&& hexValueByte !=0x03 && hexValueHalfWord != 0x03 && hexValueHalfWord != 0x4B00 && hexValueHalfWord != 0x5000 && hexValueHalfWord != 0xDC00){
                    printf("%d: %04x,",textsCount,hexValueHalfWord);
                    textsPointer = realloc(textsPointer, (textsCount + 1) * sizeof(unsigned int));
                    pointertemp = ftell(input) - 2;                     // 暂存文本起点地址
                    textsPointer[(textsCount)] = pointertemp;       // 存入本条文本地址
                    textcountstart = 1;
                }
            }
            fseek(input, -2, SEEK_CUR);
        }
        // 检查是否是0x03
        if(hexValueByte == 0x03 && textcountstart == 1){
            // 读取下一字节是否为0x01
            bytesRead = fread(buffer, sizeof(buffer[0]), sizeof(buffer), input);
            hexValueByte = buffer[0];
            if(hexValueByte == 0x01){
                textsPointerEnd = realloc(textsPointerEnd, (textsCount + 1) * sizeof(unsigned int));
                pointertemp = ftell(input) - 1;                 // 暂存文本终点地址
                textsPointerEnd[(textsCount)] = pointertemp;    // 存入本条文本地址
                printf("%d: S-%06x,E-%06x,%06x. ",textsCount,textsPointer[textsCount],textsPointerEnd[textsCount],ftell(input));
                textsCount++;
                textcountstart = 0;
            }
            fseek(input, -1, SEEK_CUR);
        }
    }
    //for(unsigned int i = 0; i <= textsCount; i++) {
    //    printf("%d: %04x,",i,textsPointer[i]);
    //}
    // 根据文本指针列表提取子文本明文
    for (unsigned int i = 0; i < textsCount; i++) {
        // 转码第i条文本并暂存
        unsigned int OffsetNow,OffsetNext;
        unsigned char textBuffer[65536]={0};
        OffsetNow = textsPointer[i];
        OffsetNext = textsPointerEnd[i];
        fseek(input,OffsetNow,SEEK_SET);
        while ((ftell(input) < OffsetNext)){  // 文本索引未指向下一文本地址
            // 读取多字节
            unsigned char buffer[3];
            size_t bytesRead = fread(buffer, sizeof(buffer[0]), sizeof(buffer), input);
            // hex检索码表
            unsigned int hexValueByte = 0, hexValueHalfWord = 0, hexValueWord = 0;
            unsigned int hexValue = 0;
            unsigned int Length = 1;// 未寻到码表时，步进1字节继续读取
            unsigned int select[3]={0,0,0}, temp[3]={0,0,0};
            hexValueByte = buffer[0];
            hexValueHalfWord = (buffer[0] << 8) | buffer[1];
            hexValueWord = (buffer[0] << 16) | (buffer[1] << 8) | buffer[2];
            char* utf8Char = NULL;
            // 检索单双三字节等码表
            for (size_t j = 0; j < charmapSize; j++){
                if (charmap[j].hexValue == hexValueByte && bytesRead >= 1){
                    utf8Char = charmap[j].utf8Char;
                    temp[0] = hexValueByte;
                    select[0] = 1;
                }
                else if (charmap[j].hexValue == hexValueHalfWord && bytesRead >= 2){
                    utf8Char = charmap[j].utf8Char;
                    temp[1] = hexValueHalfWord;
                    select[1] = 1;
                }
                else if (charmap[j].hexValue == hexValueWord && bytesRead >= 3){
                    utf8Char = charmap[j].utf8Char;
                    temp[2] = hexValueWord;
                    select[2] = 1;
                }
                // 单双三字节等码表选择优先级别：
                // 单>双>三>……。用于应对诸如0x8B,0x008B,0x00008B等整数化后数值相同的值
                for (char m = 0; m < 3;m++){
                    if(select[m] == 1){
                        hexValue = temp[m];
                        Length = m + 1;
                        break;
                    }
                }
            }
            // 存在码表
            if (utf8Char != NULL)
                strcat(textBuffer, utf8Char);
            // 不存在码表
            else{
                unsigned char nocharmap[1024]={0};
                sprintf(nocharmap, "[NoCharmap:0x%02X,or 0x%04X,or 0x%06X]",hexValueByte,hexValueHalfWord,hexValueWord);
                strcat(textBuffer,nocharmap);
            }
            // 长度检测
            if (strlen(textBuffer)>= 65536) {
                printf("textBuffer may Data overflow! Offset:%X\n",OffsetNow);
                break;
            }
            // 矫正指针位置
            fseek(input, Length - bytesRead, SEEK_CUR);
            // 文本检索到的hex值为文本结束符时，进行截断（可选）
            //if ((select[0]|select[1]|select[2] == 1) /*&& (hexValue == endMarker)*/)
            //   break;
        }
        // 子文本标签，将第i条暂存文本写入原文区和译文区
        
        fprintf(mainTemp, ".org 0x%06X\n", textsPointer[i]);
        fprintf(mainTemp, "%s_%03d:\n", inputFileName,i);
        fprintf(mainTemp, ".area %d,0\n",(textsPointerEnd[i]-textsPointer[i]));
        fprintf(mainTemp, ";原文－－－－－－－－－－－－－－－－－－－－－－\n");
        fprintf(mainTemp, ";   .strn \"%s\"\n",textBuffer);
        fprintf(mainTemp, ";译文－－－－－－－－－－－－－－－－－－－－－－\n");
        fprintf(mainTemp, "    .strn \"%s\"\n",textBuffer);
        fprintf(mainTemp, ";结束－－－－－－－－－－－－－－－－－－－－－－\n");
        fprintf(mainTemp, ".endarea\n\n\n");
        
        //fprintf(mainTemp, "%d,0x%06X,%d,.strn \"%s\"\n", i,textsPointer[i],(textsPointerEnd[i]-textsPointer[i]),textBuffer);
    }
    free(textsPointer);
    fclose(input);
    fclose(mainTemp);
    free(charmap);
}

