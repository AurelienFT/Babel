/*
** EPITECH PROJECT, 2019
** cpp_babel_2019
** File description:
** IAudio
*/

#ifndef IAUDIO_HPP_
#define IAUDIO_HPP_

#include <math.h>

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

namespace Babel {
namespace audio {
class IAudio
{
public:
	IAudio() = default;
	~IAudio() = default;
	
    virtual bool isRecording() = 0;
	virtual bool isListening() = 0;
	virtual audioData getAudioData() = 0;
	virtual void resetAudioData() = 0;

	virtual void setAudioData(audioData &data) = 0;
	virtual void addAudioData(float *data, const int &index) = 0;
	virtual bool getSendStatus() = 0;
	virtual bool getRecvStatus() = 0;

	virtual void resetRecvStatus() = 0;
	virtual void resetSendStatus() = 0;

	virtual void Record() = 0;
	virtual audioData Listen() = 0;
protected:
private:
};
}
}

#endif /* !IAUDIO_HPP_ */
