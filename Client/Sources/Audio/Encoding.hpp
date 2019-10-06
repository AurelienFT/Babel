/*
** EPITECH PROJECT, 2019
** cpp_babel_2019
** File description:
** Encoding
*/

#ifndef ENCODING_HPP_
#define ENCODING_HPP_

#include <opus.h>

#include "IEncoding.hpp"

namespace Babel {
namespace audio {
class Encoding : public IEncoding {
	public:
		Encoding() = default;
		~Encoding() = default;

        /**
    	*	creating encoder
        *   @param Fs sample_rate
        *   @param channels number of channels
        *   @param application from opus lib
        *   @param err error code from opus lib
	    */
        void encode_create(int Fs, int channels, int application, int *err)
        {
            encoder = opus_encoder_create(Fs, channels, application, err);
        };
        /**
    	*	encode float* in char*
        *   @param pcm data to be encoded
        *   @param frame_size of pcm
        *   @param data encoded
        *   @param max_data_bytes to be encoded
	    */
        int encode_float(const float * pcm, int frame_size, unsigned char * data, int max_data_bytes)
        {
            return opus_encode_float(encoder, pcm, frame_size, data, max_data_bytes);
        };
        
        /**
    	*	creating decoder
        *   @param Fs sample_rate
        *   @param channels number of channel
        *   @param err from opus lib
	    */
        void decode_create(int Fs, int channels, int *err)
        {
            decoder = opus_decoder_create(Fs, channels, err);
        };
        /**
    	*	encode float* in char*
        *   @param data data to be decoded
        *   @param len of data
        *   @param pcm decoded
        *   @param frame_size to be decoded
        *   @param decode_fec from opus lib
	    */
        int decode_float(const unsigned char *data, int len, float *pcm, int frame_size, int decode_fec)
        {
            return opus_decode_float(decoder, data, len, pcm, frame_size, decode_fec);
        };

	protected:
	private:
        OpusEncoder *encoder;
        OpusDecoder *decoder;
};
}
}

#endif /* !ENCODING_HPP_ */