from folium import plugins
import folium

import os
m = folium.Map([23.1604578,113.3446330], zoom_start=20,control_scale = True,) 

location =[[23.16057,113.344633],[23.16054,113.34525],[23.159569,113.345175],[23.159608,113.344531],[23.16057,113.344633]]
location02 = [[23.1605518,113.3446311],[23.1605518,113.3450073],[23.1605336,113.3452495],[23.1605336,113.3446291],[23.1605154,113.3446272],[23.1605154,113.3452481],[23.1604972,113.3452467],[23.1604972,113.3446253],
[23.1604790,113.3446234],[23.1604790,113.3452453],[23.1604608,113.3452439],[23.1604608,113.3446214],[23.1604426,113.3446195],[23.1604426,113.3452425],[23.1604244,113.3452411],[23.1604244,113.3446176],[23.1604062,113.3446156],[23.1604062,113.3452397],[23.1603880,113.3452383],[23.1603880,113.3446137],[23.1603698,113.3446118],[23.1603698,113.3452369],[23.1603516,113.3452354],[23.1603516,113.3446098],[23.1603334,113.3446079],
[23.1603334,113.3452340],[23.1603152,113.3452326],[23.1603152,113.3446060],[23.1602970,113.3446041],[23.1602970,113.3452312],[23.1602788,113.3452298],[23.1602788,113.3446021],[23.1602606,113.3446002],[23.1602606
,113.3452284],[23.1602424,113.3452270],[23.1602424,113.3445983],[23.1602242,113.3445963],[23.1602242,113.3452256],[23.1602060,113.3452242],[23.1602060,113.3445944],[23.1601878,113.3445925],
[23.1601878,113.3452228],[23.1601696,113.3452214],[23.1601696,113.3445905],[23.1601514,113.3445886],[23.1601514,113.3452200],[23.1601332,113.3452186],[23.1601332,113.3445867],[23.1601150,113.3445848],[23.1601150,113.3452172],
[23.1600968,113.3452158],[23.1600968,113.3445828],[23.1600786,113.3445809],[23.1600786,113.3452144],[23.1600604,113.3452130],[23.1600604,113.3445790],[23.1600422,113.3445770],[23.1600422,113.3452115],
[23.1600240,113.3452101],[23.1600240,113.3445751],[23.1600058,113.3445732],[23.1600058,113.3452087],[23.1599876,113.3452073],[23.1599876,113.3445712],[23.1599694,113.3445693],[23.1599694,113.3452059],
[23.1599512,113.3452045],[23.1599512,113.3445674],[23.1599330,113.3445655],[23.1599330,113.3452031],[23.1599148,113.3452017],[23.1599148,113.3445635],[23.1598966,113.3445616],[23.1598966,113.3452003],
[23.1598784,113.3451989],[23.1598784,113.3445597],[23.1598602,113.3445577],[23.1598602,113.3451975],[23.1598420,113.3451961],[23.1598420,113.3445558],[23.1598238,113.3445539],[23.1598238,113.3451947],[23.1598056,113.3451933],
[23.1598056,113.3445520],[23.1597874,113.3445500],[23.1597874,113.3451919],[23.1597692,113.3451905],[23.1597692,113.3445481],[23.1597510,113.3445462],[23.1597510,113.3451891],[23.1597328,113.3451877],
[23.1597328,113.3445442],[23.1597146,113.3445423],[23.1597146,113.3451862],[23.1596964,113.3451848],[23.1596964,113.3445404],[23.1596782,113.3445384],[23.1596782,113.3451834],[23.1596600,113.3451820],[23.1596600,113.3445365],
[23.1596418,113.3445346],[23.1596418,113.3451806],[23.1596236,113.3451792],[23.1596236,113.3445327],[23.1596054,113.3445739],[23.1596054,113.3451778],[23.1595872,113.3451764],[23.1595872,113.3448745]]

folium.Marker([23.16057,113.344633],popup='<b>浮标上面的那个文字</b>').add_to(m)  # 定一个点，放到地图m上
folium.Marker([23.16054,113.34525],popup='<b>浮标上面的那个文字</b>',icon=folium.Icon(color='red')).add_to(m) 
folium.Marker([23.159569,113.345175],popup='<b>浮标上面的那个文字</b>').add_to(m)  # 定一个点，放到地图m上
folium.Marker([23.159608,113.344531],popup='<b>浮标上面的那个文字</b>',icon=folium.Icon(color='red')).add_to(m)           

route02 = folium.PolyLine(    
    location,   
    weight=2,  
    color='red',  
    opacity=0.8,
    title='http://webrd02.is.autonavi.com/appmaptile?lang=zh_cn&size=1&scale=1&style=7&x={x}&y={y}&z={z}' ,
    attr = 'default' 
).add_to(m)

route02 = folium.PolyLine(    
    location02,   
    weight=2,  
    color='yellow',  
    opacity=0.8,
    title='http://webrd02.is.autonavi.com/appmaptile?lang=zh_cn&size=1&scale=1&style=7&x={x}&y={y}&z={z}' ,
    attr = 'default' 
).add_to(m)

m.save(os.path.join(r'/home/robot/hei', 'Heatmap07.html'))
