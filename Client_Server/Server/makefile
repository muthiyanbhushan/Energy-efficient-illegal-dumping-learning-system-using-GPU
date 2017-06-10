LDLIBS= -lpthread
all: output

output: errexit.c passivesock.c passiveTCP.c tcpserver.c
	gcc -Wall -Wextra errexit.c passivesock.c passiveTCP.c tcpserver.c -o output $(LDLIBS)

clean: 
	rm output
