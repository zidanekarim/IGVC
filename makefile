default:	compile
compile runner: runner.o LinkedList.o
	@gcc -o runner.out runner.o LinkedList.o 
runner.o: runner.c LinkedList.h
	@gcc -w -c runner.c
LinekdList.o: LinkedList.c LinkedList.h
	@gcc -w -c LinkedList.c
run: runner
	@./runner.out
clean:
	rm -f *.o runner.out