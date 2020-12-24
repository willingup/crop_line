#!/usr/bin/env python
# -*- coding: utf-8 -*-
import cv2
import numpy as np
import matplotlib.pyplot as plt
   
    """
    Created on Fri Sep 20 14:13:34 2019
    @author: ywx
    """
    image=cv2.imread('test2.png',cv2.IMREAD_COLOR)
    img1 = np.array(image,dtype='int')  #转换成int型，不然会导致数据溢出
    #超绿灰度图
    b, g, r = cv2.split(img1)
    #ExG_sub = cv2.subtract(2*g,r)
    #ExG = cv2.subtract(ExG_sub,b )
    ExG = 2*g-r-b
    [m,n] = ExG.shape
    
    for i in range(m):
        for j in range(n):
            if ExG[i,j]<0:
                ExG[i,j]=0
            elif ExG[i,j]>255:
                ExG[i,j]=255
                  
    ExG = np.array(ExG,dtype='uint8')  #重新转换成uint8类型
    ret2, th2 = cv2.threshold(ExG, 0, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)
 
    plt.figure(figsize=(10,5), dpi=80)
    plt.subplot(131),plt.imshow(cv2.cvtColor(image,cv2.COLOR_BGR2RGB)),\
                     plt.title('Original'),plt.axis('off')
    plt.subplot(132),plt.imshow(cv2.cvtColor(ExG,cv2.COLOR_BGR2RGB)),\
                     plt.title('ExG_gray'),plt.axis('off')
    plt.subplot(133),plt.imshow(cv2.cvtColor(th2,cv2.COLOR_BGR2RGB)),\
                     plt.title('OTSU_bw'),plt.axis('off')
    plt.show()