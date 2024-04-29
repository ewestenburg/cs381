Eric Ashton Westenburg
CS 381 Assignment 9

**How to fetch git submodules:**
Clone into the repository
- git clone --recursive https://github.com/ewestenburg/cs381.git
Move into CS381 repository
- cd cs381
Initialize and Update the Submodules
- git submodule init
- git submodule update --init --recursive

**How to compile code:**
Move into AS9
- cd as9
Delete the build folder and recreate it
- rm -r build
- mkdir build
Copy 381Resources folder into build
- cp -r 381Resources build
Copy generated folder into build
- cp -r generated build
Copy models folder into build
- cp -r generated models
Move into build folder
- cd build
Run cmake and make 
- cmake ..
- make

**How to run code:**
After compile, there will be a resulting executable that can be run titled as6
- ./as9

**How to enumerate controls:**
Hold W to increase velocity forward
![cs381-as9-1](https://github.com/ewestenburg/cs381/assets/70497906/2a69133d-9b12-4065-9159-41f168baaa14)
Hold S to jump

Press SPACE to reset game when game over
![cs381-as9-2](https://github.com/ewestenburg/cs381/assets/70497906/d2cdf995-43b2-4cde-96ce-f4a12065fab3)
