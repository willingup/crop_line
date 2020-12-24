// SusanCornerDetector.cpp: implementation of the CSusanCornerDetector class.
//
//////////////////////////////////////////////////////////////////////


#include "SusanCornerDetector.h"
#include <stdio.h>
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
 #include<string.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSusanCornerDetector::CSusanCornerDetector()
{
	m_threshold=30;
	m_power=6;
	max_no=1580;  //最多1580个角点
	m_pLUT=NULL;
}

CSusanCornerDetector::~CSusanCornerDetector()
{
	if (m_pLUT!=NULL)
	{
		delete m_pLUT;
		m_pLUT=NULL;
	}
}

void CSusanCornerDetector::SetThreshold(int thresh)
{
	if (thresh>0)
	{
		m_threshold=thresh;
	}
}

void CSusanCornerDetector::CreateLUT()
{
	int   k;
	double temp;	
	
	if (m_pLUT!=NULL)
	{
		delete [] m_pLUT;
		m_pLUT=NULL;			
	}
	m_pLUT=new unsigned char[516];

	unsigned char*bp=m_pLUT;
	bp=bp+258;
	for(k=-256;k<257;k++)
	{
		temp=((float)k)/((float)m_threshold);
		temp=temp*temp;
		if (m_power==6)
			temp=temp*temp*temp;
		temp=100.0*exp(-temp);
		*(bp+k)= (unsigned char)temp;
	 }	
}

BYTE*CSusanCornerDetector::GetLUT()
{
	return  m_pLUT+258;
}


