/*
** EPITECH PROJECT, 2019
** cpp_babel_2019
** File description:
** Audio
*/

#ifndef AUDIO_HPP_
#define AUDIO_HPP_

#include <math.h>
#include <portaudio.h>
#include <exception>
#include <vector>

#define SAMPLE_RATE 		(8000)
#define ENCODE_RATE			(80)
#define ENCODE_NUMBER 		(100)
#define FRAMES_PER_BUFFER 	(512)
#define NUM_SECONDS     	(1)
#define NUM_CHANNELS    	(2)
#define SAMPLE_SILENCE  	(0.0f)
#define SIZE_FLOAT_ARRAY	(16000)
static int gNumNoInputs = 0;

typedef struct {
   int frameIndexR;
   int frameIndexL;
   int maxFrameIndex;
   bool toSend;
   bool toRecv;
   float recordedSamples[SIZE_FLOAT_ARRAY * sizeof(float)];
   float listenedSamples[SIZE_FLOAT_ARRAY * sizeof(float)];
} audioData;

typedef struct {
	unsigned char data[SIZE_FLOAT_ARRAY];
	int32_t cuts[101];
} sendData;

class Audio
{
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
