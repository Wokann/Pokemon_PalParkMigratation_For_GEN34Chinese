#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include ".\include.h"

int main(int argc, char *argv[]) {
    //system("chcp 65001 & cls");

    char *inputFile = NULL;
    char *charmapFile = NULL;
    char headerMode = 0;
    char mainMode = 0;
    char footerMode = 0;
    unsigned int endMarker = 0;

    if (argc == 1) {
        printf("No option, use \'transMsg.exe -help\' to see usage.\n");
        printf("Press Enter to exit...");
        getchar();
        return 1;
    }

    for(int i = 1; i < argc;i++){
        if (strcmp(argv[i], "-i") == 0 && (i + 1) < argc){
            inputFile = argv[i + 1];
            i++;
        }
        else if (strcmp(argv[i], "-c") == 0 && (i + 1) < argc){
            charmapFile = argv[i + 1];
            i++;
        }
        else if (strcmp(argv[i], "-h") == 0 && (i + 1) < argc){
            headerMode = strtol(argv[i + 1], NULL, 10);
            i++;
        }
        else if (strcmp(argv[i], "-m") == 0 && (i + 1) < argc){
            mainMode = strtol(argv[i + 1], NULL, 10);
            i++;
        }
        else if (strcmp(argv[i], "-f") == 0 && (i + 1) < argc){
            footerMode = strtol(argv[i + 1], NULL, 10);;
            i++;
        }
        else if (strcmp(argv[i], "-em") == 0 && (i + 1) < argc){
            endMarker = strtol(argv[i + 1], NULL, 16);;
            //printf("0x%08x\n",endMarker);
            i++;
        }
        else if ( i==1 && strcmp(argv[i], "-help") == 0){
            printf("TransMsg tool made by wokann.(Version 20240409)\n");
            printf("Usage:\n");
            printf("\n");
            printf("    transMsg.exe -i inputFile -c charmapFile -h headerMode -m mainMode -f footerMode -em endMarker\n");
            printf("\n");
            printf("Standard option:\n");
            printf("    -i [inputBinaryFile]        Files need to be decode.\n");
            printf("    -c [charmapFile]            Files used to transfer hex to char, must be utf-8 encoding.\n");
            printf("    -h [headerMode]             Modes which Files used in header.\n");
            printf("    -h [mainMode]             Modes which Files used in main.\n");
            printf("    -f [footerMode]             Modes which Files used in footer.\n");
            printf("    -em [endMarker]          Hex Value marked for end.\n");
            printf("Another option:\n");
            printf("    -help                       show commnd usage.\n");
            printf("Press Enter to exit...");
            getchar();
            return 1;
        }
        else{
            printf("error option , use \'transMsg.exe -help\' to see usage.\n");
            printf("Press Enter to exit...");
            getchar();
            return 1;
        }
    }

    decodeBianryFileHeader(inputFile,headerMode);
    decodeBinaryFileMain(inputFile, charmapFile, mainMode, endMarker);
    decodeBianryFileFooter(inputFile,footerMode);
    joinMsg(inputFile);

    return 0;
}

// 函数用于加载码表数据
void loadCharMap(char* charmapFile, struct CharMap** charmap, size_t* charmapSize){
    FILE* file = fopen(charmapFile, "r");
    if (file == NULL){
        perror("Charmap File open error.");
        exit(EXIT_FAILURE);
    }
    size_t size = 0;                                        // 初始化码表大小
    struct CharMap* map = NULL;                             // 初始化码表结构
    char line[256];
    while (fgets(line, sizeof(line), file) != NULL){
        if (line[0] == '\n' || line[0] == '#'|| line[0] == ';')      // 跳过空行和注释
            continue;
        unsigned int hexValue;
        char utf8Char[256];
        char *newline = strchr(line, '\n');                 // 寻找换行符
        if (newline != NULL)
            *newline = '\0';                                // 将换行符替换为字符串结束符
        char *delimiter = strchr(line, '=');                // 寻找等号分隔符
        if (delimiter != NULL){
            *delimiter = '\0';                              // 将等号替换为字符串结束符
            if (sscanf(line, "%x", &hexValue) == 1){        // 将等号前面的内容作为十六进制数值拷贝到hexValue
                strcpy(utf8Char, delimiter + 1);            // 将等号后面的内容作为字符串拷贝到utf8Char
                size++;
                map = (struct CharMap*)realloc(map, size * sizeof(struct CharMap)); // 更新内存里map空间
                map[size - 1].hexValue = hexValue;          //存入码值
                map[size - 1].utf8Char = strdup(utf8Char);  //存入码值对应字符
            }
        }
    }
    fclose(file);
    *charmap = map;                                         // 写入码表
    *charmapSize = size;                                    // 写入码表条数
}

