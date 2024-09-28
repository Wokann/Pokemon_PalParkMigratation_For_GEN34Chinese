#include <stdio.h>
#include <stdint.h>
#include <string.h>

// CRC16 参数
#define CRC16_POLYNOMIAL 0xA001
#define INIT 0xFFFF

// 计算crc16
uint16_t calculateCRC16(uint8_t *data, size_t length) {
    uint16_t crc = INIT;

    static uint16_t CrcTable[256] = {};
    static int initialized = 0;
    int i;

    if (!initialized) {
        for (i = 0; i < 256; i++) {
            int c = i;
            for (int j = 0; j < 8; j++) {
                c = (c >> 1) ^ ((c & 1) ? CRC16_POLYNOMIAL : 0);
            }
            CrcTable[i] = c;
        }
        initialized = 1;
    }

    for (i = 0; i < length; i++) {
        crc = (crc >> 8) ^ CrcTable[(uint8_t)crc] ^ CrcTable[data[i]];
    }

    return crc;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <newNdsFileName> <originNdsFileName>\n", argv[0]);
        return 1;
    }

    const char *newFileName = argv[1];
    const char *originFileName = argv[2];
    FILE *newfile = fopen(newFileName, "rb+");
    if (newfile == NULL) {
        perror("Error opening file");
        return 1;
    }
    FILE *originfile = fopen(originFileName, "r");
    if (originfile == NULL) {
        perror("Error opening file");
        return 1;
    }

    //读取原rom头部数据
    uint8_t romversion[1]; 
    uint8_t normal_commands[4], KEY1_commands[4];
    fseek(originfile, 0x1E, SEEK_SET);
    fread(romversion, sizeof(uint8_t), 1, originfile);
    fseek(originfile, 0x60, SEEK_SET);
    fread(normal_commands, sizeof(uint8_t), 4, originfile);
    fseek(originfile, 0x64, SEEK_SET);
    fread(KEY1_commands, sizeof(uint8_t), 4, originfile);

    //写入新rom
    fseek(newfile, 0x1E, SEEK_SET);
    fwrite(&romversion, sizeof(uint8_t), 1, newfile);
    fseek(newfile, 0x60, SEEK_SET);
    fwrite(&normal_commands, sizeof(uint8_t), 4, newfile);
    fseek(newfile, 0x64, SEEK_SET);
    fwrite(&KEY1_commands, sizeof(uint8_t), 4, newfile);

    //读取头部数据 (0x0 - 0x15D)
    fseek(newfile, 0, SEEK_SET);
    uint8_t data[0x15E]; 
    fread(data, sizeof(uint8_t), 0x15E, newfile);

    // 计算头部crc16
    uint16_t crcResult = calculateCRC16(data, 0x15E);

    // 写入新crc16
    fseek(newfile, 0x15E, SEEK_SET);
    fwrite(&crcResult, sizeof(uint16_t), 1, newfile);

    fclose(newfile);
    fclose(originfile);

    printf("Header fix completed.\nNew header Chechsum (0x0-0x15D) CRC16 is: 0x%04X\n", crcResult);

    return 0;
}
