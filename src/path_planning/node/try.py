# coding=utf-8

'''
判断列表中的第一个元素
将所有的元素保存在列表中，经纬度加
'''
def main(parser):
    
    x = 1
    result = open('/home/robot/hei/lng.txt','w')
    result.write(str(x))
    result.close

    
   

if __name__ == '__main__':
    file=open('/home/robot/hei/lng.txt')  
    dataMat=[]  
    for line in file.readlines():    
        curLine=line.strip().split(" ")
        dataMat.append(curLine[0:4]) 
    for index in range(len(dataMat)):
        main(dataMat[index])
