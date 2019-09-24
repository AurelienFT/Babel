/*
** EPITECH PROJECT, 2019
** cpp_babel_2019
** File description:
** Audio
*/

#include <stdio.h>
#include "Audio.hpp"
#include <iostream>

Audio::Audio()
{
	PaError err;

	_audioData.maxFrameIndex = NUM_SECONDS * SAMPLE_RATE;
	_totalFrames = NUM_SECONDS * SAMPLE_RATE;
	_audioData.frameIndex = 0;
	_numSamples = _totalFrames * NUM_CHANNELS;
	int numBytes = _numSamples * sizeof(float);
	_audioData.recordedSamples = (float *)malloc(numBytes);
	for (int i = 0; i < _numSamples; i++)
		_audioData.recordedSamples[i] = 0;
	err = Pa_Initialize();
	if (err != paNoError)
		throw std::exception();

	_inputParameters.device = Pa_GetDefaultInputDevice();
	if (_inputParameters.device == paNoDevice)
	{
		throw std::exception();
	}
	_inputParameters.channelCount = 2;
	_inputParameters.sampleFormat = paFloat32;
	_inputParameters.suggestedLatency = Pa_GetDeviceInfo(_inputParameters.device)->defaultLowInputLatency;
	_inputParameters.hostApiSpecificStreamInfo = NULL;

	_outputParameters.device = Pa_GetDefaultOutputDevice();
	if (_outputParameters.device == paNoDevice)
	{
		throw std::exception();
	}
	_outputParameters.channelCount = 2;
	_outputParameters.sampleFormat = paFloat32;
	_outputParameters.suggestedLatency = Pa_GetDeviceInfo(_outputParameters.device)->defaultLowOutputLatency;
	_outputParameters.hostApiSpecificStreamInfo = NULL;
}

static int recordCallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags, void *userData)
{
	const float *in = (const float *)inputBuffer;
	long i = 0;
	audioData *data = (audioData *)userData;
	const float *rptr = (const float *)inputBuffer;
	float *wptr = &data->recordedSamples[data->frameIndex * NUM_CHANNELS];
	long framesToCalc = 0;
	int finished = 0;
	unsigned long framesLeft = data->maxFrameIndex - data->frameIndex;

	if (framesLeft < framesPerBuffer) {
		framesToCalc = framesLeft;
		finished = paComplete;
	} else {
		framesToCalc = framesPerBuffer;
		finished = paContinue;
	}

	if (inputBuffer == NULL) {
		for (i = 0; i < framesToCalc; i++) {
			*wptr++ = SAMPLE_SILENCE;
			if (NUM_CHANNELS == 2)
				*wptr++ = SAMPLE_SILENCE;
		}
	} else {
		for (i = 0; i < framesToCalc; i++) {
			*wptr++ = *rptr++;
			if (NUM_CHANNELS == 2)
				*wptr++ = *rptr++; /* right */
		}
	}
	data->frameIndex += framesToCalc;
	return finished;
};

static int listenCallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags, void *userData)
{
	audioData *data = (audioData *)userData;
	float *rptr = &data->recordedSamples[data->frameIndex * NUM_CHANNELS];
	float *wptr = (float *)outputBuffer;
	unsigned int i = 0;
	int finished = 0;
	unsigned int framesLeft = data->maxFrameIndex - data->frameIndex;

	if (framesLeft < framesPerBuffer) {
		for (i = 0; i < framesLeft; i++) {
			*wptr++ = *rptr++;
			if (NUM_CHANNELS == 2)
				*wptr++ = *rptr++;
		}
		for (; i < framesPerBuffer; i++) {
			*wptr++ = 0;
			if (NUM_CHANNELS == 2)
				*wptr++ = 0;
		}
		data->frameIndex += framesLeft;
		finished = paComplete;
	} else {
		for (i = 0; i < framesPerBuffer; i++) {
			*wptr++ = *rptr++;
			if (NUM_CHANNELS == 2)
				*wptr++ = *rptr++;
		}
		data->frameIndex += framesPerBuffer;
		finished = paContinue;
	}
	return finished;
}

audioData Audio::Record()
{
	PaError err = paNoError;

	err = Pa_OpenStream(&_streamInput, &_inputParameters, NULL, SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff, recordCallback, &_audioData);
	if (err != paNoError)
		throw std::exception();
	err = Pa_StartStream(_streamInput);
	if (err != paNoError)
		throw std::exception();

	while ((err = Pa_IsStreamActive(_streamInput)) == 1)
	{
		Pa_Sleep(1000);
		printf("index = %d\n", _audioData.frameIndex);
		fflush(stdout);
	}
}

audioData Audio::Listen()
{
	PaError err = paNoError;

	_audioData.frameIndex = 0;
	err = Pa_OpenStream(&_streamOutput, NULL, &_outputParameters, SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff, listenCallback, &_audioData);
	if (err != paNoError)
		throw std::exception();
	err = Pa_StartStream(_streamOutput);
	if (err != paNoError)
		throw std::exception();
	while ((err = Pa_IsStreamActive(_streamOutput)) == 1)
	{
		std::cout <<"test" << std::endl;
		Pa_Sleep(100);
	}
}

Audio::~Audio()
{
}
