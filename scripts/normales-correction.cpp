/*
* @Author: fra-592
* @Date:   2018-05-17 11:12:01
* @Last Modified by:   fra-592
* @Last Modified time: 2018-05-23 10:54:40
*/

// #define DEBUG

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char const *argv[])
{
	fstream f_input;
	fstream f_output;
	f_input.open(argv[1], ios::in);
	f_output.open("parsed.ply", ios::out);


	//On parcours les headers.
	string s("");
	while(s != "end_header")
	{
		getline(f_input, s);
		f_output << s << endl;

		#ifdef DEBUG
		cout << s << endl;
		#endif
	}

	float x, y, z, nx, ny, nz;
	int r, g, b, a;
	//On parcours les points. Ordre des champs: X, Y, Z, NX, NY, NZ, R, G, B, A
	while(f_input >> x >> y >> z >> nx >> ny >> nz >> r >> g >> b >> a)
	{
		#ifdef DEBUG
		cout << "x:"<< x << ", y:" << y << ", z:" << z << ", nx:" << nx << ", ny:" << ny << ", nz:" << nz << ", r:" << r << ", g:" << g << ", b:" << b << ", a:" << a << endl;
		#endif

		//Si on est rouge, on doit être selon les z croissants.
		if((g == 0) & (nz < 0)){
			nx *= -1;
			ny *= -1;
			nz *= -1;

			#ifdef DEBUG
			cout << "inverted" << endl;
			#endif

		//Sinon, on doit être selon les z décroissants.
		} else if ((g == 255) && (nz >0)){
			nx *= -1;
			ny *= -1;
			nz *= -1;
			#ifdef DEBUG
			cout << "inverted" << endl;
			#endif
		}

		f_output << x << " " << y << " " << z << " " << nx << " " << ny << " " << nz << " " << r << " " << g << " " << b << " " << a << endl;

	}

	f_input.close();
	f_output.close();
	return(0);
}
