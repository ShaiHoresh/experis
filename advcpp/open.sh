FILE=$1

mkdir $FILE
cp /home/shaihoresh/Desktop/work/advcpp/String/makefile ./$FILE
cp /home/saba/Desktop/work/advcpp/String/makefile ./$FILE
cd ./$FILE
touch $FILE.h test.cpp
gedit $FILE.h &
