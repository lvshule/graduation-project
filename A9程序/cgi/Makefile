CC=arm-none-linux-gnueabi-gcc 
AFLAGS= -Wall  -L/home/lsl/xiangmu/sql-arm/lib -lsqlite3 -lpthread  -I./include -L./lib
 
OBJS=login.cgi m0_fan.cgi m0_beep.cgi m0_led.cgi m0_env.cgi m0_seg.cgi

all:$(OBJS)
	cp $(OBJS) /source/rootfs/www/cgi-bin/	
	

$(OBJS):%.cgi:%.c
	$(CC)  $< cgic.c -o $@ $(AFLAGS)

.PHONY:clean
clean:
	rm *.cgi 
	rm *.bak

