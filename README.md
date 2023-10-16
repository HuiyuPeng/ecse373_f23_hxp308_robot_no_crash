# ecse373_f23_hxp308_robot_no_crash
## Introduction
### The simulator allows the user to build a very simple robot with common, but rudimentary simulations of 2D sensors. This laboratory reveals the performance of a robot to be created in this two-dimensional simulation environment with obstacle detection.
## Installation 
## The STDR Simulator
### Clone the STDR Simulator package locally.
### If using ROS Noetic, use this command.
`git clone -b noetic-devel https://github.com/cwru-eecs-275/stdr_simulator.git`
### Install STDR Simulator Dependencies
### The STDR Simulator has several dependencies that must be installed before the package can be built. 
### **rosdep**
### It installs dependencies declared in the package CMakeLists.txt and package.xml files. 
`sudo apt install python3-rosdep`
### Initialize rosdep
`sudo rosdep init`
### Update rosdep (notice that it does not include the use of sudo)
`rosdep update`
### If rosdep is every run incorrectly as "sudo rosdep update", it will not work correctly.
### If running "rosdep update" yields permissions errors, invoke the following command:
`sudo rosdep fix-permissions`
### Get to the catkin workspace location
`cd ~/catkin_ws`
### Install missing dependencies
`rosdep install --from-paths src --ignore-src -r -y`
### This command is fairly complex, but this is the command that will traverse a workspace
### directory structure to find dependencies to install.
### All dependencies should now be installed to allow the STDR Simulator to be built.
### **Build the STDR simulator**
### (Re)run the setup.bash script to recognize newly installed packages
`source /opt/ros/<kinetic|melodic|noetic>/setup.bash`
### Make the STDR Simulator once in the correct directory.
`catkin_make`
### Setup ROS to be aware of the current workspace
`source devel/setup.bash`
### Start the simulator with a map and without a robot
`roslaunch stdr_launchers server_with_map_and_gui.launch`
###**Installing STDR Simulator**
`sudo -- /bin/bash -c "source /opt/ros/<noetic>/setup.bash; catkin_make -DCMAKE_INSTALL_PREFIX=/opt/ros/<noetic> install"`
###**Install the STDR Simulator**
### Refresh the ROS configuration after installation or use a new terminal 
`source /opt/ros/<ros_version>/setup.bash`
### It is not neccessary to call 'source devel/setup.bash' to use the STDR as it is now installed. Start the simulator with a map and without a robot
`roslaunch stdr_lauchers server_with_map_and_gui.launch`
###**Teleoperate Robot**
### Find the message type of the /cmd_vel topic
`rostopic info /cmd_vel`
### Find all messages of the same type.
`rostopic find <message type>`
### Refresh the ROS configuration after installation or use a new terminal.
`rostopic echo /robot0/cmd_vel`
### rqt_gui can be used to control the robot
`rosrun rqt_gui rqt_gui`
## Create Node
### Run the robot 
`roslaunch robot_no_crash lab4.launch`

