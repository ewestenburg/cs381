Eric Ashton Westenburg
CS 381 Assignment 8

**How to fetch git submodules:**
Clone into the repository
- git clone --recursive https://github.com/ewestenburg/cs381.git
Move into CS381 repository
- cd cs381
Initialize and Update the Submodules
- git submodule init
- git submodule update --init --recursive

**How to compile code:**
Move into AS8
- cd as6
Delete the build folder and recreate it
- rm -r build
- mkdir build
Copy 381Resources folder into build
- cp -r 381Resources build
Copy generated folder into build
- cp -r generated build
Move into build folder
- cd build
Run cmake and make 
- cmake ..
- make

**How to run code:**
After compile, there will be a resulting executable that can be run titled as6
- ./as8

**How to enumerate controls:**
Use TAB to cycle through the entities
Use WS commands to increase the velocity in the direction the entity is facing
Use AD to change entity's heading
Use QE to change the entity's pitch
Use RF to change the entity's roll
Use SPACE to stop the entity's velocity