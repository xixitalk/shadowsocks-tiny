CFLAGS += -g -Wall

.PHONY: all
all: sslocal sserver 

sslocal : client.c common.o crypto.o log.o tea.o
	$(CROSS_COMPILE)gcc -o $@ $(CFLAGS) $^ $(LDFLAGS) 

sserver : server.c common.o crypto.o log.o tea.o
	$(CROSS_COMPILE)gcc -o $@ $(CFLAGS) $^ $(LDFLAGS) 


.PHONY: clean
clean:
	rm -rf *.o sserver sslocal test
