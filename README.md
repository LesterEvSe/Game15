# Game15
Qt5 cross-platform game for Windows and Linux.
Made for fun. Algorithms for solving the position is present.
For 2x2 and 3x3 game fields it solves for the minimum number of moves.
For 4x4 and 5x5 for the optimal.  
Read **Linux build** for Linux OS and **Windows build** for Windows respectively.

# Linux build
## Requirements
To run the project you need to install the Qt5 and GMP
### Qt install. Install Qt in the /home directory, otherwise the paths to the Qt files will not be found
###### Note: Replace 'name' with the name of your executable file
1. Install Qt https://www.qt.io/download-qt-installer
2. Go to the download where our *.run* file is installed. Before we run it,
we need to give permission to run it, using the command ***chmod +x 'name'***
3. Run our executable file ***./'name'***
4. During the installation you can not install CMake, Ninja, Qt Creator components.
However, it is **necessary** to select *Desktop gcc 64* or *gcc 32* for Qt5,
otherwise the project will not build.

## Easy build and run via .sh files
1. Run the console from the **tools** directory.
2. Install the necessary programs and build the project, using the ***bash build.sh*** command.
3. You can run the game with the ***bash game.sh*** command.

## Build and run 
1. Install compiler for C++ and build system with the commands
* Ubuntu/Debian/Linux Mint  
  ***sudo apt-get update  
  sudo apt-get install g++ cmake***  
* Fedora  
  ***sudo dnf install gcc-c++ cmake***  
* CentOS и RHEL  
  ***sudo yum install gcc-c++ cmake***  
* Arch Linux  
  ***sudo pacman -S gcc cmake***
3. To build a project, you need to make a "build" directory 
in the project folder with the command ***mkdir build***
4. Then move into it with the command ***cd build*** 
5. Next, you need to run ***cmake ..*** command inside "build" directory. 
6. Finally, use the ***make*** command to compile, link the project, and create an executable. 
7. Now you can run the application with the ***./Game15*** command.


# Windows build with Qt Creator
1. Install Qt5 **to any folder on the C drive** https://www.qt.io/download-open-source  
2. In addition to the default packages, choose the
MSVC compiler for your system (64 or 32 bit)

## Run
Now run projects with Qt Creator and build them with the MSVC compiler compiler
