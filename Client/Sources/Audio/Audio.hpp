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

namespace Babel {
namespace audio {
class Audio : public IAudio {
public:
	Audio();
	~Audio();
	/**
	*	return true if record buffer is not done
	*/
	bool isRecording();
	/**
	*	return true if listen buffer is not done
	*/
	bool isListening();
	/**
	*	return data listened
	*/
	audioData getAudioData();
	/**
	*	reset audioData, to record permanantly
	*/
	void resetAudioData();
	
	/**
	*	set audio to listen
	*	@param data to be listened
	*/
	void setAudioData(audioData &data);
	/**
	*	set audio to listen at index
	*	@param data to be listened
	*	@param index
	*/
	void addAudioData(float *data, const int &index);
	/**
	*	return true if data is ready to be send
	*/
	bool getSendStatus();
	/**
	*	return true if object is ready to record new data
	*/
	bool getRecvStatus();

	/**
	*	reset status of received data
	*/
	void resetRecvStatus();
	/**
	*	reset status of sended data
	*/
	void resetSendStatus();

	/**
	*	start recording stream
	*/
	void Record();
	/**
	*	start listening stream
	*/
	audioData Listen();
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
}
}

#endif /* !AUDIO_HPP_ */
