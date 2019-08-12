#/bin/bash
sudo chmod 666 /dev/ttyACM0
sudo chmod 666 /dev/ttyUSB0
gnome-terminal -e ./sequence/run_roscore.sh
sleep 5
gnome-terminal -e ./sequence/run_rosserial.sh
sleep 4
gnome-terminal -e ./sequence/bringup.sh
sleep 5
gnome-terminal -e ./sequence/run_rtabmap.sh
