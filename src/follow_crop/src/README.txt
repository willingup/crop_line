在笔记本上运行程序时输入的命令：
1、启动相机
roslaunch start_camera usb_cam.launch
2、启动识别苗带线的程序
rosrun follow_crop start_detect_crop02
rosrun follow_crop start_detect_crop03    （供室外做检测角度的实验，添加了检测行末以及将检测到的角度值显示在图象上）
rosrun follow_crop start_detect_crop04   （供调节PID，画面无线时程序不死）
3、启动调节PID的程序
rosrun follow_crop robot_pid_node
4、查看节点信息
rqt
