CC=gcc
CLANG=clang
CFLAGS=-O2 -Werror -Wall -Wextra -Wconversion -Wvla -Wno-unused-result -Wpedantic -std=c11 -lm
CFLAGS_ASAN=-DDEBUG -g -fsanitize=address -fno-omit-frame-pointer -fno-sanitize-recover=all
CFLAGS_MSAN=-DDEBUG -g -fsanitize=memory -fno-omit-frame-pointer -fsanitize-memory-track-origins -fPIE -O2 -pie
CFLAGS_UBSAN=-DDEBUG -g -fsanitize=undefined,integer,bounds,float-divide-by-zero,implicit-conversion,float-cast-overflow,nullability -fno-omit-frame-pointer -fno-sanitize-recover=all
SOURCE=src/*.c

.PHONY: clean all

all: onecard

onecard: $(SOURCE)
	$(CC) -o onecard $(SOURCE) $(CFLAGS)

asan: $(SOURCE)
	$(CLANG) -o asan $(CFLAGS) $(CFLAGS_ASAN) $(SOURCE)

msan: $(SOURCE)
	$(CLANG) -o msan $(SOURCE) $(CFLAGS) $(CFLAGS_MSAN)

ubsan: $(SOURCE)
	$(CLANG) -o ubsan $(CFLAGS) $(CFLAGS_UBSAN) $(SOURCE)

clean:
	$(RM) src/*.o src/*~ onecard asan msan ubsan

