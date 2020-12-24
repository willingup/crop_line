在笔记本上运行程序时输入的命令：
1、启动相机
roslaunch start_camera usb_cam.launch
2、启动识别苗带线的
rosrun follow_crop start_detect_crop02
3、启动调节PID的程序
rosrun follow_crop robot_pid_node
4、查看节点信息
rqt