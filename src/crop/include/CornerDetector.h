#if !defined(AFX_CORNERDETECTOR_H__E026A5DB_5297_40AB_A180_8F10DA9BE1B1__INCLUDED_)
#define AFX_CORNERDETECTOR_H__E026A5DB_5297_40AB_A180_8F10DA9BE1B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//typedef CList<CPoint,CPoint> POINTLIST;

#include <stdlib.h>
#include <vector>
#include <cmath>

using std::vector;

#define SEVEN_SUPP           /* size for non-max corner suppression; SEVEN_SUPP or FIVE_SUPP */
#define MAX_CORNERS 150000  /* max corners per frame */

typedef  struct CORNER{int x, y, info, dx, dy, I;} CORNER_LIST[MAX_CORNERS];
typedef unsigned char BYTE;
#define  FTOI(a) ( (a) < 0 ? ((int)(a-0.5)) : ((int)(a+0.5)) )
#define MAX_CUSTOM_NODES 100

#define MAX_POINT_SET 100
#define MAX_LINE_SET 100
#define MAX_CURVE_SET 10


class CCornerDetector {
public:
	CCornerDetector();
	virtual ~CCornerDetector();

	void SetImage(BYTE* pdata,int width,int height);  //设置数据矩阵
	/*CORNER_LIST**/vector<CORNER>  GetCornerList();     //获得角点列表
	virtual void DetectCorner()=0;  //实施检测

protected:

	/*CORNER_LIST*/vector<CORNER>  m_CornerList;
	BYTE* m_pdata;  //指向图像数据矩阵
	int m_nwidth;   //图像宽度
	int m_nheight;  //图像高度


};

#endif // !defined(AFX_CORNERDETECTOR_H__E026A5DB_5297_40AB_A180_8F10DA9BE1B1__INCLUDED_)