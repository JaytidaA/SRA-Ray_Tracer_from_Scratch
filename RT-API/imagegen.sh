g++ -o Vec4.o -c Vec4.cpp
g++ -o output main.cpp ./bin/Vec4.o
./output > image.ppm
rm output
open image.ppm