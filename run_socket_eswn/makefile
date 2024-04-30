
CFLAGS=-I /usr/include -DOS_LINUX -DNODEBUG_PRINT -DLINUX_KERNEL -DDEBUG_PRINT
LDFLAGS=-L /usr/lib 
#CXXFLAGS =-std=c++11
CXXFLAGS =-std=c++0x -Wall -O0  -g
all : clean zcu102_sender

zcu102_sender : *.cpp *.c
	g++ -m32 --static $^ -o $@ $(CFLAGS) $(LDFLAGS)  $(CXXFLAGS)

clean :
	@rm -rf zcu102_sender
	@rm -rf zcu102_sender.exe
