
FLAGS = -pedantic -Wall -Wconversion -ansi -g
LIB_PATH = ../
INC_PATH = ./




List : ListTest.c $(LIB_PATH)libList.a  
	gcc -o List $(FLAGS) ListTest.c $(LIB_PATH)libList.a 

	
 $(LIB_PATH)libList.a : List.o List_Itr.o List_Func.o
	ar -cvq libList.a List.o List_Itr.o List_Func.o
	mv libList.a ../

	
List.o : List.c List_Itr.c List_Func.c $(INC_PATH)List.h 
	gcc $(FLAGS) -c List.c  List_Itr.c List_Func.c

	
clean : 
	rm 	-f List.o List_Itr.o List_Func.o $(LIB_PATH)libList.a  List

	
	
	
