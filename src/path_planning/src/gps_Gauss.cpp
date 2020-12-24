//高斯坐标的正反算
#include<iostream>
#include<cmath>

#define PI 3.1415926535897932384626433832795
using namespace std;
//正算 x=3380330.773 y=320089.9761
//B=30° 30′ L=114°20′
void zhensuan()
{
    //这里输入的可能是度分秒，由于公式中要用COSB，所以要把B换成弧度，
    double d, f, m;
	cout << "输入B(°′″): " << endl;
	cin >> d >> f >> m;
	double dl, fl, ml;
	cout << "输入L(°′″): " << endl;
	cin >> dl >> fl >> ml;
 
	double _b = d + f / 60 + m / 3600;
 
	double B = (PI/180)*(_b);//角度要变为弧度 PI/180*B
 
	double L = dl + fl / 60 + ml / 3600;
 
	double c = 6399698.9017827110;
	double e = 0.006738525414683;//e"^2
	double m_e = 0.006693421622966;//e^2
 
	double V = sqrt(1 + e * cos(B)*cos(B));//v=根号下1+e'^2*cosB*cos(B)
 
 
	double p = 206264.806247096355;//p"
	double t = tan(B);
	double n = e * cos(B) * cos(B);//n^2
 
	double n6;
	if ((int)L % 6 == 0) {
		n6 = floor(L / 6) ;//按6度带划分 
	}
	else n6 = floor(L / 6)+1;
	double lm = n6 * 6 - 3;//中央子午线度数
	double l = fabs(L - lm)*3600;//l"以秒为单位 经差（p点经度和中央子午线之差）
	
	double a = 6378137.0;//单位m
	double b = 6356752.3142;//单位m

	double m_p = 1 / p;//p的倒数
	double N = c / V;
 
 
	//先求X
	
	
	double m1 = N * cos(B);
	double m2 = (N / 2) * sin(B) * cos(B);
	double m3 = (N / 6)* cos(B) * cos(B) * cos(B) * (1 - t * t + n );
	double m4 = (N / 24) * sin(B) * cos(B) * cos(B) * cos(B) * (5 - t * t + 9 * n  + 4 * n * n);
	double m5 = (N / 120) * cos(B) * cos(B) * cos(B) * cos(B) * cos(B) * (5 - 18 * t * t + t * t * t * t + 14 * n  - 58 * n  * t * t);
	double m6 = (N / 720) * sin(B) * cos(B) * cos(B) * cos(B) * cos(B) * cos(B) * (61 - 58 * t * t + t * t * t * t);
 
	double X = 111134.861 * (_b)-32005.780 * sin(B) * cos(B) - 133.929 * sin(B) * sin(B) * sin(B) * cos(B) - 0.698 * sin(B) * sin(B) * sin(B) * sin(B) * sin(B)*cos(B);
	//_b是度数哦
	double x = X + (m2 * m_p * m_p * l * l) + (m4 * m_p * m_p * m_p * m_p * l * l * l * l) + (m6 * m_p * m_p * m_p * m_p * m_p * m_p * l * l * l * l * l * l);
	double y = (N / p) * cos(B) * l + (N / (6 * p * p*p)) * cos(B) * cos(B) * cos(B) * (1 - t * t + n ) * l * l * l + (N / (120 * p * p * p * p * p)) * cos(B) * cos(B) * cos(B) * cos(B) * cos(B) * (5 - 18 * t * t + t * t * t * t + 14 * n - 58 * n  * t * t) * l * l * l * l * l;
	
 
	//输出
	cout << "正算结果：" << endl;
	cout << "x= " << x << endl;
	cout << "y= " << y << endl;
}
 
//坐标反算 x=3380330.773 y=320089.9761
//B=30° 30′ L=114°20′
//由x,y求B，L
void fansuan()
{
	cout << "输入坐标x,y:  " << endl;
	double x, y;
	cin >> x >> y;
 
	//迭代解法计算底点纬度
	double p = x / 6367588.4969;//弧度
 
	double Bd = p + (50221746 + (293622 + (2350 + 22 * cos(p) * cos(p)) * cos(p)) * cos(p)) * (1e-10) * sin(p) * cos(p);//底点坐标
 
	double c = 6399698.9017827110;
	double e = 0.006738525414683;//e"^2
	double m_e = 0.006693421622966;//e^2
 
	double Vd = sqrt(1 + e * cos(Bd));//v=根号下1+e'^2*cosB
	double td = tan(Bd);
	double nd = e * cos(Bd) * cos(Bd);
	double Nd = c / Vd;
	double Md = c / (Vd * Vd * Vd);
 
 
	double n1 = 1 / (Nd * cos(Bd));
	double n2 = (td / (2 * Md * Nd));
	double n3 = (1 + 2 * td * td + nd * nd) / (6 * Nd * Nd * Nd * cos(Bd));
	double n4 = (td * (5 + 3 * td * td + nd * nd - 9 * nd * nd * td * td)) / (24 * Md * Nd * Nd * Nd);
	double n5 = (5 + 28 * td * td + 24 * td * td * td * td + 6 * nd * nd + 8 * nd * nd * td * td) / (120 * Nd * Nd * Nd * Nd * Nd * cos(Bd));
	double n6 = (td * (61 + 90 * td * td + 45 * td * td * td * td)) / (720 * Md * Nd * Nd * Nd * Nd * Nd);
	
	double B = Bd - n2 * y * y + n4 * y * y * y * y-n6* y * y * y * y*y * y;
	double L = n1 * y - n3 * y * y * y + n5 * y * y * y * y * y;
	cout << "B= " << B << endl;//按弧度计算
	cout << "L= " << L << endl;
 
	cout << "转换成角度后：B=" << (180 / PI) * B << endl;
	cout << "转换成角度后：L= " << (180 / PI) * L << endl;//这里是经差，因为高斯坐标和国家统一坐标不同，不知其带号
}
int main() {

	zhensuan();
	//fansuan();
}