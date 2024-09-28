# Makefile

# 设置 OpenSSL 变量(需额外安装openssl库)
OPENSSL_INCLUDE = "C:/openssl/include"
OPENSSL_LIB = "C:/openssl/lib"

# 定义变量
CC = gcc
CFLAGS = -W"all" -W"extra" -std=c11 -I$(OPENSSL_INCLUDE)
LDFLAGS = -L$(OPENSSL_LIB) -l"ssl" -l"crypto"

# 默认目标
all: hashCal

# 编译规则 
hashCal: hashCal.c
	$(CC) -g hashCal.c $(CFLAGS) $(LDFLAGS) -o hashCal.exe

# 清理规则
clean:
	rm -f hashCal.exe

