#!/bin/sh
docker cp $2 $1:/test.cpp
docker exec -i $1 /bin/bash
g++ test.cpp -o /program || {exit && return 1}
docker cp $1:/program $3
exit
return 0
