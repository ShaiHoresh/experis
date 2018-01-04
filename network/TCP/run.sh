port=$1
ip=$2

make
x-terminal-emulator -e ./ser $port
x-terminal-emulator -e ./cli $port $ip
