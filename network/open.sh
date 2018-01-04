FILE=$1

mkdir $FILE
cp ./UDP/makefile ./$FILE
cd ./$FILE
touch server.c client.c comm.c comm.h comm6.c comm6.h
gedit *.* &
