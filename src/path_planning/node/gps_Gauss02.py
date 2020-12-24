# coding=utf-8
import scipy.integrate as integrate
from argparse import ArgumentParser
from math import cos, sin, trunc, tan, pi, sqrt

def main(parser):
   
    latitude = parser[0] 
    longitude = parser[1]
    transformationType = parser[2]
    ellipsoid = parser[3]
    if transformationType == 'GeodeticToPlane':
        print("Geodetic to plane transformation:")
        x, y = geodetic_to_plane(latitude,longitude,ellipsoid)

        result = open('/home/robot/hei/lng.txt','a')
        result.write(str(x)+" "+str(y)+'\n')
        result.close

        print("x : "+str(x))
        print("y : "+str(y))
    else:
        print("Plane to geodetic transformation:")
        lat,lon = plane_to_geodetic(float(longitude),float(latitude),ellipsoid)
        print("lat(dms) : "+str(lat))
        print("lon(dms) : "+str(lon))


def ellipsoid_pars(ell = 'wgs84'):
    # add any ellipsoid "a" and "f" here
    if ell== 'wgs84':
        # major axis
        a = 6378137.0
        f = 1/298.257223563

    elif ell=='CGCS2000':
        a = 6378137
        f = 1 / 298.257222101
        
        
    elif ell=='beijing54': 
        a = 6378245
        #b = 6356863.01877305
        f = 1/293.3

    else:
        raise Exception('No such ellipsoid')
    # minor axis
    b = a * (1 - f)
    # first and second eccentricity 第一和第二偏心
    e2 = 2 * f - pow(f, 2)
    
    e21 = (pow(a, 2) - pow(b, 2)) / pow(b, 2)
    return a, f, b, e2, e21


def geodetic_to_plane(latitude,longitude,ell):
    false_easting = 500000

    # convert to radiance
    latRad = deg_to_rad(latitude)

    # lonRad = deg_to_rad(longitude)
    # compute meridian difference and get G-K zone number 计算子午线差并获得G-K区号
    l, n = central_meridian_diff(longitude)
    a, f, b, e2, e21 = ellipsoid_pars(ell)

    N = a / sqrt(1 - f * (2 - f) * pow(sin(latRad),2))
    t = tan(latRad)
    niu2 = e21*pow(cos(latRad),2)
    Y = lambda x :a*(1-e2)/pow(1-e2*pow(sin(x),2),3/2)
    X = integrate.quad(Y,0,latRad)[0]
    # plane coordinates

    x = X + N/2 * sin(latRad)*cos(latRad)*pow(l,2)+N/24*sin(latRad)*pow(cos(latRad),3)*(5-pow(t,2)+9*niu2+4*pow(niu2,2))*pow(l,4)+N/720*sin(latRad)*pow(cos(latRad),5)*(61-58*pow(t,2)+pow(t,4))*pow(l,6)

    y = N * cos(latRad) * l + N / 6 * pow(cos(latRad) , 3) * (1 - pow(t , 2) + niu2) * pow(l , 3) + N / 120 * pow(cos(latRad) , 5 )*(5 - 18 * pow(t , 2) + pow(t , 4) + 14 * niu2 - 58 * pow(t , 2) * niu2) * pow(l , 5)
    print y
    y += false_easting
    y = float(str(int(n)) + str(y)) #输出的时候加了500km，还加了带号,带号是2位
    return x,y


def plane_to_geodetic(y,x,ell='wgs84'):
    false_easting = 500000

    a, f, b, e2, e21 = ellipsoid_pars(ell)

    m0 = a * (1 - e2)
    m2 = 3/2 * e2 * m0
    m4 = 5/4 * e2 * m2
    m6 = 7/6 * e2 * m4
    m8 = 9/8 * e2 * m6

    a0 = m0 + m2/2 + 3 * m4 /8 + 5 * m6 / 16 + 35 * m8 / 128
    a2 = m2 /2 + m4 /2 + 15 *m6/32 + 7 * m8 / 16
    a4 = m4 / 8 + 3 * m6 / 16 + 7 * m8 / 32
    a6 = m6 / 32 + m8 / 16
    a8 = m8/128

    B = []
    B.append(x/a0)
    i=0
    last = False
    while True:
        i+=1
        Bnext = (x +a2/2 * sin(2 * B[i-1]) - a4/4*sin(4*B[i-1]) + a6/6 * sin(6 * B[i-1]) - a8 / 8 * sin (8*B[i-1]))/a0
        B.append(Bnext)
        if last==True:
            Bf = B[i]
            break
        if abs(B[i] - B[i-1]) < pi/(180*60*60 * 10000):
            last = True

    n = trunc(y/ 1000000)
    y -=  (n* 1000000 + false_easting)
    L0 = n*6 - 3

    W = 1-e2*pow(sin(Bf),2)
    M = a*(1-e2)/W**(3/2)
    N = a/W**(1/2)

    t = tan(Bf)
    niu2 = e21 * pow(cos(Bf), 2)

    B = Bf - t/(2*M*N)*pow(y,2) + t/(24*M*pow(N,3))*(5 + 3*pow(t,2) + niu2 - 9*niu2*pow(t,2))*pow(y,4) - t/(720*M*pow(N,5))*(61 + 90*pow(t,2) + 45 * pow(t,4))*pow(y,6)
    l = 1/ (N * cos(Bf))*y - 1/(6 * N**3 * cos(Bf))*(1 + 2 * t**2 + niu2) * y**3 + 1/(120*N**5 * cos(Bf))*(5 + 28 * t**2 + 6 * niu2 +24 * t**4 + 8 * t**2 * niu2) * y ** 5
    #在这里把计算的答案变成了度分秒相连的表达
    lat = rad2dms(B)
    lon = rad2dms(l) + L0
    return lat, lon

'''
度变成弧度
'''
def deg_to_rad(x):
    '''
    deg,min,sec = x.split(' ')
    latDeg = float(deg) + float(min)/60 + float(sec)/3600
    print latDeg
    return (float(deg) + float(min)/60 + float(sec)/3600)/180*pi
    '''

    return float(x)*pi/180

#中央子午线
def central_meridian_diff(lon):
    '''
    deg,min,sec = lon.split(' ')
    lonDeg = float(deg) + float(min) / 60 + float(sec) / 3600
    print lonDeg
    '''
    lonDeg = float(lon)
    n = trunc(lonDeg/6)+1   #计算出带号
    lon0 = n*6 - 3           #计算中央经线
    l = (lonDeg-lon0)/180*pi   
    return l,  n


def rad2dms(radAngle):
    sign = 1
    if (radAngle < 0):
        sign = -1
        radAngle = abs(radAngle)

    secAngle = radAngle *180 /pi*3600
    degAngle = int(secAngle/3600 + 0.0001)
    minAngle = int((secAngle-degAngle*3600.0)/60.0+0.0001)
    secAngle = secAngle - degAngle*3600 - minAngle*60
    if secAngle < 0:
        secAngle = 0
    dmsAngle = degAngle+minAngle/100 + secAngle/10000
    dmsAngle = dmsAngle *sign
    return dmsAngle


if __name__ == '__main__':
    file=open('/home/robot/hei/lat.txt')    
    dataMat=[]  
    for line in file.readlines():    
        curLine=line.strip().split(" ")
        dataMat.append(curLine[0:4]) 
        
    for index in range(len(dataMat)):
        main(dataMat[index])
