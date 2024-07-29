g++ -o bin/Vec4.o -c src/Vec4.cpp
g++ -o output main.cpp bin/Vec4.o
./output > image.ppm
rm output
open image.ppm