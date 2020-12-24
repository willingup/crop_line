# -*- coding: utf-8 -*-
"""
python 实现 点之间距离计算(基于经纬度)
"""
import os
import csv
os.chdir('D:\lonlat')
os.getcwd()

from math import radians, cos, sin, asin, sqrt
def haversine(lon1, lat1, lon2, lat2): # 经度1，纬度1，经度2，纬度2 （十进制度数）
    """
    Calculate the great circle distance between two points 
    on the earth (specified in decimal degrees)
    """
    # 将十进制度数转化为弧度
    lon1, lat1, lon2, lat2 = map(radians, [lon1, lat1, lon2, lat2])
    # haversine公式
    dlon = lon2 - lon1 
    dlat = lat2 - lat1 
    a = sin(dlat/2)**2 + cos(lat1) * cos(lat2) * sin(dlon/2)**2
    c = 2 * asin(sqrt(a)) 
    r = 6371 # 地球平均半径，单位为公里
    return c * r * 1000
#lat1 = 
#lon1 = 
#lat2 = 
#lon2 = 
file = open(r'aabb.txt','w') 
with open('aabb.csv', 'r') as csvfile: #打开csv
  reader = csv.reader(csvfile)
  for line in reader: #读取csv里的数据
    print(reader.line_num)
    # 忽略第一行
    if reader.line_num == 1: #由于第一行为变量名称，故忽略掉
      continue
      # line是个list，取得所有需要的值
    lat1 = float(line[0].strip())
    lon1 = float(line[1].strip())
    lat2 = float(line[2].strip())
    lon2 = float(line[3].strip())
    d = haversine(lon1,lat1,lon2,lat2)
    #print(d)
    file.write(str(d)) #写入文档
    file.write('\n')
file.close() 
