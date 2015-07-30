## Makefile ##

## Macro defs
CC     = gcc
CFLAGS = -std=c99 -lrt
OFFSET = 0
ABI    = hard

SRC    = src
INC    = headers
BUILD  = build

## Build rules
pipeline:
	$(CC) -o $(BUILD)/pipeline.$(ABI) $(SRC)/pipeline.c $(CFLAGS) -mfloat-abi=$(ABI)

triad:
	$(CC) -o $(BUILD)/triad.$(ABI) $(SRC)/triad.c $(CFLAGS) -mfloat-abi=$(ABI)
