LIBS=-lcurl
TARGET=creddit
COMPILER=gcc
FLAGS=-g -Wall

compile: ${OBJS}
	${COMPILER} ${FLAGS} -o ${TARGET} main.c ${LIBS}

%.o: %.c
	${COMPILER} -o $@ -c $<

clean:
	rm -rf ${OBJS} ${TARGET}
