
#把所有的目录做成变量，方便修改和移植 
BIN = ../bin
SRC = ../src
INC = ../include
OBJ = ../obj

#提取所有源文件(即：*.cc文件)和所有中间文件(即：*.o)
SOURCE = $(wildcard ${SRC}/*.cc)
OBJECT = $(patsubst %.cc,${OBJ}/%.o,$(notdir ${SOURCE}))

#设置最后目标文件
TARGET = my_player_test
BIN_TARGET = ${BIN}/${TARGET}

TARGET2 = my_player_main
BIN_TARGET2 = ${BIN}/${TARGET2}


CC = g++ 
CFLAGS = -g -Wall -I${INC} 

#用所有中间文件生成目的文件，规则中可以用 $^替换掉 ${OBJECT}

#生成各个中间文件
${OBJ}/%.o:${SRC}/%.cc 
	$(CC) $(CFLAGS) -o $@ -c $^

#根据所有的.o文件生成一个可执行文件
#${BIN_TARGET}:${OBJECT}	
#	$(CC) -o $@ $^

.PHONY:all
all:${BIN_TARGET} ${BIN_TARGET2}

${BIN_TARGET2}:${OBJ}/my_player_main.o ${OBJ}/my_player.o ${OBJ}/operate.o
	$(CC) -o $@ $^

${BIN_TARGET}:${OBJ}/my_player_test.o ${OBJ}/my_player.o ${OBJ}/operate.o
	$(CC) -o $@ $^


.PHONY:clean
clean:
	@find $(OBJ) -name *.o -exec rm -rf {} \; #这个是find命令，
	rm -rf $(BIN_TARGET)
	rm -rf ${BIN_TARGET2}



