echo Start to compile!
g++ -std=c++11 main.cpp -o query.out
./query.out $1
echo Remove query.out
rm query.out

