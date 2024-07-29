Hello everyone, this branch contains the code written by JaytidaA.

# Cherno's Tutorials
I am going through the YouTube videos of **The Cherno** about `OpenGL` and performing the programs which are performed by him.
## `Makefile` Usage
Currently there exist two `Makefiles`, the main one in the folder is used as follows (make sure that the includes and libraries are present in the correct paths):
```bash
make application
```
to create the `application` executable. This process produces a lot of object files as well so to remove them use the command:
```bash
make clean
```
and to remove the object files along with the produced executable, use:
```bash
make clean-all
```

## Videos
The videos folder also contains a `Makefile` which is used to produce executables of the results of the first few videos of the tutorial playlist. The `Makefile` is to be used as follows, make sure that the includes and libraries are present in the correct paths.
```bash
make <name-of-cpp-file-without-any-extensions>
```

# Tutorial Notes
I am trying to make a few Notes based on the knowledge I gain throughout the videos but most of the functions and constants have to be remembered through constant use and referral to the documentation for GLFW and GLEW.

# RT-API
The RT-API folder consists of an API Markdown file which explains the use of the API. The API is divided into the following folders: `include`, `src` and `bin` which contain the headers, imlpementations and the compiled binaries, respectively.

To generate an image, run the following command in your terminal.
```bash
./imagegen.sh
```