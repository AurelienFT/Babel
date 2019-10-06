/*
** EPITECH PROJECT, 2019
** cpp_babel_2019
** File description:
** Audio
*/

#ifndef AUDIO_HPP_
#define AUDIO_HPP_

#include <portaudio.h>
#include <exception>
#include <vector>

#include "IAudio.hpp"

class Audio : public IAudio {
public:
	Audio();
	~Audio();
	bool isRecording();
	bool isListening();
	audioData getAudioData();
	void resetAudioData();
	
	void setAudioData(audioData &data);
	void addAudioData(float *data, const int &index);
	bool getSendStatus();
	bool getRecvStatus();

	void resetRecvStatus();
	void resetSendStatus();

	void Record();
	audioData Listen();
	void Listen(audioData &data);
	void stopStream();
protected:
private:
	PaStreamParameters _inputParameters;
	PaStreamParameters _outputParameters;
	PaStream *_streamInput;
	PaStream *_streamOutput;
	audioData _audioData;
	int _numSamples;
	int _totalFrames;

	std::vector<float> _listenData;
};

#endif /* !AUDIO_HPP_ */
