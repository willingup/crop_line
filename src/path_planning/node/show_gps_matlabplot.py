import matplotlib.pyplot as plt
import numpy as np
import os

def get_longitude(filename,i):
    fopen = open(filename,'r')
    longitude = []
    for eachline in fopen:
        group = eachline.split(" ")
        longitude.append(float(group[i]))
    fopen.close()
    return longitude

def get_latitude(filename,i):
    fopen = open(filename,'r')
    latitude = []
    for eachline in fopen:
        group = eachline.split(" ")
        latitude.append(float(group[i]))
    fopen.close()
    return latitude
 
def draw_image(filename,size,color,i):
    latitude = get_latitude(filename, i)  
    longitude = get_longitude(filename, i+1)

    '''
    print(latitude)
    print(longitude)
    '''

    """
    plt.scatter(latitude,longitude,size,color)
    """
    plt.scatter(latitude,longitude,marker='o',c='',edgecolors='g')

    plt.xlim(min(latitude)-0.0000001,max(latitude)+0.0000010)
    plt.ylim(min(longitude)-0.0000001,max(longitude)+0.0000003)
    """
    plt.plot(latitude,longitude,"b")
    """
    plt.show()
    


if __name__ == '__main__':
    draw_image("/home/robot/hei/lat.txt",1,"red",0)
    