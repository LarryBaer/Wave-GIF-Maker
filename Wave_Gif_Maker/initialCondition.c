#include <math.h>
double initialCondition(double x, double y) {
	// Tight point
	double sigma=0.01;

        // Wider point
	//double sigma=0.1;

	// Center
	double mu = 0.5;

	double result = (1.0/(2.0*M_PI*sigma*sigma))*exp(-0.5*( ((x-mu)/sigma)*((x-mu)/sigma) +  ((y-mu)/sigma)*((y-mu)/sigma)  ));
	return result;
}
