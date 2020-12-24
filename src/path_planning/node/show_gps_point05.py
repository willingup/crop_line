from folium import plugins
import folium

import os
m = folium.Map([23.1604578,113.3446330], zoom_start=20,control_scale = True,) 

location =[[23.16057,113.344633],[23.16054,113.34525],[23.159569,113.345175],[23.159608,113.344531],[23.16057,113.344633]]
location02 = [[23.1595993,113.3446740],[23.1605680,113.3446740],[23.1605611,113.3448170],[23.1595907,113.3448170],[23.1595820,113.3449600],[23.1605541,113.3449600],[23.1605471,113.3451030],[23.1595734,113.3451030],[23.1604882,113.3452460],[23.1605402,113.3452460]]

folium.Marker([23.16057,113.344633],popup='<b>浮标上面的那个文字</b>').add_to(m)  # 定一个点，放到地图m上
folium.Marker([23.16054,113.34525],popup='<b>浮标上面的那个文字</b>',icon=folium.Icon(color='red')).add_to(m) 
folium.Marker([23.159569,113.345175],popup='<b>浮标上面的那个文字</b>').add_to(m)  # 定一个点，放到地图m上
folium.Marker([23.159608,113.344531],popup='<b>浮标上面的那个文字</b>',icon=folium.Icon(color='red')).add_to(m)           

route02 = folium.PolyLine(    
    location,   
    weight=0.5,  
    color='red',  
    opacity=0.8,
    title='http://webrd02.is.autonavi.com/appmaptile?lang=zh_cn&size=1&scale=1&style=7&x={x}&y={y}&z={z}' ,
    attr = 'default' 
).add_to(m)

route02 = folium.PolyLine(    
    location02,   
    weight=0.5,  
    color='yellow',  
    opacity=0.8,
    title='http://webrd02.is.autonavi.com/appmaptile?lang=zh_cn&size=1&scale=1&style=7&x={x}&y={y}&z={z}' ,
    attr = 'default' 
).add_to(m)

m.save(os.path.join(r'/home/robot/hei', 'Heatmap08.html'))
