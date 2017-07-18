CC= arm-none-linux-gnueabi-gcc
PROJ_NAME = storage
INCLUDE_PATH = ./include
#LIB_PATH = ./lib
OBJS =	main.o
OBJS += pthread_refresh.o 
OBJS += test.o
OBJS += pthread_msg.o
OBJS += pthread_a9_uart_snd.o
OBJS += pthread_a9_uart_rev.o


CFLAG = -Wall   -I$(INCLUDE_PATH)   -lpthread


all: $(OBJS)
	$(CC)  $(CFLAG)  -o  $(PROJ_NAME) $(OBJS)
	cp $(PROJ_NAME) /source/rootfs/

$(OBJS):%.o: %.c
	$(CC)  $(CFLAG)  -c  -o   $@  $<

clean:
	rm -rf *.o $(PROJ_NAME) 

