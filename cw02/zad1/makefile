all: main test

main: main.c
	gcc -Wall main.c -o main -g -O0 -fsanitize=undefined -lubsan

pies: main test

test:

	./main generate dane 4000 4	| tee -a wyniki.txt

	./main copy dane daneCopy 40000 4 sys	| tee -a wyniki.txt
	./main sort daneCopy 4000 4 sys	| tee -a wyniki.txt
	./main copy dane daneCopy 4000 4 lib	| tee -a wyniki.txt
	./main sort daneCopy 4000 4 lib	| tee -a wyniki.txt
	
	./main generate dane 4000 512	| tee -a wyniki.txt

	./main copy dane daneCopy 4000 512 sys	| tee -a wyniki.txt
	./main sort daneCopy 4000 512 sys	| tee -a wyniki.txt
	./main copy dane daneCopy 4000 512 lib	| tee -a wyniki.txt
	./main sort daneCopy 4000 512 lib	| tee -a wyniki.txt

	./main generate dane 4000 4096	| tee -a wyniki.txt

	./main copy dane daneCopy 4000 4096 sys	| tee -a wyniki.txt
	./main sort daneCopy 4000 4096 sys	| tee -a wyniki.txt
	./main copy dane daneCopy 4000 4096 lib	| tee -a wyniki.txt
	./main sort daneCopy 4000 4096 lib	| tee -a wyniki.txt

	./main generate dane 4000 8192	| tee -a wyniki.txt

	./main copy dane daneCopy 4000 8192 sys	| tee -a wyniki.txt
	./main sort daneCopy 4000 8192 sys	| tee -a wyniki.txt
	./main copy dane daneCopy 4000 8192 lib	| tee -a wyniki.txt
	./main sort daneCopy 4000 8192 lib	| tee -a wyniki.txt
            	
	echo "ZMIANA LICZBY REKORDOW W SORTOWANYM PLIKU" >> wyniki.txt

	./main generate dane 32000 4	| tee -a wyniki.txt

	./main copy dane daneCopy 32000 4 sys	| tee -a wyniki.txt
	./main sort daneCopy 3200 4 sys	| tee -a wyniki.txt
	./main copy dane daneCopy 32000 4 lib	| tee -a wyniki.txt
	./main sort daneCopy 3200 4 lib	| tee -a wyniki.txt
	
	./main generate dane 32000 512	| tee -a wyniki.txt

	./main copy dane daneCopy 32000 512 sys	| tee -a wyniki.txt
	./main sort daneCopy 32000 512 sys	| tee -a wyniki.txt
	./main copy dane daneCopy 32000 512 lib	| tee -a wyniki.txt
	./main sort daneCopy 32000 512 lib	| tee -a wyniki.txt

	./main generate dane 32000 4096	| tee -a wyniki.txt

	./main copy dane daneCopy 32000 4096 sys	| tee -a wyniki.txt
	./main sort daneCopy 32000 4096 sys	| tee -a wyniki.txt
	./main copy dane daneCopy 32000 4096 lib	| tee -a wyniki.txt
	./main sort daneCopy 32000 4096 lib	| tee -a wyniki.txt

	./main generate dane 32000 8192	| tee -a wyniki.txt

	./main copy dane daneCopy 32000 8192 sys	| tee -a wyniki.txt
	./main sort daneCopy 32000 8192 sys	| tee -a wyniki.txt
	./main copy dane daneCopy 32000 8192 lib	| tee -a wyniki.txt
	./main sort daneCopy 32000 8192 lib	| tee -a wyniki.txt
            	
clean:
	rm -r main