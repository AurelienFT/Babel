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

#define SAMPLE_RATE (44100)
#define FRAMES_PER_BUFFER (512)
#define NUM_SECONDS     (5)
#define NUM_CHANNELS    (2)
#define SAMPLE_SILENCE  (0.0f)
static int gNumNoInputs = 0;

typedef struct {
   int frameIndex;
   int maxFrameIndex;
   float *recordedSamples;
} audioData;

class Audio
{
public:
	Audio();
	~Audio();
	audioData Record();
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
};

#endif /* !AUDIO_HPP_ */
