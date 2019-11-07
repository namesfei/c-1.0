#include"trip.h"
#include<math.h>
Ship::Ship()
{
	//m_sta_shipdata.name=new char[30];
	//m_sta_shipdata.name= "";
	//for (int i = 0; i < 4; i++) {
	//	m_sta_shipdata.number[i] = '0';
	//}
	//for (int i = 0; i < 9; i++) {
	//	m_sta_shipdata.MMSI[i] = '0';
	//}
	//m_sta_shipdata.length=0.0;
	//m_sta_shipdata.width = 0.0;
	//m_sta_shipdata.draft = 0.0;
	//m_sta_shipdata.displacement = 0.0;
	m_sta_shipdata = new sta_shipdata;
	speed = 0.0;
	course = 0.0;
	latitude = 0.0;
	longitude = 0.0;
	ship_profile[0].x = 0; ship_profile[0].y = 0;
	ship_profile[1].x = 0; ship_profile[1].y = 0;
	ship_profile[2].x = 0; ship_profile[2].y = 0;
	ship_profile[3].x = 0; ship_profile[3].y = 0;
	ship_profile[4].x = 0; ship_profile[4].y = 0;
	//for (int i = 0; i < 4; i++) {
	//	ship_profile[i].x = 0;
	//	ship_profile[i].y = 0;
	//}
}
Ship::Ship(sta_shipdata stdat)
{
	//m_sta_shipdata.name = new char[30];
	//m_sta_shipdata.name = stdat.name;
	//for (int i = 0; i < 4; i++) {
	//	m_sta_shipdata.number[i] = stdat.number[i];
	//}
	//for (int i = 0; i < 9; i++) {
	//	m_sta_shipdata.MMSI[i] = stdat.MMSI[i];
	//}
	//m_sta_shipdata.length = stdat.length;
	//m_sta_shipdata.width = stdat.width;
	//m_sta_shipdata.draft = stdat.draft;
	//m_sta_shipdata.displacement = stdat.displacement;
	m_sta_shipdata = new sta_shipdata;
	m_sta_shipdata->name = stdat.name;
	for (int i = 0; i < 4; i++) {
		m_sta_shipdata->number[i] = stdat.number[i];
	}
	for (int i = 0; i < 9; i++) {
		m_sta_shipdata->MMSI[i] = stdat.MMSI[i];
	}
	m_sta_shipdata->length = stdat.length;
	m_sta_shipdata->width = stdat.width;
	m_sta_shipdata->draft = stdat.draft;
	m_sta_shipdata->displacement = stdat.displacement;
	speed = 0.0;
	course = 0.0;
	latitude = 0.0;
	longitude = 0.0;
	ship_profile[0].x = 0; ship_profile[0].y = 0;
	ship_profile[1].x = 0; ship_profile[1].y = 0;
	ship_profile[2].x = 0; ship_profile[2].y = 0;
	ship_profile[3].x = 0; ship_profile[3].y = 0;
	ship_profile[4].x = 0; ship_profile[4].y = 0;
	//for (int i = 0; i < 5; i++) {
	//	ship_profile[i].x = 0.0;
	//	ship_profile[i].y = 0.0;
	//}
}

Ship::~Ship()
{
	delete m_sta_shipdata;
}

void Ship::set_position(double latu, double lotu)
{
	latitude = latu;
	longitude = lotu;
}

void Ship::set_speed_course(double _speed, double _course) 
{
	speed = _speed;
	course = _course;
}
void Ship::set_ship_profile() 
{
	ship_profile[0].x = 0;
	ship_profile[0].y = 0;
	ship_profile[1].x = m_sta_shipdata->width;
	ship_profile[1].y = 0;
	ship_profile[2].x = 0;
	ship_profile[2].y = m_sta_shipdata->length;
	ship_profile[3].x = m_sta_shipdata->width;
	ship_profile[3].y = m_sta_shipdata->length;
	ship_profile[4].x= m_sta_shipdata->width*0.5;
	ship_profile[4].y = m_sta_shipdata->length*1.3;
}
void Ship:: dy_set_profile()
{
	for (int i = 0; i < 5; i++) {
		double x = ship_profile[i].x;
		double y = ship_profile[i].y;
		ship_profile[i].x = sin(course*3.14/180)*y+cos(course * 3.14 / 180)*x;
		ship_profile[i].y = cos(course * 3.14 / 180) * y - sin(course * 3.14 / 180) * x;
	}
}
void Ship::set_ship_profile_byscale(double scale) 
{
	for (int i = 0; i < 5; i++) {
		ship_profile[i].x *= scale;
		ship_profile[i].y *= scale;
	}
}

double Ship::ca_juli(double lati, double longi)
{
	//计算距离
	double a, b, R;
	R = 6378137; // 地球半径
	a = (lati-latitude)* 3.14 / 180.0;
	b = (longi-longitude) * 3.14 / 180.0;
	double sa2, sb2;
	sa2 = sin(a / 2.0);
	sb2 = sin(b / 2.0);
	double juli = 2 * R * asin(sqrt(sa2 * sa2 + cos(latitude * 3.14 / 180.0) * cos(lati * 3.14 / 180.0) * sb2 * sb2));
	return juli;
	
}
void Ship::showmessage()
{
	cout << "船名：" << m_sta_shipdata->name << endl;
	cout << "呼号：";
	for (int i = 0; i < 4; i++) {
		cout << m_sta_shipdata->number[i];
	}
	cout << endl;
	cout << "MMSI：";
	for (int i = 0; i < 9; i++) {
		cout << m_sta_shipdata->MMSI[i];
	}
	cout << endl;
	cout << "船长：" << m_sta_shipdata->length << "米" << endl;
	cout << "船宽：" << m_sta_shipdata->width << "米" << endl;
	cout << "吃水：" << m_sta_shipdata->draft << "米" << endl;
	cout << "排水：" << m_sta_shipdata->displacement << "吨" << endl;
	cout << "航向：" << course << "°" << endl;
	cout << "航速：" << speed << "km/h" << endl;
	cout << "船舶位置：" << latitude << "°";
	if (latitude < 0)
		cout << "S"<<" ";
	else
		cout << "N"<<" ";
	cout << longitude << "°";
	if (longitude < 0)
		cout << "W" << endl;
	else
		cout << "E" << endl;
	cout << "船舶轮廓信息：";
	for (int i = 0; i < 5; i++) {
		cout <<"("<< ship_profile[i].x << "," << ship_profile[i].y <<")"<< " ";
	}
	cout << endl;
}
double Ship::ca_fangwei(double lati, double longi)
{
	//计算方位
	double b = (longi - longitude) * 3.14 / 180.0;
	double y = sin(b) * cos(lati * 3.14 / 180.0);
	double x = cos(latitude * 3.14 / 180.0) * sin(lati * 3.14 / 180.0) - sin(latitude * 3.14 / 180.0) * cos(lati * 3.14 / 180.0) * cos(b);
	double brng = atan2(y, x) * 180;
	if (brng < 0)
		brng = brng + 360;
	return brng;
}
