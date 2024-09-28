# Makefile

# 定义变量
CC = gcc
CFLAGS = -W"all" -W"extra" -std=c11

# 默认目标
all: test


# 编译规则 
test: test.c
	$(CC) -g test.c $(CFLAGS) -o test.exe

# 清理规则
clean:
	rm -f test.exe

