CC ?= gcc
CFLAGS ?= -Wall -Wextra -g   
LDFLAGS ?=                  

SRC_DIR = src
OBJ_DIR = build
TARGET = myapp             

# 自动获取所有.c文件并生成对应的.o文件路径
SRCS = $(wildcard $(SRC_DIR)/*.c) 
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# 默认目标：编译可执行文件
all: $(TARGET)

# 链接目标文件生成可执行程序
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

# 编译每个.c文件到.o文件，并自动创建目标目录
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)  # 自动创建目标目录（如果不存在）
	$(CC) $(CFLAGS) -c $< -o $@

run:$(TARGET)
	./myapp

# 清理生成的文件
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# 声明伪目标（不生成实际文件）
.PHONY: all clean
