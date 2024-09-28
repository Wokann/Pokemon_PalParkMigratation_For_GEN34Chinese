#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include ".\include.h"

// 模式0：
// 头文件无数据
void footer_Mode_0(char* inputFile){
    // 打开文本文件
    FILE* input = fopen(inputFile, "rb");
    if (input == NULL) {
        perror("Input File open error.");
        return;
    }
    // 获得文本文件名并创建临时文件头"*_footer.temp"
    char inputFileName[256];
    char footerTempFile[256];
    strcpy(inputFileName, inputFile);               // 获取bin文件名
    inputFileName[strlen(inputFile)-4]=0;           // 去掉.bin后缀，获得纯文件名
    strcpy(footerTempFile,inputFileName);           //拷贝至新文件名
    strcat(footerTempFile,"_footer.temp");          // 添加后缀
    FILE* footerTemp = fopen(footerTempFile, "w");  // 创建并打开临时文件
    if (footerTemp == NULL){
        perror("footerTemp File create error.");
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

    //文件尾
    fprintf(footerTemp, "\n;文件尾\n");
    fprintf(footerTemp, "FooterOf_%s:\n",inputFileName);
    fprintf(footerTemp, ";无数据\n");
    fprintf(footerTemp, ".func EndOf_%s :: .endfunc\n",inputFileName);

    fclose(input);
    fclose(footerTemp);
}

// 模式1：
// 子文件末尾加一个单字节0xFF结束
// 已知适用游戏：Rockman_ZX_Advent_(jp)
void footer_Mode_1(char* inputFile){
    // 打开文本文件
    FILE* input = fopen(inputFile, "rb");
    if (input == NULL) {
        perror("Input File open error.");
        return;
    }
    // 获得文本文件名并创建临时文件头"*_footer.temp"
    char inputFileName[256];
    char footerTempFile[256];
    strcpy(inputFileName, inputFile);               // 获取bin文件名
    inputFileName[strlen(inputFile)-4]=0;           // 去掉.bin后缀，获得纯文件名
    strcpy(footerTempFile,inputFileName);           //拷贝至新文件名
    strcat(footerTempFile,"_footer.temp");          // 添加后缀
    FILE* footerTemp = fopen(footerTempFile, "w");  // 创建并打开临时文件
    if (footerTemp == NULL){
        perror("footerTemp File create error.");
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

    //文件尾
    fprintf(footerTemp, "\n;文件尾\n");
    fprintf(footerTemp, "FooterOf_%s:\n",inputFileName);
    fprintf(footerTemp, ".byte 0xFF\n");
    fprintf(footerTemp, ".func EndOf_%s :: .endfunc\n",inputFileName);

    fclose(input);
    fclose(footerTemp);
}

// 模式2：
// 待定
void footer_Mode_2(char* inputFile){
    // 打开文本文件
    FILE* input = fopen(inputFile, "rb");
    if (input == NULL) {
        perror("Input File open error.");
        return;
    }
    // 获得文本文件名并创建临时文件头"*_footer.temp"
    char inputFileName[256];
    char footerTempFile[256];
    strcpy(inputFileName, inputFile);               // 获取bin文件名
    inputFileName[strlen(inputFile)-4]=0;           // 去掉.bin后缀，获得纯文件名
    strcpy(footerTempFile,inputFileName);           //拷贝至新文件名
    strcat(footerTempFile,"_footer.temp");          // 添加后缀
    FILE* footerTemp = fopen(footerTempFile, "w");  // 创建并打开临时文件
    if (footerTemp == NULL){
        perror("footerTemp File create error.");
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

    //文件尾
    fprintf(footerTemp, "\n;文件尾\n");
    fprintf(footerTemp, "FooterOf_%s:\n",inputFileName);
    fprintf(footerTemp, ";\n");
    fprintf(footerTemp, ".func EndOf_%s :: .endfunc\n",inputFileName);

    fclose(input);
    fclose(footerTemp);
}