### If you wish to use extra libraries (math.h for instance),
### add their flags here (-lm in our case) in the "LIBS" variable.

LIBS = -lm
CC=gcc
###
CFLAGS  = -std=c99
CFLAGS += -g
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -pedantic
CFLAGS += -Werror
CFLAGS += -Wmissing-declarations
CFLAGS += -DUNITY_SUPPORT_64

ASANFLAGS  = -fsanitize=address
ASANFLAGS += -fno-common
ASANFLAGS += -fno-omit-frame-pointer

test: tests.out
	@./tests.out

memcheck: test/*.c src/*.c src/*.h
	@echo Compiling $@
	@$(CC) $(ASANFLAGS) $(CFLAGS) src/*.c test/vendor/unity.c test/*.c -o memcheck.out $(LIBS)
	@./memcheck.out
	@echo "Memory check passed"

tests.out: test/*.c src/*.c src/*.h
	@echo Compiling $@
	$(CC) $(CFLAGS) src/*.c test/vendor/unity.c test/*.c -o tests.out $(LIBS)

clang: test/*.c src/*.c src/*.h
	@echo Compiling with clang
	clang-tidy $(CFLAGS) src/*.c test/vendor/unity.c test/*.c -o tests.out $(LIBS)

gcov: test/*.c src/*.c src/*.h
	@echo Compiling with gcov
	gcc -fprofile-arcs -ftest-coverage $(CFLAGS) src/*.c test/vendor/unity.c test/*.c -o tests.out $(LIBS)
	./tests.out
	gcov acronym.c
	cat acronym.c.gcov | grep "####"


clean:
	rm -rf *.o *.out *.gcda *.gcno *.gcov *.out.dSYM html

dox:
	@echo Building documentation
	doxygen doxygen.cfg