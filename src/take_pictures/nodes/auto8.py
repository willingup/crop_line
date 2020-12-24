#!/usr/bin/env python
# coding:utf-8
import os
import cv2
import time

cam=cv2.VideoCapture(0)

width = 1280
height = 720
cam.set(cv2.CAP_PROP_FRAME_WIDTH, width)
cam.set(cv2.CAP_PROP_FRAME_HEIGHT, height)
count=1

print("开始拍摄～")

while(True):
    ret,img=cam.read()
       
    cv2.imwrite("/home/robot/pictures/auto_pictures8/"  + str(count) + ".png", img)
    count+=1
    if count==1000:      #此处设置采集数量，count-1
        break
    time.sleep(1)
    #cv2.imshow('image', img)
    #cv2.waitKey(10)
print("已拍摄1000张～")   
cam.release()
cv2.destroyAllWindows() 