// 函数用于创建不同的文件头格式
void decodeBianryFileHeader(char* inputFile,char headerMode){
    switch(headerMode){
        case 0:
            header_Mode_0(inputFile);
            break;
        case 1:
            header_Mode_1(inputFile);
            break;
        case 2:
            header_Mode_2(inputFile);
            break;
        case 3:
            header_Mode_3(inputFile);
            break;
        case 4:
            header_Mode_4(inputFile);
            break;
        default:
            break;
    }
}

// 函数用于创建不同的文件正文格式
void decodeBinaryFileMain(char* inputFile, char* charmapFile, char mainMode, unsigned int endMarker){
    switch(mainMode){
        case 0:
            main_Mode_0(inputFile, charmapFile, endMarker);
            break;
        case 1:
            main_Mode_1(inputFile, charmapFile, endMarker);
            break;
        case 2:
            main_Mode_2(inputFile, charmapFile, endMarker);
            break;
        case 3:
            main_Mode_3(inputFile, charmapFile, endMarker);
            break;
        case 4:
            main_Mode_4(inputFile, charmapFile, endMarker);
            break;
        case 5:
            main_Mode_5(inputFile, charmapFile, endMarker);
            break;
        default:
            break;
    }
}

// 函数用于创建不同的文件尾格式
void decodeBianryFileFooter(char* inputFile,char footerMode){
    switch(footerMode){
        case 0:
            footer_Mode_0(inputFile);
            break;
        case 1:
            footer_Mode_1(inputFile);
            break;
        case 2:
            footer_Mode_2(inputFile);
            break;
        case 3:
            //footer_Mode_3(inputFile);
            break;
        default:
            break;
    }
}

int joinMsg(char* inputFile){
    // 打开临时文件"*_header.temp", "*_main.temp", "*_footer.temp"
    char inputFileName[256];
    char headerTempFile[256];
    char mainTempFile[256];
    char footerTempFile[256];
    strcpy(inputFileName, inputFile);               // 获取bin文件名
    inputFileName[strlen(inputFile)-4]=0;           // 去掉.bin后缀，获得纯文件名
    strcpy(headerTempFile,inputFileName);           // 拷贝至新文件名
    strcat(headerTempFile,"_header.temp");          // 添加后缀
    strcpy(mainTempFile,inputFileName);             // 拷贝至新文件名
    strcat(mainTempFile,"_main.temp");              // 添加后缀
    strcpy(footerTempFile,inputFileName);           // 拷贝至新文件名
    strcat(footerTempFile,"_footer.temp");          // 添加后缀
    //创建合并文件
    char joinTempFile[256];
    strcpy(joinTempFile,inputFileName);             // 拷贝至新文件名
    strcat(joinTempFile,".s");                      // 添加后缀
    FILE* joinTemp = fopen(joinTempFile, "w");
    if (joinTemp == NULL) {
        perror("Join File create error.");
        return;
    }

    //载入文件头
    FILE* headerTemp = fopen(headerTempFile, "r");
    if (headerTemp != NULL) {
        int c;
        while ((c = fgetc(headerTemp)) != EOF) {
            fputc(c, joinTemp);
        }
        fclose(headerTemp);
    } else {
        perror("headerTemp File open error.");
        return 1;
    }
    //载入文件正文
    FILE* mainTemp = fopen(mainTempFile, "r");
    if (mainTemp != NULL) {
        int c;
        while ((c = fgetc(mainTemp)) != EOF) {
            fputc(c, joinTemp);
        }
        fclose(mainTemp);
    } else {
        perror("mainTemp File open error.");
        return 1;
    }
    //载入文件尾
    FILE* footerTemp = fopen(footerTempFile, "r");
    if (footerTemp != NULL) {
        int c;
        while ((c = fgetc(footerTemp)) != EOF) {
            fputc(c, joinTemp);
        }
        fclose(footerTemp);
    } else {
        perror("footerTemp File open error.");
        return 1;
    }
    fclose(joinTemp);
    remove(headerTempFile);
    remove(mainTempFile);
    remove(footerTempFile);
}