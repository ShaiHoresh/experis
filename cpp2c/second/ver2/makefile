all: cppFile cFile
	@echo "to check the results, enter \"make test\""

cFile: cpp2c_v2.1_24-jul-2017.c
	gcc -ansi -pedantic -o cFile cpp2c_v2.1_24-jul-2017.c

cppFile: cpp2c_v2.1_24-jul-2017.cpp
	g++ -ansi -pedantic -o cppFile cpp2c_v2.1_24-jul-2017.cpp

run:
	./cFile

test:
	@ ./cFile > my.txt
	@ ./cppFile > your.txt
	@ diff my.txt your.txt > dif.txt
	cat dif.txt

gdb:
	gcc -ansi -pedantic -o cFile cpp2c_v2.1_24-jul-2017.c -g
	gdb ./cFile

clean:
	-rm -f cFile cppFile
	-rm -f *.txt
