// CornerDetector.cpp: implementation of the CCornerDetector class.
//
//////////////////////////////////////////////////////////////////////


#include "CornerDetector.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCornerDetector::CCornerDetector()
{
	m_pdata=NULL;
	m_nwidth=0;
	m_nheight=0;
	m_CornerList.reserve(0);
}

CCornerDetector::~CCornerDetector()
{
	
	m_CornerList.clear();
}

void CCornerDetector::SetImage(BYTE* pdata,int width,int height)
{
	if (pdata!=NULL)
	{
		m_pdata=pdata;
		m_nwidth=width;
		m_nheight=height;
	}
}

/*CORNER_LIST**/vector<CORNER> CCornerDetector::GetCornerList()
{
	return m_CornerList;
}