#!/bin/bash
gcc -o test_client client.c
gcc -o test_server server.c

cp test_client ./client1/
cp test_client ./client2/

./test_server > /dev/null 2>&1 &

cd ./client2/
./test_client < input.txt > /dev/null 2>&1 &
cd ..

cd ./client1/
./test_client < input.txt > /dev/null 2>&1 &
cd ..

sleep 10

diff ./client1/20.txt ./client2/20.txt

if [ $? -eq 0 ]; then
    echo "Succeed"
else
    echo "Fail"
fi

pkill test_client
pkill test_server
rm ./client1/20.txt
