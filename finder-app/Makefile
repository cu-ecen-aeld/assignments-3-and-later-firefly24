CROSS_COMPILE = $(CC)

all:	
ifeq ($(CROSS_COMPILE),aarch64-none-linux-gnu-)
	aarch64-none-linux-gnu-gcc writer.c -o writer
endif
ifeq ($(CROSS_COMPILE),cc)		
	$(CC) writer.c -o writer
endif
clean:
	rm -f writer *.o
