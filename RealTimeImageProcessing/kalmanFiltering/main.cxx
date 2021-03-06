#include <iostream>
#include <vector>
#include <Eigen/Dense>

#include "Kalman.h"

using namespace std;
using namespace myStd;

int main(int argc, char* argv[]) {
	cout << "I am in main kalman" << endl;
	int n = 3; //states no
	int m = 1; // measurements no

	double dt = 1.0/30; // Time step

	Eigen::MatrixXd A(n, n); 
	Eigen::MatrixXd C(m, n); 
	Eigen::MatrixXd Q(n, n); 
	Eigen::MatrixXd R(m, m); 
	Eigen::MatrixXd P(n, n); 

	A << 1, dt, 0, 0, 1, dt, 0, 0, 1;
	C << 1, 0, 0;

	Q << .05, .05, .0, .05, .05, .0, .0, .0, .0;
	R << 5;
	P << .1, .1, .1, .1, 10000, 10, .1, 10, 100;

	cout << "A: \n" << A << endl;
	cout << "C: \n" << C << endl;
	cout << "Q: \n" << Q << endl;
	cout << "R: \n" << R << endl;
	cout << "P: \n" << P << endl;

	// Construct the filter, calling constructor and initialize
	Kalman kalman(dt, A, C, Q, R, P);

	//  measurements (y)
	vector<double> measurements = {
		1.04202710058, 1.10726790452, 1.2913511148, 1.48485250951, 1.72825901034,
		1.74216489744, 2.11672039768, 2.14529225112, 2.16029641405, 2.21269371128,
		2.57709350237, 2.6682215744, 2.51641839428, 2.76034056782, 2.88131780617,
		2.88373786518, 2.9448468727, 2.82866600131, 3.0006601946, 3.12920591669,
		2.858361783, 2.83808170354, 2.68975330958, 2.66533185589, 2.81613499531,
		2.81003612051, 2.88321849354, 2.69789264832, 2.4342229249, 2.23464791825,
		2.30278776224, 2.02069770395, 1.94393985809, 1.82498398739, 1.52526230354,
		1.86967808173, 1.18073207847, 1.10729605087, 0.916168349913, 0.678547664519,
		0.562381751596, 0.355468474885, -0.155607486619, -0.287198661013, -0.602973173813
	};

	Eigen::VectorXd x0(n); // taking a n x 1 vector x
	x0 << measurements[0], 0, -9.81; // input the the n x 1 vector
	kalman.initGuess(dt, x0); // input the initial guess

	double t = 0;
	Eigen::VectorXd y(m); // initialize the y vector with size m x 1 
	cout << "t = " << t << ", " << "x_hat[0]: " << kalman.state().transpose() << endl;
	vector< double > r;
	vector< double > r2;
	for(int i = 0; i < measurements.size(); i++) {
		t += dt;
		y << measurements[i];
		kalman.filter(y);
		r.push_back(t);
		r2.push_back(kalman.state().transpose()[0]);
	}


	for(int i = 0; i < measurements.size(); i++)
	{
		cout << r[i] <<  ' ' << r2[i] << '\n'; 
	}
	cout << endl;

	return 0;
}
