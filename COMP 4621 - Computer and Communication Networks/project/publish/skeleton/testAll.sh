#! /bin/bash
for i in {1..5}
do
  echo "=====Test $i====="
  cp ./client.c ../test$i/
  cp ./server.c ../test$i/
  cd ../test$i
  chmod u+x ./test.sh
  ./test.sh
  rm ./client.c
  rm ./server.c
  cd ../skeleton
done

find .. -name test_client -delete
find .. -name test_server -delete
