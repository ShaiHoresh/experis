#export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../../lib
#make

#gcc CdrGen.c -o CDRgen
#./CDRgen

gnome-terminal -x ./feeder/feeder
gnome-terminal -x ./processNstore/processor

mv ./feeder/cdrs/CDRFile0.cdr ./feeder/
mv ./feeder/cdrs/CDRFile1.cdr ./feeder/
mv ./feeder/cdrs/CDRFile2.cdr ./feeder/
mv ./feeder/cdrs/CDRFile3.cdr ./feeder/
mv ./feeder/cdrs/CDRFile4.cdr ./feeder/
mv ./feeder/cdrs/CDRFile5.cdr ./feeder/
