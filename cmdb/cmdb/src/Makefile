#目标文件
BIN =../bin
SRC = ../src ../test
INC = ../include
OBJ = ../obj

#一次获取目录下所有.cc文件
FILES = $(foreach dir,$(SRC),$(wildcard $(dir)/*.cc))
#将.cc文件替换为.o文件
OBJS = $(patsubst %.cc,%.o,$(FILES))

CC = g++
CFLAGS = -g -Wall -I$(INC)

TARGET = control_main
BIN_TARGET = $(BIN)/$(TARGET)

.PHONY:all
all:cgi $(OBJS) $(BIN_TARGET) cgb
LIB = -rdynamic -fpic -ldl -lpthread
#LIB = -ldl -L../lib/ -lso1 -lso2 -lso3 -lpthread
#根据类型生成依赖进而编译生成.o文件，并且存放到OBJ目录下
$(OBJS):%.o:%.cc
	$(CC) $(CFLAGS) -c -o $(OBJ)/$(notdir $@) $<  

#连接二进制文件生成程序
$(BIN_TARGET):$(OBJ)/control_main.o $(OBJ)/control.o $(OBJ)/singleton.o $(OBJ)/framework.o $(OBJ)/log.o $(OBJ)/read_conf.o $(OBJ)/find_file.o
	@$(CC) -o $@ $^ $(LIB) 

#编译生成动态库
cgi:
	@cd ../business; make clean; make; cd - 

#编译生成测试可执行文件
cgb:
	@cd ../test; make clean; make ; cd -;

#清除 
.PHONY:clean 
clean:
	-rm $(OBJ)/*.o
	-rm $(BIN)/control_main
	@cd ../test; make clean; cd -;
	@cd ../business; make clean; cd -;
