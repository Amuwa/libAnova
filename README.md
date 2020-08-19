# libAnova
ANOVA library for C++

ANOVA, ANAlysis Of VAriance, the method of analysing the significance of contribution of factors.

![screenshot](https://github.com/Amuwa/libAnova/blob/master/screenshot.png?raw=true  "Screen shot")


# Usage

## For contributing
1. [Fork this repository](https://github.com/Amuwa/libAnova/fork)
2. Do whatever change you want
3. [Submit a pull request](https://github.com/Amuwa/libAnova/pulls)


## For running the program as-is
If you have Cmake installed on your local computer, this should be straight forward. 
If not, please install it. 

*Windows users are encouraged to use GitBash for Windows for any of the commands mensioned below* 

1. Clone this repository or download as zip file. 
2. Change directory to anova `$ cd anova`
3. Make a directory called `build`and move into it `$ mkdir build && cd build`
4. Run the cmake command to build. If no build type is specified, Cmake will choose the 
build system for the platform (linux, mac or Windows). `$ cmake ..`

**NB** Steps 2 - 4 can be achieved by running [./run.sh](run.sh) file in root repo. 

- If using Windows, a Visual Studio project will be created inside `build` directory. Open `[build/anovacpp.sln](build/anovacpp.sln) 
- For unix systems, you need to run `$ make` to create an executable inside the build directory [build/anovacpp](build/anovacpp)

Video instructions are found in [instructions](./instructions) folder

Please see the example code.


#Info

Users are encouraged to cite the following paper that initiates this project:

Rao et al (2013). Scheduling a single vehicle in the just-in-time part supply for a mixed-model assembly line. Computers & Operations Research, 40(11), 2599-2610




