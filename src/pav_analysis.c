#include <math.h>
#include "pav_analysis.h"
//FUNCIONES ENCARGADAS DE SACAR PARÄMETROS DE LA SEÑAL

float compute_power(const float *x, unsigned int N)
{
  float power = 0;
  for (int n = 0; n < N; n++)
  {
    power = power + (x[n]*x[n]);
  }
  power = 10*log10(power/N);
  return power;
}

float compute_am(const float *x, unsigned int N)
{
  float amplitude = 0;
  for (int n = 0; n < N; n++)
  {
    amplitude = amplitude + fabs(x[n]);
  }
  amplitude = amplitude/N;
  
  return amplitude;
}

float compute_zcr(const float *x, unsigned int N, float fm)
{
  float zcr = 0;
  for (int n = 1; n < N; n++)
  {
    if( (x[n]>0 && x[n-1]<0) || (x[n]<0 && x[n-1]>0) ){
      zcr++;
    }
  }
  zcr= (zcr/(N-1))*(fm/2);
  return zcr;
}