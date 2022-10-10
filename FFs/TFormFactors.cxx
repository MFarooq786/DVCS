/////////////////////////////////////////////////////////////////////////////////
//                                                                             //
//  Calculation of the elastic form factors using:                             //
//                                                                             //
//  1. Galster/Dipole parametrization                                          //
//                                                                             //
//     Calculates GM, GE, F1, F2, GA, and GP and from their t dependence       //
//                                                                             //
//  2. Kelly parametrization                                                   //
//                                                                             //
//  Written by Liliet Calero Diaz                                              //
/////////////////////////////////////////////////////////////////////////////////

#include <cmath>
#include "TFormFactors.h"

using namespace std;  	// std namespace: so you can do things like 'cout'

ClassImp(TFormFactors)				// classimp: necessary for root

// 1. ==================== Dipole parametrization used by Simonetta ===================


Double_t TFormFactors::ffGE(Double_t t) {
  Double_t GE = 1.0 / ( 1.0 + ( -t / 0.710649 ) ) / ( 1.0 + ( -t / 0.710649 ) );
  return GE;
}

Double_t TFormFactors::ffGM(Double_t t) {
  Double_t shape = ffGE(t);
  return GM0*shape;
}

Double_t TFormFactors::ffF2(Double_t t) {
  Double_t f2 = (ffGM(t) - ffGE(t)) / (1. - t / (4.*.938272*.938272));
  return f2;
}

Double_t TFormFactors::ffF1(Double_t t) {
  Double_t f1 = ffGM(t)- ffF2(t);
  return f1;
}

Double_t TFormFactors::ffGA(Double_t t) {
  Double_t ga = 1.2695;
  Double_t ma = 1.026;
  Double_t part = t/(ma*ma);
  Double_t dif = (1-part)*(1-part);
  Double_t GA = ga/dif;
  return GA;
}

Double_t TFormFactors::ffGP(Double_t t) {
  return 8.13;
}

// 2. =============== Kelly parametrization ================

Double_t TFormFactors::ffGEp(Double_t t) {
  Double_t tau = - t / 4. / M / M;
  Double_t GEp = ( 1. + a1_GEp * tau )/( 1. + b1_GEp * tau + b2_GEp * tau * tau + b3_GEp * tau * tau * tau );
  return GEp;
}

Double_t TFormFactors::ffGMp(Double_t t) {
  Double_t tau = - t / 4. / M / M;
  Double_t GMp = GM0 * ( 1. + a1_GMp * tau )/( 1. + b1_GMp * tau + b2_GMp * tau * tau + b3_GMp * tau * tau * tau );
  return GMp;
}

Double_t TFormFactors::ffF2_K(Double_t t) {
  Double_t tau = - t / 4. / M / M;
  Double_t f2_K = ( ffGMp(t) - ffGEp(t) ) / ( 1. + tau );
  return f2_K;
}

Double_t TFormFactors::ffF1_K(Double_t t) {
  Double_t tau = - t / 4. / M / M;
  Double_t f1_K = ( ffGMp(t) - ffF2_K(t) );
  return f1_K;
}
