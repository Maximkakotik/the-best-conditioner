#include <iostream>
#include <fstream>
#include <string>
#include <exception>
#include "json.hpp"
#include "pugixml.hpp"
using namespace pugi;
using json = nlohmann::json;
using namespace std;
class AirConditioner {
private:
	int t = 10;
	int v = 1;
public:
	AirConditioner() {
		cout << "temp=10; speed=1" << endl;
	}
	void setT(int k) {
		if (k >= 10 && k <= 30) {
			t = k;
		}
		else {
			exception();
		}
	}
	void setV(int k) {
		if (k >= 1 && k <= 10) {
			v = k;
		}
		else {
			exception();
		}
	}
	void tempplus() {
		if (this->t < 30) {
			this->t++;
		}
		else {
			cout << "max temp" << endl;
		}
	}
	void tempminus() {
		if (this->t > 10) {
			this->t--;
		}
		else {
			cout << "min temp" << endl;
		}
	}
	void vplus() {
		if (this->v >= 1 && this->v < 10) {
			this->v++;
		}
		else {
			this->v = 1;
		}
	}
	void vminus() {
		if (this->v > 1 && this->v <= 10) {
			this->v--;
		}
		else {
			this->v = 10;
		}
	}
	int getT() {
		return this->t;
	}
	int getV() {
		return this->v;
	}
};
int main()
{
	AirConditioner one;
	one.setT(13);
	one.setV(5);
	json f;
	f["temp"] = one.getT();
	f["speed"] = one.getV();
	ofstream file("air.json");
	file << setw(4) << f << endl;
	one.setT(18);
	one.setV(9);
	// xml
	xml_document doc;
	xml_node main_node = doc.append_child("conditioners");
	xml_node cond_node = main_node.append_child("conditioner");

	xml_attribute attr = cond_node.append_attribute("name");
	attr.set_value("one");
	xml_node temp_node = cond_node.append_child("temp");
	temp_node.text().set(one.getT());
	xml_node speed_node = cond_node.append_child("speed");
	speed_node.text().set(one.getV());

	doc.save_file("air.xml");
}