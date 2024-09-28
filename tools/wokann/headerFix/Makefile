# Makefile

# 定义变量
CC = gcc
CFLAGS = -W"all" -W"extra" -std=c11

# 默认目标
all: headerFix


# 编译规则 
headerFix: headerFix.c
	$(CC) -g headerFix.c $(CFLAGS) -o headerFix.exe

# 清理规则
clean:
	rm -f headerFix.exe

