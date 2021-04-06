#ifndef PAV_ANALYSIS_H
#define PAV_ANALYSIS_H
//typedef struct data_t Data_t;

float compute_power(const float *x, unsigned int N);

float compute_am(const float *x, unsigned int N);

float compute_zcr(const float *x, unsigned int N, float fm);

//float compute_init_power(float p);

#endif /* PAV_ANALYSIS_H */