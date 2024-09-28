#include <stdio.h>
#include <stdint.h>

#define NUM_HWORDS 8 // 设定要读取的 hword 数量

int main() {
    FILE *file;
    uint16_t hwordValue[NUM_HWORDS]; // hword 值的数组

    // 打开文件
    file = fopen("example.bin", "rb");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // 定位到文件位置
    fseek(file, 0, SEEK_SET); // 假设 hword 在文件中的偏移量为 4 字节

    // 从文件中批量读取小端格式的 hword
    fread(hwordValue, sizeof(uint16_t), NUM_HWORDS, file);

    // 关闭文件
    fclose(file);

    // 输出批量读取的 hword 值
    printf("Little-endian hword values:\n");
    for (int i = 0; i < NUM_HWORDS; i++) {
        printf("%04x\n", hwordValue[i]);
    }

    return 0;
}
