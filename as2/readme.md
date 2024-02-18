Eric Ashton Westenburg
CS 381 Assignment 0
Due Date: 2/4/24

**How to fetch git submodules:**
Clone into the repository
- git clone --recursive https://github.com/ewestenburg/cs381.git
Move into CS381 repository
- cd cs381
Initialize and Update the Submodules
- git submodule init
- git submodule update --init --recursive

**How to compile code:**
Move into AS1
- cd as1
Delete the build folder and recreate it
- rm -r build
- mkdir build
Move into build folder
- cd build
Run cmake and make 
- cmake ..
- make

**How to run code:**
After compile, there will be a resulting executable that can be run titled as1
- ./as1

**How to enumerate controls:**
N/A