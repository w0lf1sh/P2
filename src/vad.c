#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "pav_analysis.h"
#include "vad.h"

const float FRAME_TIME = 10.0F; /* in milis. */

/* 
 * As the output state is only ST_VOICE, ST_SILENCE, or ST_UNDEF,
 * only this labels are needed. You need to add all labels, in case
 * you want to print the internal state in string format
 */

const char *state_str[] = {
    "UNDEF", "S", "V", "INIT"};

const char *state2str(VAD_STATE st)
{
  return state_str[st];
}

/* Define a datatype with interesting features */
typedef struct
{
  float zcr;
  float p;
  float am;
  //float init_power;
} Features;
/*
typedef struct
{
  int trm;        //Número de tramas tomadas como "inicial". Actuara como indice para el vector init_p[]
  float init_p[]; //potencias de las tramas tomadas como inciales
} Data;*/

/* 
 * TODO: Delete and use your own features!
 */
Features compute_features(const float *x, int N)
{
/*
   * Input: x[i] : i=0 .... N-1 
   * Ouput: computed features
   */
/* 
   * DELETE and include a call to your own functions
   *
   * For the moment, compute random value between 0 and 1 
   */

  /*
  static int llamadas = 1; //Cuenta las veces que llamamos a la función
  Data *d;
  if (llamadas == 1) //Asumimos primera trama de silencio y calculamos pot. Sera nuestro valor de referencia
  {
    d->trm = 0;
    d->init_p[0] = compute_power(x, N);
  }
  */
  Features feat;
  feat.zcr = compute_zcr(x, N, 16000);
  feat.p = compute_power(x, N);
  feat.am = compute_am(x, N);
/*
  if (feat.p < d->init_p[0] + 10) 
  {
    d->trm++;
    if (d->trm == llamadas) //Si no superamos el umbral, y nunca lo hemos superado antes, guardamos el power de la trama
    {
      d->init_p[d->trm] = feat.p;
    }
  }
  else if ((feat.p >= d->init_p[0] + 10) && (llamadas == d->trm + 1)) //El +1 es para que solo se entre una vez en esta
                                                                      //condicion
  {
    feat.init_power = compute_init_power(d->init_p, d->trm);
    printf("la potencia de las muestras iniciales es: %f", feat.init_power);
  }

  llamadas++;
  */
  return feat;
}

/* 
 * TODO: Init the values of vad_data
 */

VAD_DATA *vad_open(float rate, float alfa0)
{
  VAD_DATA *vad_data = malloc(sizeof(VAD_DATA)); //asigna la cantidad de memoria especificada en bytes
  vad_data->state = ST_INIT;
  vad_data->alfa0 = alfa0;
  vad_data->sampling_rate = rate;
  vad_data->frame_length = rate * FRAME_TIME * 1e-3;
  return vad_data;
}

//Devuelve el estado de la trama de señal
VAD_STATE vad_close(VAD_DATA *vad_data)
{
  /* 
   * TODO: decide what to do with the last undecided frames
   */
  VAD_STATE state = vad_data->state;

  free(vad_data);
  return state;
}

unsigned int vad_frame_size(VAD_DATA *vad_data)
{
  return vad_data->frame_length;
}

/* 
 * TODO: Implement the Voice Activity Detection 
 * using a Finite State Automata
 */

VAD_STATE vad(VAD_DATA *vad_data, float *x)
{

  /* 
   * TODO: You can change this, using your own features,
   * program finite state automaton, define conditions, etc.
   */
 // static int trama = 1;
  Features f = compute_features(x, vad_data->frame_length);
  vad_data->last_feature = f.p; /* save feature, in case you want to show */
  
  /*
    if (trama == 1){
      vad_data->k0 = f.p + vad_data->alfa0;
    }
    */
  switch (vad_data->state)
  {
  case ST_INIT:
    vad_data->k0 = f.p + vad_data->alfa0;
    vad_data->state = ST_SILENCE;
    break;

  case ST_SILENCE:
    if (f.p > vad_data->k0)
      vad_data->state = ST_VOICE;
    break;

  case ST_VOICE:
    if (f.p < vad_data->k0)
      vad_data->state = ST_SILENCE;
    break;

  case ST_UNDEF:
    break;
  }

  if (vad_data->state == ST_SILENCE ||
      vad_data->state == ST_VOICE)
    return vad_data->state;
  else
    return ST_UNDEF;
}

void vad_show_state(const VAD_DATA *vad_data, FILE *out)
{
  fprintf(out, "%d\t%f\n", vad_data->state, vad_data->last_feature);
}
