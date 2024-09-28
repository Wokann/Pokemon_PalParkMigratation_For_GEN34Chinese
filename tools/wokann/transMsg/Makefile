# Makefile

# 定义变量
CC = gcc
CFLAGS = -W"all" -W"extra" -std=c11 -g

SRC = transMsg.c headerMode.c mainMode.c footerMode.c
TARGET = transMsg

# 默认目标
all: $(TARGET)


# 编译规则 
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

# 清理规则
clean:
	rm -f $(TARGET)

