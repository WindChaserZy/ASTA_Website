unzip -o -q $1 -d .
make clean
make
mv work.exe $2


