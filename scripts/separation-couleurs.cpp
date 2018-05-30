/*
* @Author: fra-592
* @Date:   2018-05-17 11:12:01
* @Last Modified by:   fra-592
* @Last Modified time: 2018-05-23 10:54:42
*/

// # define DEBUG

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char const *argv[])
{
	fstream f_input;
	fstream f_front, f_back;
	f_input.open(argv[1], ios::in);
	f_front.open("front.ply", ios::out);
	f_back.open("back.ply", ios::out);

	//On parcours les headers.
	string s("");
	while(s != "end_header")
	{
		getline(f_input, s);
		f_front << s << endl;
		f_back << s << endl;

		#ifdef DEBUG
		cout << s << endl;
		#endif
	}

	float x, y, z;
	int r, g, b, a;
	int c_front = 0;
	int c_back = 0;

	//On parcours les points. Ordre des champs: X, Y, Z, R, G, B, A
	while(f_input >> x >> y >> z >> r >> g >> b >> a)
	{
		#ifdef DEBUG
		cout << "x:"<< x << ", y:" << y << ", z:" << z << ", r:" << r << ", g:" << g << ", b:" << b << ", a:" << a << endl;
		#endif

		//Si on est rouge, on appartient à la face avant.
		if(g == 0){
			f_front << x << " " << y << " " << z << " " << r << " " << g << " " << b << " " << a << endl;
			c_front++;

		//Sinon, on fait partie du dos.
		} else {
			f_back << x << " " << y << " " << z << " " << r << " " << g << " " << b << " " << a << endl;
			c_back++;
		}
	}

	cout << "Front: " << c_front << ", back: " << c_back << endl;
	f_input.close();
	f_front.close();
	f_back.close();
	return(0);
}
