distance_points02.cpp 相对于distance_points01.cpp 的改变是 将经纬度的顺序交换，原来的定义的struct PointInfo的（lng,lat）
经度在前，纬度在后
现在修改为纬度在前，经度在后

distance_points04.cpp
实现根据4个GPS点进行规划，目前的缺点是只能是横向的，之后做一个纵向的，下一步把角度继承进来

