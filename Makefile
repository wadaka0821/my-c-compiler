CFLAGS = -std=c11 -g

mcc.out: mcc.c
	gcc-9 -o mcc.out mcc.c

test: mcc.out
	bash test.sh

clean:
	rm -f mcc.out *.o *~ tmp*

.PHONY: test clean