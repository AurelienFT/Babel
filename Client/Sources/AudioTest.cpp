/*
** EPITECH PROJECT, 2019
** cpp_babel_2019
** File description:
** AudioTest
*/

/*
    7  * $Id$
    8  *
    9  * This program uses the PortAudio Portable Audio Library.
   10  * For more information see: http://www.portaudio.com
   11  * Copyright (c) 1999-2000 Ross Bencina and Phil Burk
   12  *
   13  * Permission is hereby granted, free of charge, to any person obtaining
   14  * a copy of this software and associated documentation files
   15  * (the "Software"), to deal in the Software without restriction,
   16  * including without limitation the rights to use, copy, modify, merge,
   17  * publish, distribute, sublicense, and/or sell copies of the Software,
   18  * and to permit persons to whom the Software is furnished to do so,
   19  * subject to the following conditions:
   20  *
   21  * The above copyright notice and this permission notice shall be
   22  * included in all copies or substantial portions of the Software.
   23  *
   24  * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   25  * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   26  * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   27  * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
   28  * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
   29  * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
   30  * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
   31  */ /*
   34  * The text above constitutes the entire PortAudio license; however, 
   35  * the PortAudio community also makes the following non-binding requests:
   36  *
   37  * Any person wishing to distribute modifications to the Software is
   38  * requested to send the modifications to the original developer so that
   39  * they can be incorporated into the canonical version. It is also 
   40  * requested that these non-binding requests be included along with the 
   41  * license above.
   42  */

#include <stdio.h>
#include <math.h>
#include "portaudio.h"

/*
   48 ** Note that many of the older ISA sound cards on PCs do NOT support
   49 ** full duplex audio (simultaneous record and playback).
   50 ** And some only support full duplex at lower sample rates.
   51 */

#define SAMPLE_RATE (44100)
#define PA_SAMPLE_TYPE paFloat32
#define FRAMES_PER_BUFFER (64)

typedef float SAMPLE;

static int gNumNoInputs = 0;
/* This routine will be called by the PortAudio engine when audio is needed.
 ** It may be called at interrupt level on some machines so don't do anything
 ** that could mess up the system like calling malloc() or free().
 */
static int soundCallback(const void *inputBuffer, void *outputBuffer,
			unsigned long framesPerBuffer,
			const PaStreamCallbackTimeInfo *timeInfo,
			PaStreamCallbackFlags statusFlags,
			void *userData)
{
	SAMPLE *out = (SAMPLE *)outputBuffer;
	const SAMPLE *in = (const SAMPLE *)inputBuffer;
	unsigned int i;
	(void)timeInfo; /* Prevent unused variable warnings. */
	(void)statusFlags;
	(void)userData;

	if (inputBuffer == NULL)
	{
		for (i = 0; i < framesPerBuffer; i++)
		{
			*out++ = 0; /* left - silent */
			*out++ = 0; /* right - silent */
		}
		gNumNoInputs += 1;
	}
	else
	{
		for (i = 0; i < framesPerBuffer; i++)
		{
			*out++ = *in++; /* left - distorted */
			*out++ = *in++;       /* right - clean */
		}
	}

	return paContinue;
}

/*******************************************************************/
int main(void)
{
	PaStreamParameters inputParameters, outputParameters;
	PaStream *stream;
	PaError err;

	err = Pa_Initialize();
	if (err != paNoError)
		goto error;

	inputParameters.device = Pa_GetDefaultInputDevice(); /* default input device */
	if (inputParameters.device == paNoDevice)
	{
		fprintf(stderr, "Error: No default input device.\n");
		goto error;
	}
	inputParameters.channelCount = 2; /* stereo input */
	inputParameters.sampleFormat = PA_SAMPLE_TYPE;
	inputParameters.suggestedLatency = Pa_GetDeviceInfo(inputParameters.device)->defaultLowInputLatency;
	inputParameters.hostApiSpecificStreamInfo = NULL;

	outputParameters.device = Pa_GetDefaultOutputDevice(); /* default output device */
	if (outputParameters.device == paNoDevice)
	{
		fprintf(stderr, "Error: No default output device.\n");
		goto error;
	}
	outputParameters.channelCount = 2; /* stereo output */
	outputParameters.sampleFormat = PA_SAMPLE_TYPE;
	outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
	outputParameters.hostApiSpecificStreamInfo = NULL;

	err = Pa_OpenStream(
	    &stream,
	    &inputParameters,
	    &outputParameters,
	    SAMPLE_RATE,
	    FRAMES_PER_BUFFER,
	    0, /* paClipOff, */ /* we won't output out of range samples so don't bother clipping them */
	    soundCallback,
	    NULL);
	if (err != paNoError)
		goto error;
	err = Pa_StartStream(stream);
	if (err != paNoError)
		goto error;

	printf("Hit ENTER to stop program.\n");
	getchar();
	err = Pa_CloseStream(stream);
	if (err != paNoError)
		goto error;

	printf("Finished. gNumNoInputs = %d\n", gNumNoInputs);
	Pa_Terminate();
	return 0;

error:
	Pa_Terminate();
	fprintf(stderr, "An error occured while using the portaudio stream\n");
	fprintf(stderr, "Error number: %d\n", err);
	fprintf(stderr, "Error message: %s\n", Pa_GetErrorText(err));
	return -1;
}