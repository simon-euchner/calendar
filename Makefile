# ---------------------------------------------------------------------------- #
#                                                                              #
# LICENSE NOTICE.                                                              #
#                                                                              #
#     LICENSES: GPL-3.0                                                        #
#                                                                              #
#     IMPORTANT: THIS IS FREE SOFTWARE WITHOUT ANY WARRANTY. THE USER IS FREE  #
#                TO MODIFY AND REDISTRIBUTE THIS SOFTWARE UNDER THE TERMS OF   #
#                THE LICENSE LISTED ABOVE PUBLISHED BY THE FREE SOFTWARE       #
#                FOUNDATION. THE PUBLISHER, SIMON EUCHNER, IS NOT RESPONSIBLE  #
#                FOR ANY NEGATIVE EFFECTS THIS SOFTWARE MAY CAUSE.             #
#                                                                              #
# ---------------------------------------------------------------------------- #
#                                                                              #
# Makefile for the calendar program *calendar* by Simon Euchner.               #
#                                                                              #
# ---------------------------------------------------------------------------- #


### Variables

# Compiler and Linker (GNU C compiler/linker)
CC = gcc
LD = gcc
FLAGS = -Wall -Wextra -std=c99
OLVL = -O1

# Paths
SRC = ./src.d
OBJ = ./obj.d
BIN = ./bin.d

# GTK-4.0 specific variables
CFLAGS = `pkg-config --cflags gtk4`
LIB = `pkg-config --libs gtk4`

# Target (binary *calendar*)
TARGET = ${BIN}/calendar

# Define file names
F1  = calendar
F2  = days
F3  = sett
F4  = csss
F5  = init
F6  = calh
F7  = call
F8  = dhcs
F9  = dtiw
F10 = dniw
F11 = mcdb

# Specify object code files
OBJ_FILENAMES = ${F1}.o ${F2}.o ${F3}.o ${F4}.o ${F5}.o ${F6}.o ${F7}.o ${F8}.o\
				${F9}.o ${F10}.o ${F11}.o
OBJ_FILES = ${foreach file, ${OBJ_FILENAMES}, ${OBJ}/${file}}


### Print info
all: ${TARGET}
	@echo -e "\nBuilding process completed successfully.\n\n\n"
	@echo -e "Running now *calendar*.\n"
	@${TARGET}
	@echo -e "\n"


### Link
${TARGET}: ${OBJ_FILES}
	${LD} ${FLAGS} ${OLVL} -o ${BIN}/calendar ${wildcard ${OBJ}/*.o} ${LIB}


### Compile

# calendar.c
${OBJ}/${F1}.o: ${SRC}/${F1}.c
	${CC} ${FLAGS} ${OLVL} ${CFLAGS} -o ${OBJ}/${F1}.o -c ${SRC}/${F1}.c

# days.c
${OBJ}/${F2}.o: ${SRC}/${F2}.c
	${CC} ${FLAGS} ${OLVL} -o ${OBJ}/${F2}.o -c ${SRC}/${F2}.c

# sett.c
${OBJ}/${F3}.o: ${SRC}/${F3}.c
	${CC} ${FLAGS} ${OLVL} -o ${OBJ}/${F3}.o -c ${SRC}/${F3}.c

# csss.c
${OBJ}/${F4}.o: ${SRC}/${F4}.c
	${CC} ${FLAGS} ${OLVL} ${CFLAGS} -o ${OBJ}/${F4}.o -c ${SRC}/${F4}.c

# init.c
${OBJ}/${F5}.o: ${SRC}/${F5}.c
	${CC} ${FLAGS} ${OLVL} ${CFLAGS} -o ${OBJ}/${F5}.o -c ${SRC}/${F5}.c

# calh.c
${OBJ}/${F6}.o: ${SRC}/${F6}.c
	${CC} ${FLAGS} ${OLVL} ${CFLAGS} -o ${OBJ}/${F6}.o -c ${SRC}/${F6}.c

# call.c
${OBJ}/${F7}.o: ${SRC}/${F7}.c
	${CC} ${FLAGS} ${OLVL} ${CFLAGS} -o ${OBJ}/${F7}.o -c ${SRC}/${F7}.c

# dhcs.c
${OBJ}/${F8}.o: ${SRC}/${F8}.c
	${CC} ${FLAGS} ${OLVL} ${CFLAGS} -o ${OBJ}/${F8}.o -c ${SRC}/${F8}.c

# dtiw.c
${OBJ}/${F9}.o: ${SRC}/${F9}.c
	${CC} ${FLAGS} ${OLVL} ${CFLAGS} -o ${OBJ}/${F9}.o -c ${SRC}/${F9}.c

# dniw.c
${OBJ}/${F10}.o: ${SRC}/${F10}.c
	${CC} ${FLAGS} ${OLVL} ${CFLAGS} -o ${OBJ}/${F10}.o -c ${SRC}/${F10}.c

# mcdb.c
${OBJ}/${F11}.o: ${SRC}/${F11}.c
	${CC} ${FLAGS} ${OLVL} ${CFLAGS} -o ${OBJ}/${F11}.o -c ${SRC}/${F11}.c


### Cleanup

clean:
	rm ${OBJ}/*.o
	rm ${BIN}/calendar

.PHONY: clean
