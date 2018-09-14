OBJ = ../obj
#LIB = -ldl -L../lib/ -lso1 -lso2 -lso3 -lpthread 
LIB = -fpic -rdynamic -ldl -pthread
BIN = ../bin

.PHONY:all
all:singleton_test find_file_test log_test read_conf_test framework_test

singleton_test:$(OBJ)/singleton_test.o $(OBJ)/singleton.o $(OBJ)/read_conf.o $(OBJ)/log.o
	g++ -o $@ $^
	mv singleton_test $(BIN)

find_file_test:$(OBJ)/find_file_test.o $(OBJ)/find_file.o $(OBJ)/read_conf.o
	g++ -o $@ $^
	mv find_file_test $(BIN)

log_test:$(OBJ)/log_test.o $(OBJ)/log.o $(OBJ)/read_conf.o
	g++ -o $@ $^
	mv log_test $(BIN)

read_conf_test:$(OBJ)/read_conf_test.o $(OBJ)/read_conf.o
	g++ -o $@ $^
	mv read_conf_test $(BIN)

framework_test:$(OBJ)/framework_test.o $(OBJ)/framework.o $(OBJ)/read_conf.o $(OBJ)/log.o $(OBJ)/find_file.o 
	g++ -o $@ $^ $(LIB)
	mv framework_test $(BIN) 
	
.PHONY:clean
clean:
	rm -f $(BIN)/singleton_test $(BIN)/find_file_test $(BIN)/log_test $(BIN)/read_conf_test $(BIN)/framework_test
