The application takes an input image (and, optionally, a mask marking high priority areas with green and low priority areas with red), changes size to the target one and saves the result in the output file. If the debug mode is enabled, an image path has to be provided. As a result, images with seams marked on them will be saved so that it's possible to examine how the algorithm worked. 

Please keep in mind that at the moment, only RGB images with the "png" extension are considered valid input. Also, enlargening the image has not been implemented yet, so only target dimensions smaller than the original one are accepted.

This application accepts input in the following way. After the app name, a tag has to be provided followed by a correct value of that tag. Acceptable tags are:
(1) "-s" which specifies target output size; expected value follows the  "heightxwidth" pattern (e.g. "200x200")
 
(2) "-i" which specifies the input file (which has to exist on disk!);  a path containing a folder can be provided, but it has to be to a folder  in the "bin" directory! Example: "images/beach.png", assuming that the  "images" folder is present in "bin". At the moment, only RGB images with the png extension are considered valid input.
 
(3) "-o" which specifies the output file; a path containing a folder can be provided, but it has to be to a folder in the "bin: directory! Example: "output/outputBeach.png", assuming that there is an "output" directory in the "bin" directory. At the moment, only RGB images with the png extension are considered valid input.
 
(4) "-m" which specifies the mask file (which has to exist on disk!); a path containing a folder can be provided, but it has to be to a folder in the bin directory! Example: "images/beachMask.png", assuming that the "images" folder is in "bin". At the moment, only RGB images with the png extension are considered valid input.
 
(5) "-d" which enables the debug mode and accepts a path pattern for debug data. That pattern should point to a directory followed by an image name (e.g. "output/seamBeach.png)

TL;DR, example call: "./imgSmartResize -s 200x200 -i images/beach.png -o output/outputBeach.png -m images/beachMask.png -d output/seamBeach.png"

 
