Makefile is not yet ready so please follow these steps to compile the program:

1. Make sure that you have the libraries GL, GLEW, GLFW installed
2. Use the following command:
`g++ main.cpp -I/usr/include -L/usr/lib -lGL -lGLEW -lglfw -lwayland-client -lwayland-egl -lwayland-cursor`
or 
`g++ main.cpp -I/usr/include -L/usr/lib -lGL -lGLEW -lglfw -lX11`
3. If compilation does not occur then replace the paths of the -I and -L flags of where the header file directories and the libraries directories are stored in your system.