void CSusanCornerDetector::DetectCorner()
{
	//检查是否存在图像
	if (m_pdata==NULL)
	{
		//AfxMessageBox(TEXT("Susan算子中没有图像数据"));
		return;
	}

	// 创建查找表
	CreateLUT(); 

	int   n,x,y,sq,xx,yy,
		  i,j,*cgx,*cgy;
	float divide;
	unsigned char c,*p,*cp;

	unsigned char*in=m_pdata;
	unsigned char*bp=GetLUT();
	int x_size=m_nwidth;
	int y_size=m_nheight;
	
	BYTE* m_pTempBuffer=new BYTE[x_size* y_size];
	memset (m_pTempBuffer,0,x_size * y_size * sizeof(BYTE));

	cgx=(int *)malloc(x_size*y_size*sizeof(int));
	cgy=(int *)malloc(x_size*y_size*sizeof(int));


  for (i=5;i<y_size-5;i++)
    for (j=5;j<x_size-5;j++)
	{
        n=100;
        p=in + (i-3)*x_size + j - 1;
        cp=bp + in[i*x_size+j];  

        n+=*(cp-*p++);
        n+=*(cp-*p++);
        n+=*(cp-*p);
        p+=x_size-3; 

        n+=*(cp-*p++);
        n+=*(cp-*p++);
        n+=*(cp-*p++);
        n+=*(cp-*p++);
        n+=*(cp-*p);
        p+=x_size-5;

        n+=*(cp-*p++);
        n+=*(cp-*p++);
        n+=*(cp-*p++);
        n+=*(cp-*p++);
        n+=*(cp-*p++);
        n+=*(cp-*p++);
        n+=*(cp-*p);
        p+=x_size-6;

        n+=*(cp-*p++);
        n+=*(cp-*p++);
        n+=*(cp-*p);
      if (n<max_no){    /* do this test early and often ONLY to save wasted computation */
        p+=2;
        n+=*(cp-*p++);
      if (n<max_no){
        n+=*(cp-*p++);
      if (n<max_no){
        n+=*(cp-*p);
      if (n<max_no){
        p+=x_size-6;

        n+=*(cp-*p++);
      if (n<max_no){
        n+=*(cp-*p++);
      if (n<max_no){
        n+=*(cp-*p++);
      if (n<max_no){
        n+=*(cp-*p++);
      if (n<max_no){
        n+=*(cp-*p++);
      if (n<max_no){
        n+=*(cp-*p++);
      if (n<max_no){
        n+=*(cp-*p);
      if (n<max_no){
        p+=x_size-5;

        n+=*(cp-*p++);
      if (n<max_no){
        n+=*(cp-*p++);
      if (n<max_no){
        n+=*(cp-*p++);
      if (n<max_no){
        n+=*(cp-*p++);
      if (n<max_no){
        n+=*(cp-*p);
      if (n<max_no){
        p+=x_size-3;

        n+=*(cp-*p++);
      if (n<max_no){
        n+=*(cp-*p++);
      if (n<max_no){
        n+=*(cp-*p);

        if (n<max_no)
        {
            x=0;y=0;
            p=in + (i-3)*x_size + j - 1;

            c=*(cp-*p++);x-=c;y-=3*c;
            c=*(cp-*p++);y-=3*c;
            c=*(cp-*p);x+=c;y-=3*c;
            p+=x_size-3; 
    
            c=*(cp-*p++);x-=2*c;y-=2*c;
            c=*(cp-*p++);x-=c;y-=2*c;
            c=*(cp-*p++);y-=2*c;
            c=*(cp-*p++);x+=c;y-=2*c;
            c=*(cp-*p);x+=2*c;y-=2*c;
            p+=x_size-5;
    
            c=*(cp-*p++);x-=3*c;y-=c;
            c=*(cp-*p++);x-=2*c;y-=c;
            c=*(cp-*p++);x-=c;y-=c;
            c=*(cp-*p++);y-=c;
            c=*(cp-*p++);x+=c;y-=c;
            c=*(cp-*p++);x+=2*c;y-=c;
            c=*(cp-*p);x+=3*c;y-=c;
            p+=x_size-6;

            c=*(cp-*p++);x-=3*c;
            c=*(cp-*p++);x-=2*c;
            c=*(cp-*p);x-=c;
            p+=2;
            c=*(cp-*p++);x+=c;
            c=*(cp-*p++);x+=2*c;
            c=*(cp-*p);x+=3*c;
            p+=x_size-6;
    
            c=*(cp-*p++);x-=3*c;y+=c;
            c=*(cp-*p++);x-=2*c;y+=c;
            c=*(cp-*p++);x-=c;y+=c;
            c=*(cp-*p++);y+=c;
            c=*(cp-*p++);x+=c;y+=c;
            c=*(cp-*p++);x+=2*c;y+=c;
            c=*(cp-*p);x+=3*c;y+=c;
            p+=x_size-5;

            c=*(cp-*p++);x-=2*c;y+=2*c;
            c=*(cp-*p++);x-=c;y+=2*c;
            c=*(cp-*p++);y+=2*c;
            c=*(cp-*p++);x+=c;y+=2*c;
            c=*(cp-*p);x+=2*c;y+=2*c;
            p+=x_size-3;

            c=*(cp-*p++);x-=c;y+=3*c;
            c=*(cp-*p++);y+=3*c;
            c=*(cp-*p);x+=c;y+=3*c;

            xx=x*x;
            yy=y*y;
            sq=xx+yy;
            if ( sq > ((n*n)/2) )
            {
              if(yy<xx) {
                divide=(float)y/(float)abs(x);
                sq=abs(x)/x;
                sq=*(cp-in[(i+FTOI(divide))*x_size+j+sq]) +
                   *(cp-in[(i+FTOI(2*divide))*x_size+j+2*sq]) +
                   *(cp-in[(i+FTOI(3*divide))*x_size+j+3*sq]);}
              else {
                divide=(float)x/(float)abs(y);
                sq=abs(y)/y;
                sq=*(cp-in[(i+sq)*x_size+j+FTOI(divide)]) +
                   *(cp-in[(i+2*sq)*x_size+j+FTOI(2*divide)]) +
                   *(cp-in[(i+3*sq)*x_size+j+FTOI(3*divide)]);}

              if(sq>290){
                m_pTempBuffer[i*x_size+j] = max_no-n;
                cgx[i*x_size+j] = (51*x)/n;
                cgy[i*x_size+j] = (51*y)/n;}
            }
	}
}}}}}}}}}}}}}}}}}}}

  /* to locate the local maxima */
  n=0;
  for (i=5;i<y_size-5;i++)
    for (j=5;j<x_size-5;j++) {
       x = m_pTempBuffer[i*x_size+j];
       if (x>0)  {
          /* 5x5 mask */
#ifdef FIVE_SUPP
          if (
              (x>m_pTempBuffer[(i-1)*x_size+j+2]) &&
              (x>m_pTempBuffer[(i  )*x_size+j+1]) &&
              (x>m_pTempBuffer[(i  )*x_size+j+2]) &&
              (x>m_pTempBuffer[(i+1)*x_size+j-1]) &&
              (x>m_pTempBuffer[(i+1)*x_size+j  ]) &&
              (x>m_pTempBuffer[(i+1)*x_size+j+1]) &&
              (x>m_pTempBuffer[(i+1)*x_size+j+2]) &&
              (x>m_pTempBuffer[(i+2)*x_size+j-2]) &&
              (x>m_pTempBuffer[(i+2)*x_size+j-1]) &&
              (x>m_pTempBuffer[(i+2)*x_size+j  ]) &&
              (x>m_pTempBuffer[(i+2)*x_size+j+1]) &&
              (x>m_pTempBuffer[(i+2)*x_size+j+2]) &&
              (x>=m_pTempBuffer[(i-2)*x_size+j-2]) &&
              (x>=m_pTempBuffer[(i-2)*x_size+j-1]) &&
              (x>=m_pTempBuffer[(i-2)*x_size+j  ]) &&
              (x>=m_pTempBuffer[(i-2)*x_size+j+1]) &&
              (x>=m_pTempBuffer[(i-2)*x_size+j+2]) &&
              (x>=m_pTempBuffer[(i-1)*x_size+j-2]) &&
              (x>=m_pTempBuffer[(i-1)*x_size+j-1]) &&
	      (x>=m_pTempBuffer[(i-1)*x_size+j  ]) &&
	      (x>=m_pTempBuffer[(i-1)*x_size+j+1]) &&
	      (x>=m_pTempBuffer[(i  )*x_size+j-2]) &&
	      (x>=m_pTempBuffer[(i  )*x_size+j-1]) &&
	      (x>=m_pTempBuffer[(i+1)*x_size+j-2]) )
#endif
#ifdef SEVEN_SUPP
          if ( 
                (x>m_pTempBuffer[(i-3)*x_size+j-3]) &&
                (x>m_pTempBuffer[(i-3)*x_size+j-2]) &&
                (x>m_pTempBuffer[(i-3)*x_size+j-1]) &&
                (x>m_pTempBuffer[(i-3)*x_size+j  ]) &&
                (x>m_pTempBuffer[(i-3)*x_size+j+1]) &&
                (x>m_pTempBuffer[(i-3)*x_size+j+2]) &&
                (x>m_pTempBuffer[(i-3)*x_size+j+3]) &&

                (x>m_pTempBuffer[(i-2)*x_size+j-3]) &&
                (x>m_pTempBuffer[(i-2)*x_size+j-2]) &&
                (x>m_pTempBuffer[(i-2)*x_size+j-1]) &&
                (x>m_pTempBuffer[(i-2)*x_size+j  ]) &&
                (x>m_pTempBuffer[(i-2)*x_size+j+1]) &&
                (x>m_pTempBuffer[(i-2)*x_size+j+2]) &&
                (x>m_pTempBuffer[(i-2)*x_size+j+3]) &&

                (x>m_pTempBuffer[(i-1)*x_size+j-3]) &&
                (x>m_pTempBuffer[(i-1)*x_size+j-2]) &&
                (x>m_pTempBuffer[(i-1)*x_size+j-1]) &&
                (x>m_pTempBuffer[(i-1)*x_size+j  ]) &&
                (x>m_pTempBuffer[(i-1)*x_size+j+1]) &&
                (x>m_pTempBuffer[(i-1)*x_size+j+2]) &&
                (x>m_pTempBuffer[(i-1)*x_size+j+3]) &&

                (x>m_pTempBuffer[(i)*x_size+j-3]) &&
                (x>m_pTempBuffer[(i)*x_size+j-2]) &&
                (x>m_pTempBuffer[(i)*x_size+j-1]) &&
                (x>=m_pTempBuffer[(i)*x_size+j+1]) &&
                (x>=m_pTempBuffer[(i)*x_size+j+2]) &&
                (x>=m_pTempBuffer[(i)*x_size+j+3]) &&

                (x>=m_pTempBuffer[(i+1)*x_size+j-3]) &&
                (x>=m_pTempBuffer[(i+1)*x_size+j-2]) &&
                (x>=m_pTempBuffer[(i+1)*x_size+j-1]) &&
                (x>=m_pTempBuffer[(i+1)*x_size+j  ]) &&
                (x>=m_pTempBuffer[(i+1)*x_size+j+1]) &&
                (x>=m_pTempBuffer[(i+1)*x_size+j+2]) &&
                (x>=m_pTempBuffer[(i+1)*x_size+j+3]) &&

                (x>=m_pTempBuffer[(i+2)*x_size+j-3]) &&
                (x>=m_pTempBuffer[(i+2)*x_size+j-2]) &&
                (x>=m_pTempBuffer[(i+2)*x_size+j-1]) &&
                (x>=m_pTempBuffer[(i+2)*x_size+j  ]) &&
                (x>=m_pTempBuffer[(i+2)*x_size+j+1]) &&
                (x>=m_pTempBuffer[(i+2)*x_size+j+2]) &&
                (x>=m_pTempBuffer[(i+2)*x_size+j+3]) &&

                (x>=m_pTempBuffer[(i+3)*x_size+j-3]) &&
                (x>=m_pTempBuffer[(i+3)*x_size+j-2]) &&
                (x>=m_pTempBuffer[(i+3)*x_size+j-1]) &&
                (x>=m_pTempBuffer[(i+3)*x_size+j  ]) &&
                (x>=m_pTempBuffer[(i+3)*x_size+j+1]) &&
                (x>=m_pTempBuffer[(i+3)*x_size+j+2]) &&
                (x>=m_pTempBuffer[(i+3)*x_size+j+3]) )
	#endif
	{
		CORNER cur_corner;
		cur_corner.info=0;
		cur_corner.x=j;
		cur_corner.y=i;
		cur_corner.dx=cgx[i*x_size+j];
		cur_corner.dy=cgy[i*x_size+j];
		cur_corner.I=in[i*x_size+j];
		m_CornerList.push_back(cur_corner);
	/*m_CornerList[n].info=0;
	m_CornerList[n].x=j;
	m_CornerList[n].y=i;
	m_CornerList[n].dx=cgx[i*x_size+j];
	m_CornerList[n].dy=cgy[i*x_size+j];
	m_CornerList[n].I=in[i*x_size+j];*/
	n++;
	if(n==MAX_CORNERS)
	{
		  fprintf(stderr,"Too many corners.\n");
		  exit(1);
			 }}}}
	//m_CornerList[n].info=7;

	free(cgx);
	free(cgy);
	delete [] m_pTempBuffer;

}

