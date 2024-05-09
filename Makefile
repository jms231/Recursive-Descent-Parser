
EXECS=dcooke_parser


CC=gcc

MYFILE=RecParser.C


all: ${EXECS}

${EXECS}: ${MYFILE}
	${CC} -o ${EXECS} ${MYFILE}

clean:
	rm -f ${EXECS}
