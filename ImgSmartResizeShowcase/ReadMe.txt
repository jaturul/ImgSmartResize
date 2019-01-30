This application showcases the smart (i.e. content-aware) resize 
functionality present in the Image Processing library. To build this
program, the following pre-requisites have to be satisfied (not necessary if pre-built libraries and copies of original headers are used):
(1) go to the ImageProcessing directory and follow the instructions
in ReadMe.txt to build the library.
(2) copy the resulting libImageProcessing.so file to the lib directory
in this project
(3) copy the directory ImageProcessing in ImageProcessing/include to 
ImgSmartResizeShowcase/include
(4) go to the lodepng directory and follow the instructions
in ReadMe.txt to build the library.
(5) copy the resulting liblodepng.so file to the thirdparty/lodepng/lib 
directory in this project
(6) copy the file lodepng.h in lodepng/include to 
ImgSmartResizeShowcase/thirdparty/include

When these pre-requisites have been fulfilled, to build the library, 
open the terminal in this directory and:
(1) cd build
(2) cmake .. && make
The application will be created in the bin directory. Instructions on how
to use it are contained in the "ReadMe" file present there.