void CSusanCornerDetector::QuickDetect()
{
	//检查是否存在图像
	if (m_pdata==NULL)
	{
		//AfxMessageBox(TEXT("Susan算子中没有图像数据"));
		return;
	}
	
	// 创建查找表
	CreateLUT(); 

		int   n,x,y,i,j;
	unsigned char *p,*cp;
    //r是用来保存结果的缓冲区，x_size * y_size分别是宽度和高度，bp是LUT表的地址
	unsigned char*in=m_pdata;
	unsigned char*bp=m_pLUT;
	int x_size=m_nwidth;
	int y_size=m_nheight;

	BYTE* m_pTempBuffer=new BYTE[x_size* y_size];
	memset (m_pTempBuffer,0,x_size * y_size * sizeof(BYTE));
	
	for (i=7;i<y_size-7;i++)
		for (j=7;j<x_size-7;j++) {
			n=100;
			p=in + (i-3)*x_size + j - 1;
			cp=bp + in[i*x_size+j];
			
			n+=*(cp-*p++);
			n+=*(cp-*p++);
			n+=*(cp-*p);
        p+=x_size-3;

        n+=*(cp-*p++);
        n+=*(cp-*p++);
        n+=*(cp-*p++);
        n+=*(cp-*p++);
        n+=*(cp-*p);
        p+=x_size-5;

        n+=*(cp-*p++);
        n+=*(cp-*p++);
        n+=*(cp-*p++);
        n+=*(cp-*p++);
        n+=*(cp-*p++);
        n+=*(cp-*p++);
        n+=*(cp-*p);
        p+=x_size-6;

        n+=*(cp-*p++);
        n+=*(cp-*p++);
        n+=*(cp-*p);
      if (n<max_no){
        p+=2;
        n+=*(cp-*p++);
      if (n<max_no){
        n+=*(cp-*p++);
      if (n<max_no){
        n+=*(cp-*p);
      if (n<max_no){
        p+=x_size-6;

        n+=*(cp-*p++);
      if (n<max_no){
        n+=*(cp-*p++);
      if (n<max_no){
        n+=*(cp-*p++);
      if (n<max_no){
        n+=*(cp-*p++);
      if (n<max_no){
        n+=*(cp-*p++);
      if (n<max_no){
        n+=*(cp-*p++);
      if (n<max_no){
        n+=*(cp-*p);
      if (n<max_no){
        p+=x_size-5;

        n+=*(cp-*p++);
      if (n<max_no){
        n+=*(cp-*p++);
      if (n<max_no){
        n+=*(cp-*p++);
      if (n<max_no){
        n+=*(cp-*p++);
      if (n<max_no){
        n+=*(cp-*p);
      if (n<max_no){
        p+=x_size-3;

        n+=*(cp-*p++);
      if (n<max_no){
        n+=*(cp-*p++);
      if (n<max_no){
        n+=*(cp-*p);

        if (n<max_no)
          m_pTempBuffer[i*x_size+j] = max_no-n;
}}}}}}}}}}}}}}}}}}}

  /* to locate the local maxima */
  n=0;
  for (i=7;i<y_size-7;i++)
    for (j=7;j<x_size-7;j++) {
       x = m_pTempBuffer[i*x_size+j];
       if (x>0)  {
          /* 5x5 mask */
#ifdef FIVE_SUPP
          if (
              (x>m_pTempBuffer[(i-1)*x_size+j+2]) &&
              (x>m_pTempBuffer[(i  )*x_size+j+1]) &&
              (x>m_pTempBuffer[(i  )*x_size+j+2]) &&
              (x>m_pTempBuffer[(i+1)*x_size+j-1]) &&
              (x>m_pTempBuffer[(i+1)*x_size+j  ]) &&
              (x>m_pTempBuffer[(i+1)*x_size+j+1]) &&
              (x>m_pTempBuffer[(i+1)*x_size+j+2]) &&
              (x>m_pTempBuffer[(i+2)*x_size+j-2]) &&
              (x>m_pTempBuffer[(i+2)*x_size+j-1]) &&
              (x>m_pTempBuffer[(i+2)*x_size+j  ]) &&
              (x>m_pTempBuffer[(i+2)*x_size+j+1]) &&
              (x>m_pTempBuffer[(i+2)*x_size+j+2]) &&
              (x>=m_pTempBuffer[(i-2)*x_size+j-2]) &&
              (x>=m_pTempBuffer[(i-2)*x_size+j-1]) &&
              (x>=m_pTempBuffer[(i-2)*x_size+j  ]) &&
              (x>=m_pTempBuffer[(i-2)*x_size+j+1]) &&
              (x>=m_pTempBuffer[(i-2)*x_size+j+2]) &&
              (x>=m_pTempBuffer[(i-1)*x_size+j-2]) &&
              (x>=m_pTempBuffer[(i-1)*x_size+j-1]) &&
	      (x>=m_pTempBuffer[(i-1)*x_size+j  ]) &&
	      (x>=m_pTempBuffer[(i-1)*x_size+j+1]) &&
	      (x>=m_pTempBuffer[(i  )*x_size+j-2]) &&
	      (x>=m_pTempBuffer[(i  )*x_size+j-1]) &&
	      (x>=m_pTempBuffer[(i+1)*x_size+j-2]) )
#endif
#ifdef SEVEN_SUPP
          if ( 
                (x>m_pTempBuffer[(i-3)*x_size+j-3]) &&
                (x>m_pTempBuffer[(i-3)*x_size+j-2]) &&
                (x>m_pTempBuffer[(i-3)*x_size+j-1]) &&
                (x>m_pTempBuffer[(i-3)*x_size+j  ]) &&
                (x>m_pTempBuffer[(i-3)*x_size+j+1]) &&
                (x>m_pTempBuffer[(i-3)*x_size+j+2]) &&
                (x>m_pTempBuffer[(i-3)*x_size+j+3]) &&

                (x>m_pTempBuffer[(i-2)*x_size+j-3]) &&
                (x>m_pTempBuffer[(i-2)*x_size+j-2]) &&
                (x>m_pTempBuffer[(i-2)*x_size+j-1]) &&
                (x>m_pTempBuffer[(i-2)*x_size+j  ]) &&
                (x>m_pTempBuffer[(i-2)*x_size+j+1]) &&
                (x>m_pTempBuffer[(i-2)*x_size+j+2]) &&
                (x>m_pTempBuffer[(i-2)*x_size+j+3]) &&

                (x>m_pTempBuffer[(i-1)*x_size+j-3]) &&
                (x>m_pTempBuffer[(i-1)*x_size+j-2]) &&
                (x>m_pTempBuffer[(i-1)*x_size+j-1]) &&
                (x>m_pTempBuffer[(i-1)*x_size+j  ]) &&
                (x>m_pTempBuffer[(i-1)*x_size+j+1]) &&
                (x>m_pTempBuffer[(i-1)*x_size+j+2]) &&
                (x>m_pTempBuffer[(i-1)*x_size+j+3]) &&

                (x>m_pTempBuffer[(i)*x_size+j-3]) &&
                (x>m_pTempBuffer[(i)*x_size+j-2]) &&
                (x>m_pTempBuffer[(i)*x_size+j-1]) &&
                (x>=m_pTempBuffer[(i)*x_size+j+1]) &&
                (x>=m_pTempBuffer[(i)*x_size+j+2]) &&
                (x>=m_pTempBuffer[(i)*x_size+j+3]) &&

                (x>=m_pTempBuffer[(i+1)*x_size+j-3]) &&
                (x>=m_pTempBuffer[(i+1)*x_size+j-2]) &&
                (x>=m_pTempBuffer[(i+1)*x_size+j-1]) &&
                (x>=m_pTempBuffer[(i+1)*x_size+j  ]) &&
                (x>=m_pTempBuffer[(i+1)*x_size+j+1]) &&
                (x>=m_pTempBuffer[(i+1)*x_size+j+2]) &&
                (x>=m_pTempBuffer[(i+1)*x_size+j+3]) &&

                (x>=m_pTempBuffer[(i+2)*x_size+j-3]) &&
                (x>=m_pTempBuffer[(i+2)*x_size+j-2]) &&
                (x>=m_pTempBuffer[(i+2)*x_size+j-1]) &&
                (x>=m_pTempBuffer[(i+2)*x_size+j  ]) &&
                (x>=m_pTempBuffer[(i+2)*x_size+j+1]) &&
                (x>=m_pTempBuffer[(i+2)*x_size+j+2]) &&
                (x>=m_pTempBuffer[(i+2)*x_size+j+3]) &&

                (x>=m_pTempBuffer[(i+3)*x_size+j-3]) &&
                (x>=m_pTempBuffer[(i+3)*x_size+j-2]) &&
                (x>=m_pTempBuffer[(i+3)*x_size+j-1]) &&
                (x>=m_pTempBuffer[(i+3)*x_size+j  ]) &&
                (x>=m_pTempBuffer[(i+3)*x_size+j+1]) &&
                (x>=m_pTempBuffer[(i+3)*x_size+j+2]) &&
                (x>=m_pTempBuffer[(i+3)*x_size+j+3]) )
#endif
{
	CORNER cur_corner;
	cur_corner.info=0;
	cur_corner.x=j;
	cur_corner.y=i;
//m_CornerList[n].info=0;
//m_CornerList[n].x=j;
//m_CornerList[n].y=i;
x = in[(i-2)*x_size+j-2] + in[(i-2)*x_size+j-1] + in[(i-2)*x_size+j] + in[(i-2)*x_size+j+1] + in[(i-2)*x_size+j+2] +
    in[(i-1)*x_size+j-2] + in[(i-1)*x_size+j-1] + in[(i-1)*x_size+j] + in[(i-1)*x_size+j+1] + in[(i-1)*x_size+j+2] +
    in[(i  )*x_size+j-2] + in[(i  )*x_size+j-1] + in[(i  )*x_size+j] + in[(i  )*x_size+j+1] + in[(i  )*x_size+j+2] +
    in[(i+1)*x_size+j-2] + in[(i+1)*x_size+j-1] + in[(i+1)*x_size+j] + in[(i+1)*x_size+j+1] + in[(i+1)*x_size+j+2] +
    in[(i+2)*x_size+j-2] + in[(i+2)*x_size+j-1] + in[(i+2)*x_size+j] + in[(i+2)*x_size+j+1] + in[(i+2)*x_size+j+2];

cur_corner.I=x/25;
//m_CornerList[n].I=x/25;
/*m_CornerList[n].I=in[i*x_size+j];*/
x = in[(i-2)*x_size+j+2] + in[(i-1)*x_size+j+2] + in[(i)*x_size+j+2] + in[(i+1)*x_size+j+2] + in[(i+2)*x_size+j+2] -
   (in[(i-2)*x_size+j-2] + in[(i-1)*x_size+j-2] + in[(i)*x_size+j-2] + in[(i+1)*x_size+j-2] + in[(i+2)*x_size+j-2]);
x += x + in[(i-2)*x_size+j+1] + in[(i-1)*x_size+j+1] + in[(i)*x_size+j+1] + in[(i+1)*x_size+j+1] + in[(i+2)*x_size+j+1] -
        (in[(i-2)*x_size+j-1] + in[(i-1)*x_size+j-1] + in[(i)*x_size+j-1] + in[(i+1)*x_size+j-1] + in[(i+2)*x_size+j-1]);

y = in[(i+2)*x_size+j-2] + in[(i+2)*x_size+j-1] + in[(i+2)*x_size+j] + in[(i+2)*x_size+j+1] + in[(i+2)*x_size+j+2] -
   (in[(i-2)*x_size+j-2] + in[(i-2)*x_size+j-1] + in[(i-2)*x_size+j] + in[(i-2)*x_size+j+1] + in[(i-2)*x_size+j+2]);
y += y + in[(i+1)*x_size+j-2] + in[(i+1)*x_size+j-1] + in[(i+1)*x_size+j] + in[(i+1)*x_size+j+1] + in[(i+1)*x_size+j+2] -
        (in[(i-1)*x_size+j-2] + in[(i-1)*x_size+j-1] + in[(i-1)*x_size+j] + in[(i-1)*x_size+j+1] + in[(i-1)*x_size+j+2]);

cur_corner.dx=x/15;
cur_corner.dy=y/15;

m_CornerList.push_back(cur_corner);
//m_CornerList[n].dx=x/15;
//m_CornerList[n].dy=y/15;
n++;
if(n==MAX_CORNERS){
      fprintf(stderr,"Too many corners.\n");
      exit(1);
         }}}}
m_CornerList[n].info=7;


	
}