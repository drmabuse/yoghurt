#pragma once

#include <iostream>
#include <vector>
#include <complex>
#include <math.h>


/* fast fourier transform 
 * just a realization of simple algorithm  */

const double PI = 3.14159265; //


/* FFT itself
 * takes vector of complex numbers /source/ and vector of complex numbers /dest/
 * fourier-transforms /source/ into /dest/ */
void FFT(const std::vector<std::complex<double> > &source, std::vector<std::complex<double> > &dest);
