from folium import plugins
import folium

import os
m = folium.Map([23.1604578,113.3446330], zoom_start=5) 

location =[[23.1604578,113.3446330],[23.1604578,113.3452500],[23.1604524,113.3446330],[23.1604524,113.3452500],[23.1604471,113.3446330],[23.1604471,113.3452500],[23.1604417,113.3446330],[23.1604417,113.3452500],
[23.1604364,113.3446330],[23.1604364,113.3452500],[23.1604310,113.3446330],[23.1604310,113.3452500],[23.1604257,113.3446330],[23.1604257,113.3452500],[23.1604204,113.3446330],[23.1604204,113.3452500],
[23.1604150,113.3446330],[23.1604150,113.3452500],[23.1604097,113.3446330],[23.1604097,113.3452500],[23.1604043,113.3446330],[23.1604043,113.3452500],[23.1603990,113.3446330],[23.1603990,113.3452500],[23.1603936,113.3446330],[23.1603936,113.3452500],[23.1603883,113.3446330],[23.1603883,113.3452500],[23.1603829,113.3446330],[23.1603829,113.3452500],[23.1603776,113.3446330],[23.1603776,113.3452500],[23.1603723,113.3446330],
[23.1603723,113.3452500],[23.1603669,113.3446330],[23.1603669,113.3452500],[23.1603616,113.3446330],[23.1603616,113.3452500],[23.1603562,113.3446330],[23.1603562,113.3452500],[23.1603509,113.3446330],
[23.1603509,113.3452500],[23.1603455,113.3446330],[23.1603455,113.3452500],[23.1603402,113.3446330],[23.1603402,113.3452500],[23.1603348,113.3446330],[23.1603348,113.3452500],[23.1603295,113.3446330],[23.1603295,113.3452500],[23.1603242,113.3446330],[23.1603242,113.3452500],[23.1603188,113.3446330],[23.1603188,113.3452500],[23.1603135,113.3446330],[23.1603135,113.3452500],[23.1603081,113.3446330],[23.1603081,113.3452500],
[23.1603028,113.3446330],[23.1603028,113.3452500],[23.1602974,113.3446330],[23.1602974,113.3452500],[23.1602921,113.3446330],[23.1602921,113.3452500],[23.1602867,113.3446330],[23.1602867,113.3452500],
[23.1602814,113.3446330],[23.1602814,113.3452500],[23.1602761,113.3446330],[23.1602761,113.3452500],[23.1602707,113.3446330],[23.1602707,113.3452500],[23.1602654,113.3446330],[23.1602654,113.3452500],[23.1602600,113.3446330],
[23.1602600,113.3452500],[23.1602547,113.3446330],[23.1602547,113.3452500],[23.1602493,113.3446330],[23.1602493,113.3452500],[23.1602440,113.3446330],[23.1602440,113.3452500],[23.1602386,113.3446330],
[23.1602386,113.3452500],[23.1602333,113.3446330],[23.1602333,113.3452500],[23.1602280,113.3446330],[23.1602280,113.3452500],[23.1602226,113.3446330],[23.1602226,113.3452500],[23.1602173,113.3446330],
[23.1602173,113.3452500],[23.1602119,113.3446330],[23.1602119,113.3452500],[23.1602066,113.3446330],[23.1602066,113.3452500],[23.1602012,113.3446330],[23.1602012,113.3452500],[23.1601959,113.3446330],[23.1601959,113.3452500],
[23.1601905,113.3446330],[23.1601905,113.3452500],[23.1601852,113.3446330],[23.1601852,113.3452500],[23.1601799,113.3446330],[23.1601799,113.3452500],[23.1601745,113.3446330],[23.1601745,113.3452500],[23.1601692,
113.3446330],[23.1601692,113.3452500],[23.1601638,113.3446330],[23.1601638,113.3452500],[23.1601585,113.3446330],[23.1601585,113.3452500],[23.1601531,113.3446330],[23.1601531,113.3452500],[23.1601478,113.3446330],
[23.1601478,113.3452500],[23.1601424,113.3446330],[23.1601424,113.3452500],[23.1601371,113.3446330],[23.1601371,113.3452500],[23.1601318,113.3446330],[23.1601318,113.3452500],[23.1601264,113.3446330],
[23.1601264,113.3452500],[23.1601211,113.3446330],[23.1601211,113.3452500],[23.1601157,113.3446330],[23.1601157,113.3452500],[23.1601104,113.3446330],[23.1601104,113.3452500],[23.1601050,113.3446330],
[23.1601050,113.3452500],[23.1600997,113.3446330],[23.1600997,113.3452500],[23.1600943,113.3446330],[23.1600943,113.3452500],[23.1600890,113.3446330],[23.1600890,113.3452500],[23.1600837,113.3446330],[23.1600837,113.3452500
],[23.1600783,113.3446330],[23.1600783,113.3452500],[23.1600730,113.3446330],[23.1600730,113.3452500],[23.1600676,113.3446330],[23.1600676,113.3452500],[23.1600623,113.3446330],[23.1600623,113.3452500],
[23.1600569,113.3446330],[23.1600569,113.3452500],[23.1600516,113.3446330],[23.1600516,113.3452500],[23.1600462,113.3446330],[23.1600462,113.3452500],[23.1600409,113.3446330],[23.1600409,113.3452500],
[23.1600356,113.3446330],[23.1600356,113.3452500],[23.1600302,113.3446330],[23.1600302,113.3452500],[23.1600249,113.3446330],[23.1600249,113.3452500],[23.1600195,113.3446330],[23.1600195,113.3452500],[23.1600142,113.3446330],
[23.1600142,113.3452500],[23.1600088,113.3446330],[23.1600088,113.3452500],[23.1600035,113.3446330],[23.1600035,113.3452500],[23.1599981,113.3446330],[23.1599981,113.3452500],[23.1599928,113.3446330],
[23.1599928,113.3452500],[23.1599875,113.3446330],[23.1599875,113.3452500],[23.1599821,113.3446330],[23.1599821,113.3452500],[23.1599768,113.3446330],[23.1599768,113.3452500],[23.1599714,113.3446330],
[23.1599714,113.3452500],[23.1599661,113.3446330],[23.1599661,113.3452500],[23.1599607,113.3446330],[23.1599607,113.3452500],[23.1599554,113.3446330],[23.1599554,113.3452500],[23.1599500,113.3446330],[23.1599500,113.3452500],
[23.1599447,113.3446330],[23.1599447,113.3452500],[23.1599394,113.3446330],[23.1599394,113.3452500],[23.1599340,113.3446330],[23.1599340,113.3452500],[23.1599287,113.3446330],[23.1599287,113.3452500],
[23.1599233,113.3446330],[23.1599233,113.3452500],[23.1599180,113.3446330],[23.1599180,113.3452500],[23.1599126,113.3446330],[23.1599126,113.3452500],[23.1599073,113.3446330],[23.1599073,113.3452500],
[23.1599019,113.3446330],[23.1599019,113.3452500],[23.1598966,113.3446330],[23.1598966,113.3452500],[23.1598913,113.3446330],[23.1598913,113.3452500],[23.1598859,113.3446330],[23.1598859,113.3452500],[23.1598806,113.3446330],
[23.1598806,113.3452500],[23.1598752,113.3446330],[23.1598752,113.3452500],[23.1598699,113.3446330],[23.1598699,113.3452500],[23.1598645,113.3446330],[23.1598645,113.3452500],[23.1598592,113.3446330],
[23.1598592,113.3452500],[23.1598538,113.3446330],[23.1598538,113.3452500],[23.1598485,113.3446330],[23.1598485,113.3452500],[23.1598432,113.3446330],[23.1598432,113.3452500],[23.1598378,113.3446330],[23.1598378,113.3452500],[23.1598325,113.3446330],[23.1598325,113.3452500],[23.1598271,113.3446330],[23.1598271,113.3452500],[23.1598218,113.3446330],[23.1598218,113.3452500],[23.1598164,113.3446330],[23.1598164,113.3452500],[23.1598111,113.3446330],[23.1598111,113.3452500],[23.1598057,113.3446330],[23.1598057,113.3452500],[23.1598004,113.3446330],[23.1598004,113.3452500],[23.1597951,113.3446330],[23.1597951,113.3452500],[23.1597897,113.3446330],[23.1597897,113.3452500],[23.1597844,113.3446330],[23.1597844,113.3452500],[23.1597790,113.3446330],[23.1597790,113.3452500],[23.1597737,113.3446330],[23.1597737,113.3452500],[23.1597683,113.3446330],[23.1597683,113.3452500],[23.1597630,113.3446330],[23.1597630,113.3452500],[23.1597576,113.3446330],[23.1597576,113.3452500],[23.1597523,113.3446330],[23.1597523,113.3452500],[23.1597470,113.3446330],[23.1597470,113.3452500],[23.1597416,113.3446330],[23.1597416,113.3452500],[23.1597363,113.3446330],[23.1597363,113.3452500],[23.1597309,113.3446330],[23.1597309,113.3452500],[23.1597256,113.3446330],[23.1597256,113.3452500],[23.1597202,113.3446330],[23.1597202,113.3452500],[23.1597149,113.3446330],[23.1597149,113.3452500],[23.1597095,113.3446330],[23.1597095,113.3452500],[23.1597042,113.3446330],[23.1597042,113.3452500],[23.1596989,113.3446330],[23.1596989,113.3452500],[23.1596935,113.3446330],[23.1596935,113.3452500],[23.1596882,113.3446330],[23.1596882,113.3452500],[23.1596828,113.3446330],[23.1596828,113.3452500],[23.1596775,113.3446330],[23.1596775,113.3452500],[23.1596721,113.3446330],[23.1596721,113.3452500],[23.1596668,113.3446330],[23.1596668,113.3452500],[23.1596614,113.3446330],[23.1596614,113.3452500],[23.1596561,113.3446330],[23.1596561,113.3452500],[23.1596508,113.3446330],[23.1596508,113.3452500],[23.1596454,113.3446330],[23.1596454,113.3452500],[23.1596401,113.3446330],[23.1596401,113.3452500],[23.1596347,113.3446330],[23.1596347,113.3452500],[23.1596294,113.3446330],[23.1596294,113.3452500],[23.1596240,113.3446330],[23.1596240,113.3452500],[23.1596187,113.3446330],[23.1596187,113.3452500],[23.1596133,113.3446330],[23.1596133,113.3452500]]  

          
           
route = folium.PolyLine(    
    location,   
    weight=3,  
    color='orange',  
    opacity=0.8    
).add_to(m)  
m.save(os.path.join(r'/home/robot/hei', 'Heatmap2.html'))
