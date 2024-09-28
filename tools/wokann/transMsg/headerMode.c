#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include ".\include.h"

// 模式0：
// 头文件无数据
void header_Mode_0(char* inputFile){
    // 打开文本文件
    FILE* input = fopen(inputFile, "rb");
    if (input == NULL) {
        perror("Input File open error.");
        return;
    }
    // 获得文本文件名并创建临时文件"*_header.temp"
    char inputFileName[256];
    char headerTempFile[256];
    strcpy(inputFileName, inputFile);               // 获取bin文件名
    inputFileName[strlen(inputFile)-4]=0;           // 去掉.bin后缀，获得纯文件名
    strcpy(headerTempFile,inputFileName);           // 拷贝至新文件名
    strcat(headerTempFile,"_header.temp");          // 添加后缀
    FILE* headerTemp = fopen(headerTempFile, "w");  // 创建并打开临时文件
    if (headerTemp == NULL){
        perror("headerTemp File create error.");
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

    //文件头
    fprintf(headerTemp, ".func StartOf_%s :: .endfunc\n",inputFileName);
    fprintf(headerTemp, ";文件头\n");
    fprintf(headerTemp, "HeaderOf_%s:\n",inputFileName);
    fprintf(headerTemp, ";无数据\n");

    fclose(input);
    fclose(headerTemp);
}

// 模式1：
// .hword 除文件头外文件大小, 
// .hword 子文本指针区长度。可用于计算文本数量、正文起点绝对地址。子文本指针区长度+4=文件正文起点绝对地址。
// .hword 子文本指针区。以首条文本为起点地址计算。
// 已知适用游戏：Rockman_ZX_Advent_(jp)
void header_Mode_1(char* inputFile){
    // 打开文本文件
    FILE* input = fopen(inputFile, "rb");
    if (input == NULL) {
        perror("Input File open error.");
        return;
    }
    // 获得文本文件名并创建临时文件"*_header.temp"
    char inputFileName[256];
    char headerTempFile[256];
    strcpy(inputFileName, inputFile);               // 获取bin文件名
    inputFileName[strlen(inputFile)-4]=0;           // 去掉.bin后缀，获得纯文件名
    strcpy(headerTempFile,inputFileName);           // 拷贝至新文件名
    strcat(headerTempFile,"_header.temp");          // 添加后缀
    FILE* headerTemp = fopen(headerTempFile, "w");  // 创建并打开临时文件
    if (headerTemp == NULL){
        perror("headerTemp File create error.");
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

    //文件头
    fprintf(headerTemp, ".func StartOf_%s :: .endfunc\n",inputFileName);
    fprintf(headerTemp, ";文件头\n");
    fprintf(headerTemp, "HeaderOf_%s:\n",inputFileName);
    
    //获得子文本数量
    unsigned int textsPointerDataSize, textsCount;
    fseek(input, 2, SEEK_SET);
    fread(&textsPointerDataSize,sizeof(unsigned short),1,input);
    textsCount = textsPointerDataSize / 2;
    fprintf(headerTemp, ".hword (EndOf_%s - 4)   ;子文本指针区起的文件大小\n",inputFileName);
    fprintf(headerTemp, ".hword 0x%04x          ;子文本指针区长度。总计%d条文本\n",textsPointerDataSize,textsCount);
    fprintf(headerTemp, ";子文本指针区（以首条文本起点为基点地址计算）\n");
    for(int i = 0;i<textsCount;i++)
        fprintf(headerTemp, ".hword (%s_%03d -%s_000)\n",inputFileName,i,inputFileName);

    fclose(input);
    fclose(headerTemp);
}

// 模式2：
// .word 文本长度（不计入结束符）,文本绝对地址
// 已知适用游戏：RuneFactory1_(jp)
void header_Mode_2(char* inputFile){
    // 打开文本文件
    FILE* input = fopen(inputFile, "rb");
    if (input == NULL) {
        perror("Input File open error.");
        return;
    }
    // 获得文本文件名并创建临时文件"*_header.temp"
    char inputFileName[256];
    char headerTempFile[256];
    strcpy(inputFileName, inputFile);               // 获取bin文件名
    inputFileName[strlen(inputFile)-4]=0;           // 去掉.bin后缀，获得纯文件名
    strcpy(headerTempFile,inputFileName);           // 拷贝至新文件名
    strcat(headerTempFile,"_header.temp");          // 添加后缀
    FILE* headerTemp = fopen(headerTempFile, "w");  // 创建并打开临时文件
    if (headerTemp == NULL){
        perror("headerTemp File create error.");
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

    //文件头
    fprintf(headerTemp, ".func StartOf_%s :: .endfunc\n",inputFileName);
    fprintf(headerTemp, ";文件头\n");
    fprintf(headerTemp, "HeaderOf_%s:\n",inputFileName);
    
    //获得子文本数量
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
    int j=0;
    for(int i = 0;i<textsCount;i++){
        if (textsPointer[i] < textsPointer[textsCount]){
            if (i < textsCount - 1)
                fprintf(headerTemp, ".word (%s_%03d - %s_%03d - 1),%s_%03d\n",inputFileName,i+1,inputFileName,i,inputFileName,i);
            else if (i = textsCount - 1)
                fprintf(headerTemp, ".word (FooterOf_%s - %s_%03d - 1),%s_%03d\n",inputFileName,inputFileName,i,inputFileName,i);
        }
        else if (textsPointer[i] >= textsPointer[textsCount]){
            fprintf(headerTemp, ".word 0, EndOf_%s + %d\n",inputFileName,j);
            j++;
        }
    }

    fclose(input);
    fclose(headerTemp);
}

// 模式3：
// .word 一组三行文本起点绝对地址, 第一行文本长度，第二行文本长度, 第三行文本长度（均计入结束符）
// 已知适用游戏：RuneFactory1_(jp)-rfItemHelp.bin
void header_Mode_3(char* inputFile){
    // 打开文本文件
    FILE* input = fopen(inputFile, "rb");
    if (input == NULL) {
        perror("Input File open error.");
        return;
    }
    // 获得文本文件名并创建临时文件"*_header.temp"
    char inputFileName[256];
    char headerTempFile[256];
    strcpy(inputFileName, inputFile);               // 获取bin文件名
    inputFileName[strlen(inputFile)-4]=0;           // 去掉.bin后缀，获得纯文件名
    strcpy(headerTempFile,inputFileName);           // 拷贝至新文件名
    strcat(headerTempFile,"_header.temp");          // 添加后缀
    FILE* headerTemp = fopen(headerTempFile, "w");  // 创建并打开临时文件
    if (headerTemp == NULL){
        perror("headerTemp File create error.");
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

    //文件头
    fprintf(headerTemp, ".func StartOf_%s :: .endfunc\n",inputFileName);
    fprintf(headerTemp, ";文件头\n");
    fprintf(headerTemp, "HeaderOf_%s:\n",inputFileName);

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
        textsPointer[i+2] += textsPointer[i];
        i += 2;
    }
    textsPointer[textsCount] = fileSize;

    int j=0;
    for(int i = 0;i<textsCount;i++){
        if (textsPointer[i] < textsPointer[textsCount]){
            fprintf(headerTemp, ".word %s_%03d",inputFileName,(i/3));
            fprintf(headerTemp, ", (%s_%03d_1 - %s_%03d_0)",inputFileName,(i/3),inputFileName,(i/3));
            fprintf(headerTemp, ", (%s_%03d_2 - %s_%03d_1)",inputFileName,(i/3),inputFileName,(i/3));
            if ((textsCount - i) > 3)
                fprintf(headerTemp, ", (%s_%03d - %s_%03d_2)\n",inputFileName,(i/3)+1,inputFileName,(i/3));
            else if ((textsCount - i) <= 3)
                fprintf(headerTemp, ", (FooterOf_%s - %s_%03d_2)\n",inputFileName,inputFileName,(i/3));
        }
        else if (textsPointer[i] >= textsPointer[textsCount]){
            fprintf(headerTemp, ".word EndOf_%s,0,0,0\n",inputFileName);
        }
        i += 2;
    }

    fclose(input);
    fclose(headerTemp);
}

// 模式4：
// .word 文本长度（不计入结束符）,文本绝对地址,0,0
// .word 0,0,0,0
// 已知适用游戏：RuneFactory1_(jp)-rfTxtSchedule.bin
void header_Mode_4(char* inputFile){
    // 打开文本文件
    FILE* input = fopen(inputFile, "rb");
    if (input == NULL) {
        perror("Input File open error.");
        return;
    }
    // 获得文本文件名并创建临时文件"*_header.temp"
    char inputFileName[256];
    char headerTempFile[256];
    strcpy(inputFileName, inputFile);               // 获取bin文件名
    inputFileName[strlen(inputFile)-4]=0;           // 去掉.bin后缀，获得纯文件名
    strcpy(headerTempFile,inputFileName);           // 拷贝至新文件名
    strcat(headerTempFile,"_header.temp");          // 添加后缀
    FILE* headerTemp = fopen(headerTempFile, "w");  // 创建并打开临时文件
    if (headerTemp == NULL){
        perror("headerTemp File create error.");
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

    //文件头
    fprintf(headerTemp, ".func StartOf_%s :: .endfunc\n",inputFileName);
    fprintf(headerTemp, ";文件头\n");
    fprintf(headerTemp, "HeaderOf_%s:\n",inputFileName);

    //获得子文本数量
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
    for (int i = 0; i < textsCount; i++) {
        fseek(input, (i * 0x10) + 4, SEEK_SET);
        fread(&textsPointer[i], sizeof(unsigned int), 1, input);
        textsPointer[i] += textsBaseOffset;
    }
    textsPointer[textsCount] = fileSize;
    for(int i = 0;i<textsCount;i++){
        if (textsPointer[i] < textsPointer[textsCount] && textsPointer[i] != 0){
            if (i < textsCount - 1)
                fprintf(headerTemp, ".word (%s_%03d - %s_%03d - 1),%s_%03d,0,0\n",inputFileName,i+1,inputFileName,i,inputFileName,i);
            else if (i = textsCount - 1)
                fprintf(headerTemp, ".word (FooterOf_%s - %s_%03d - 1),%s_%03d,0,0\n",inputFileName,inputFileName,i,inputFileName,i);
        }
        else if (textsPointer[i] >= textsPointer[textsCount] || (textsPointer[i] == 0)){
            fprintf(headerTemp, ".word 0,0,0,0\n");
        }
    }

    fclose(input);
    fclose(headerTemp);
}

// 模式5：
// 待定
void header_Mode_5(char* inputFile){
    // 打开文本文件
    FILE* input = fopen(inputFile, "rb");
    if (input == NULL) {
        perror("Input File open error.");
        return;
    }
    // 获得文本文件名并创建临时文件"*_header.temp"
    char inputFileName[256];
    char headerTempFile[256];
    strcpy(inputFileName, inputFile);               // 获取bin文件名
    inputFileName[strlen(inputFile)-4]=0;           // 去掉.bin后缀，获得纯文件名
    strcpy(headerTempFile,inputFileName);           // 拷贝至新文件名
    strcat(headerTempFile,"_header.temp");          // 添加后缀
    FILE* headerTemp = fopen(headerTempFile, "w");  // 创建并打开临时文件
    if (headerTemp == NULL){
        perror("headerTemp File create error.");
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

    //文件头
    fprintf(headerTemp, ".func StartOf_%s :: .endfunc\n",inputFileName);
    fprintf(headerTemp, ";文件头\n");
    fprintf(headerTemp, "HeaderOf_%s:\n",inputFileName);

    fclose(input);
    fclose(headerTemp);
}