Eric Ashton Westenburg
CS 381 Assignment 3
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
Move into AS3
- cd as3
Delete the build folder and recreate it
- rm -r build
- mkdir build
Copy 381Resources folder into build
- cp -r 381Resources build
Move into build folder
- cd build
Run cmake and make 
- cmake ..
- make

**How to run code:**
After compile, there will be a resulting executable that can be run titled as3
- ./as3

**How to enumerate controls:**
Use TAB to cycle through the planes
Use WS commands to increase the plane's velocity in the direction the plane is facing
Use AD to change plane's heading
Use SPACE to reset the plane's velocity to 0