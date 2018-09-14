LIB = ../lib
INC = ../include
export LD_LIBRARY_PATH=/home/weienjun/viki/ConfiMent2/os/os1/os

.PHONY:all
all:so1 so2 so3

so1:so1.cc ../src/read_conf.cc 
	g++ -shared -fpic -o libso1.so so1.cc -I/readconf -I$(INC)
#	g++ -o $@ $^ -L. -los2 
so2:so2.cc ../src/read_conf.cc 
	g++ -shared -fpic -o libso2.so so2.cc -I/readconf -I$(INC)
#	g++ -o $@ $^ -L. -los2  

so3:so3.cc ../src/read_conf.cc 
	g++ -shared -fpic -o libso3.so so3.cc -I/readconf -I$(INC)
	mv libso1.so libso2.so libso3.so ../lib
.PHONY:clean
clean:
	rm -f  ../lib/*.so
