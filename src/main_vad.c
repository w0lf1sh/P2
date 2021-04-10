#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sndfile.h>

#include "vad.h"
#include "vad_docopt.h"

#define DEBUG_VAD 0x1

int main(int argc, char *argv[])
{
  int verbose = 0; /* To show internal state of vad: verbose = DEBUG_VAD; */

  SNDFILE *sndfile_in, *sndfile_out = 0;
  SF_INFO sf_info;
  FILE *vadfile;
  int n_read = 0, i;
  int n_write = 0; // Número de bytes que escribira la función sf_write_float()

  VAD_DATA *vad_data;
  VAD_STATE state, last_state, last_defined_state;

  float *buffer, *buffer_zeros;
  int frame_size;         /* in samples */
  float frame_duration;   /* in seconds */
  unsigned int t, last_t; /* in frames */

  char *input_wav, *output_vad, *output_wav;

  DocoptArgs args = docopt(argc, argv, /* help */ 1, /* version */ "2.0");
  float alfa0 = atof(args.alfa0);

  verbose = args.verbose ? DEBUG_VAD : 0;
  input_wav = args.input_wav;
  output_vad = args.output_vad;
  output_wav = args.output_wav;

  if (input_wav == 0 || output_vad == 0)
  {
    fprintf(stderr, "%s\n", args.usage_pattern);
    return -1;
  }

  /* Open input sound file */
  if ((sndfile_in = sf_open(input_wav, SFM_READ, &sf_info)) == 0)
  {
    fprintf(stderr, "Error opening input file %s (%s)\n", input_wav, strerror(errno));
    return -1;
  }

  if (sf_info.channels != 1)
  {
    fprintf(stderr, "Error: the input file has to be mono: %s\n", input_wav);
    return -2;
  }

  /* Open vad file */
  if ((vadfile = fopen(output_vad, "wt")) == 0)
  {
    fprintf(stderr, "Error opening output vad file %s (%s)\n", output_vad, strerror(errno));
    return -1;
  }

  /* Open output sound file, with same format, channels, etc. than input */
  if (output_wav)
  {
    if ((sndfile_out = sf_open(output_wav, SFM_WRITE, &sf_info)) == 0)
    {
      fprintf(stderr, "Error opening output wav file %s (%s)\n", output_wav, strerror(errno));
      return -1;
    }
  }

  vad_data = vad_open(sf_info.samplerate, alfa0);
  /* Allocate memory for buffers */
  frame_size = vad_frame_size(vad_data);
  buffer = (float *)malloc(frame_size * sizeof(float));
  buffer_zeros = (float *)malloc(frame_size * sizeof(float));
  for (i = 0; i < frame_size; ++i)
    buffer_zeros[i] = 0.0F;

  frame_duration = (float)frame_size / (float)sf_info.samplerate;
  last_state = ST_UNDEF;
  last_defined_state = ST_SILENCE;

  for (t = last_t = 0;; t++)
  { /* For each frame ... */
    /* End loop when file has finished (or there is an error) */
    if ((n_read = sf_read_float(sndfile_in, buffer, frame_size)) != frame_size)
      break;

    //Copiamos la trama del fichero original "wav" al fichero .wav output en caso de haberlo especificado
    if (sndfile_out != 0)
    {
      /* TODO: copy all the samples into sndfile_out */
      if ((n_write = sf_write_float(sndfile_out, buffer, frame_size)) != frame_size)
        break;
    }

    state = vad(vad_data, buffer);

    if (verbose & DEBUG_VAD)
      vad_show_state(vad_data, stdout);

    if (state == ST_SILENCE || state == ST_VOICE)
    {
      last_defined_state = state;
    }

    /* TODO: print only SILENCE and VOICE labels */
    /* As it is, it prints UNDEF segments but is should be merge to the proper value */
    if (state != last_state)
    {
      if ((t != last_t) && (last_state == ST_UNDEF && vad_data->trama == 10))
      { //Condición que solo se cumple para el principio
        fprintf(vadfile, "%.5f\t%.5f\t%s\n", last_t * frame_duration, t * frame_duration, state2str(ST_SILENCE));
        vad_data->trama++; //Aumentamos el número de tramas para que esta condición ya no se cumpla
      }
      else if ((t != last_t) && (last_state == ST_UNDEF && state == ST_SILENCE))
      {
        if (last_defined_state == ST_SILENCE)
        {
          fprintf(vadfile, "%.5f\t%.5f\t%s\n", last_t * frame_duration, t * frame_duration, state2str(ST_SILENCE));
        }
        else
        {
          fprintf(vadfile, "%.5f\t%.5f\t%s\n", last_t * frame_duration, t * frame_duration, state2str(ST_VOICE));
        }
      }
      else if ((t != last_t) && (last_state == ST_UNDEF && state == ST_VOICE))
      {
        if (last_defined_state == ST_VOICE)
        {
          fprintf(vadfile, "%.5f\t%.5f\t%s\n", last_t * frame_duration, t * frame_duration, state2str(ST_VOICE));
        }
        else
        {
          fprintf(vadfile, "%.5f\t%.5f\t%s\n", last_t * frame_duration, t * frame_duration, state2str(ST_SILENCE));
        }
      }
      else if (t != last_t)
      {
        if (last_state != ST_UNDEF)
        {
          fprintf(vadfile, "%.5f\t%.5f\t%s\n", last_t * frame_duration, t * frame_duration, state2str(last_state));
        }
        else
        {
          fprintf(vadfile, "%.5f\t%.5f\t%s\n", last_t * frame_duration, t * frame_duration, state2str(last_defined_state));
        }
      }

      last_state = state;
      last_t = t;
    }

    if (sndfile_out != 0)
    {
      /* TODO: go back and write zeros in silence segments */
      if (state == ST_SILENCE)
      {
        //Primero nos colocamos de vuelta a la posición de la trama de silencio desde la posición actual (SEEK_CUR)
        if (sf_seek(sndfile_out, (-1) * frame_size, SEEK_CUR) == -1)
          break;
        //ya posicionados, sobreescribimos el fichero .wav
        if ((n_write = sf_write_float(sndfile_out, buffer_zeros, frame_size)) != frame_size)
          break;
      }
    }
  }

  state = vad_close(vad_data);
  /* TODO: what do you want to print, for last frames? */
  if (t != last_t){
    if (state == ST_UNDEF)
    {
      fprintf(vadfile, "%.5f\t%.5f\t%s\n", last_t * frame_duration, t * frame_duration + n_read / (float)sf_info.samplerate, state2str(last_defined_state));
    }
    else
    {
      fprintf(vadfile, "%.5f\t%.5f\t%s\n", last_t * frame_duration, t * frame_duration + n_read / (float)sf_info.samplerate, state2str(state));
    }
  }
  /* clean up: free memory, close open files */
  free(buffer);
  free(buffer_zeros);
  sf_close(sndfile_in);
  fclose(vadfile);
  if (sndfile_out)
    sf_close(sndfile_out);
  return 0;
}
