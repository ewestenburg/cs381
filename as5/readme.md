Eric Ashton Westenburg
CS 381 Assignment 5

**How to fetch git submodules:**

Clone into the repository
- git clone --recursive https://github.com/ewestenburg/cs381.git

Move into CS381 repository
- cd cs381

Initialize and Update the Submodules
- git submodule init
- git submodule update --init --recursive

**How to compile code:**

Move into AS5
- cd as5

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

After compile, there will be a resulting executable that can be run titled as5
- ./as5

**How to enumerate controls:**
- Move Audio Control dials to adjust sound audio
    - Press Up and Down arrows to adjust sound volume
    - Press TAB to switch between dials
- Press Space to play "Ping"
- Press "Try this" button to play sound effect from the internet
- Press "Change Theme" button to change the GUI theme
