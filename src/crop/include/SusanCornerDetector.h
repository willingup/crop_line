// SusanCornerDetector.h: interface for the CSusanCornerDetector class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SUSANCORNERDETECTOR_H__DB05883B_E119_4EF1_9D51_4E4056CB7D4A__INCLUDED_)
#define AFX_SUSANCORNERDETECTOR_H__DB05883B_E119_4EF1_9D51_4E4056CB7D4A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CornerDetector.h"

class CSusanCornerDetector : public CCornerDetector  
{
public:
	CSusanCornerDetector();
	virtual ~CSusanCornerDetector();
	void SetThreshold(int thresh);
	virtual void DetectCorner();

protected:

	void QuickDetect();
	void CreateLUT();
	BYTE* GetLUT();

	int m_threshold;
	int m_power;
	int max_no;
	BYTE* m_pLUT;


};

#endif // !defined(AFX_SUSANCORNERDETECTOR_H__DB05883B_E119_4EF1_9D51_4E4056CB7D4A__INCLUDED_)