CC = gcc
CFLAGS = -g -Wall -w

%.o: %.c &.h
	$(CC) $(CFLAGS) -c $^


default:	compile
compile runner: runner.o LinkedList.o
	@$(CC) $(CFLAGS) -o $@ $^
runner.o: runner.c LinkedList.h
	@$(CC) $(CFLAGS) -w -c $^
LinekdList.o: LinkedList.c LinkedList.h
	@$(CC) $(CFLAGS) -c $^
run: runner
	@./runner
.PHONY: clean
clean:
	rm -f *.o runner.out