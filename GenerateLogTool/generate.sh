echo Start to compile!
g++ -std=c++11 main.cpp -o generate.out
echo Start to genetate log file
./generate.out $1
echo Remove generate.out
rm generate.out