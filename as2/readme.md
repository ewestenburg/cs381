Eric Ashton Westenburg
CS 381 Assignment 0
Due Date: 2/4/24

**Question #5**
The problem cannot be simplified by remapping camera directions to specific world axes because the provided Raylib functions and camera controls are designed to work with the default camera coordinate system, where W moves along the +Z axis. Trying to remap camera directions to specific world axes would require custom camera controls and transformations which would complicate the implementation.

**How to fetch git submodules:**
Clone into the repository
- git clone --recursive https://github.com/ewestenburg/cs381.git
Move into CS381 repository
- cd cs381
Initialize and Update the Submodules
- git submodule init
- git submodule update --init --recursive

**How to compile code:**
Move into AS2
- cd as2
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
After compile, there will be a resulting executable that can be run titled as2
- ./as2

**How to enumerate controls:**
Use WASD commands to increase the plane's velocity in the x and y axes
Use Q to increase the plane's velocity upward
Use E to increase the plane's velocity downward