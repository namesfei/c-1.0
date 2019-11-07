#include"trip.h"
int main()
{
	sta_shipdata mship = { {'1','2','3','4','5','6','7','8','9'}, "ั๔นโ",{'8','8','8','8'},90,18,5,2000 };
	Ship myship(mship);
	myship.set_position(123, 35);
	myship.set_speed_course(20, 90);
	myship.set_ship_profile();
	myship.showmessage();
	myship.set_ship_profile_byscale(1.0/10);
	myship.showmessage();
	cout << myship.ca_fangwei(123, 36) << " " << myship.ca_juli(123, 36) << endl;
	return 0;
}