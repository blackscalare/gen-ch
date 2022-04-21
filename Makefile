.PHONY: clean

CC ?= gcc
SRC := main.c
BINS := gen-ch

all: build

build:
	@echo "Starting build..."
	${CC} -o ${BINS} ${SRC}
	@echo "Finished building"

clean:
	@echo "Cleaning up..."
	rm -f ${BINS}

install: build
	@echo "Installing gen-ch to /usr/bin/"
	mv ${BINS} /usr/bin/
