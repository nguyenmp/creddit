LIBS+=-lcurl -I/usr/local/include/json-c 
TARGET=creddit
DAEMON=creddit-daemon
COMPILER=gcc
FLAGS=-g -Wall

compile: ${OBJS}
	${COMPILER} ${FLAGS} -o ${TARGET} main.c ${LIBS}
	${COMPILER} ${FLAGS} -o ${DAEMON} daemon.c ${LIBS}

%.o: %.c
	${COMPILER} -o $@ -c $<

clean:
	rm -rf ${OBJS} ${TARGET} ${DAEMON}
