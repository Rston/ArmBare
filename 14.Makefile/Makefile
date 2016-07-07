# 基本的Makefile示例
# 自动变量$@（规则的目标文件名）$<（规则的依赖文件名）$^（依赖的文件集合）

CC=gcc
TARGET=main
SRCS=$(wildcard *.c) 
OBJS=$(patsubst %.c, %.o, $(SRCS))

$(TARGET):$(OBJS)
	$(CC) -o $@  $^
%.o:%.c
	$(CC) -o $@ -c $<
			
clean:
	rm *.o $(TARGET)
