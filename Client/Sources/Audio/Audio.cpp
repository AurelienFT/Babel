/*
** EPITECH PROJECT, 2019
** cpp_babel_2019
** File description:
** Audio
*/

#include <stdio.h>
#include <iostream>
#include "Audio.hpp"

Babel::audio::Audio::Audio()
{
	PaError err;

	_audioData.maxFrameIndex = SAMPLE_RATE * NUM_SECONDS;
	_totalFrames = _audioData.maxFrameIndex;
	_audioData.frameIndexL = 0;
	_audioData.frameIndexR = 0;
	_audioData.toRecv = true;
	_audioData.toSend = false;
	_numSamples = _totalFrames * NUM_CHANNELS;
	int numBytes = _numSamples * sizeof(float);
	for (int i = 0; i < _numSamples; i++)
		_audioData.recordedSamples[i] = 0;
	err = Pa_Initialize();
	if (err != paNoError)
		throw std::exception();

	_inputParameters.device = Pa_GetDefaultInputDevice();
	if (_inputParameters.device == paNoDevice) {
		throw std::exception();
	}
	_inputParameters.channelCount = 2;
	_inputParameters.sampleFormat = paFloat32;
	_inputParameters.suggestedLatency = Pa_GetDeviceInfo(_inputParameters.device)->defaultLowInputLatency;
	_inputParameters.hostApiSpecificStreamInfo = NULL;

	_outputParameters.device = Pa_GetDefaultOutputDevice();
	if (_outputParameters.device == paNoDevice) {
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
	float *wptr = &data->recordedSamples[data->frameIndexR * NUM_CHANNELS];
	long framesToCalc = 0;
	int finished = 0;
	unsigned long framesLeft = data->maxFrameIndex - data->frameIndexR;

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
	data->frameIndexR += framesToCalc;
	if (data->frameIndexR == data->maxFrameIndex) {
		data->frameIndexR = 0;
		data->toSend = true;
		finished = paContinue;
	}
	return finished;
};

static int listenCallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags, void *userData)
{
	audioData *data = (audioData *)userData;
	float *rptr = &data->listenedSamples[data->frameIndexL * NUM_CHANNELS];
	float *wptr = (float *)outputBuffer;
	unsigned int i = 0;
	int finished = 0;
	unsigned int framesLeft = data->maxFrameIndex - data->frameIndexL;

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
		data->frameIndexL = 0;
		data->toRecv = true;
		finished = paContinue;
	} else {
		for (i = 0; i < framesPerBuffer; i++) {
			*wptr++ = *rptr++;
			if (NUM_CHANNELS == 2)
				*wptr++ = *rptr++;
		}
		data->frameIndexL += framesPerBuffer;
		finished = paContinue;
	}
	return finished;
}

bool Babel::audio::Audio::isRecording()
{
	if (Pa_IsStreamActive(_streamInput) == 1)
		return true;
	return false;
}

bool Babel::audio::Audio::isListening()
{
	if (Pa_IsStreamActive(_streamOutput) == 1)
		return true;
	return false;
}

bool Babel::audio::Audio::getSendStatus()
{
	return _audioData.toSend;
}

bool Babel::audio::Audio::getRecvStatus()
{
	return _audioData.toRecv;
}

void Babel::audio::Audio::resetRecvStatus()
{
	_audioData.toRecv = false;
}

void Babel::audio::Audio::resetSendStatus()
{
	_audioData.toSend = false;
}

audioData Babel::audio::Audio::getAudioData()
{
	return _audioData;
}

void Babel::audio::Audio::resetAudioData()
{
	_audioData.frameIndexL = 0;
}

void Babel::audio::Audio::setAudioData(audioData &data)
{
	_audioData = data;
}

void Babel::audio::Audio::addAudioData(float *data, const int &index)
{
	for (auto i = 0; i < SIZE_FLOAT_ARRAY; i++) {
		_audioData.listenedSamples[i + index] = data[i];
	}
}

void Babel::audio::Audio::Record()
{
	PaError err = paNoError;

	err = Pa_OpenStream(&_streamInput, &_inputParameters, NULL, SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff, recordCallback, &_audioData);
	if (err != paNoError)
		throw std::exception();
	err = Pa_StartStream(_streamInput);
	if (err != paNoError)
		throw std::exception();
}

audioData Babel::audio::Audio::Listen()
{
	PaError err = paNoError;

	_audioData.frameIndexL = 0;
	err = Pa_OpenStream(&_streamOutput, NULL, &_outputParameters, SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff, listenCallback, &_audioData);
	if (err != paNoError)
		throw std::exception();
	err = Pa_StartStream(_streamOutput);
	if (err != paNoError)
		throw std::exception();
}

Babel::audio::Audio::~Audio()
{
}

void Babel::audio::Audio::stopStream()
{
	Pa_CloseStream(_streamInput);
	Pa_CloseStream(_streamOutput);
}
