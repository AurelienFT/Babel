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

class Encoding : public IEncoding {
	public:
		Encoding() = default;
		~Encoding() = default;

        void encode_create(int Fs, int channels, int application, int *err)
        {
            encoder = opus_encoder_create(Fs, channels, application, err);
        };
        int encode_float(const float * pcm, int frame_size, unsigned char * data, int max_data_bytes)
        {
            return opus_encode_float(encoder, pcm, frame_size, data, max_data_bytes);
        };
        
        void decode_create(int Fs, int channels, int *err)
        {
            decoder = opus_decoder_create(Fs, channels, err);
        };
        int decode_float(const unsigned char *data, int len, float *pcm, int frame_size, int decode_fec)
        {
            return opus_decode_float(decoder, data, len, pcm, frame_size, decode_fec);
        };

	protected:
	private:
        OpusEncoder *encoder;
        OpusDecoder *decoder;
};

#endif /* !ENCODING_HPP_ */