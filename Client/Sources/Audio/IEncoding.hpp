/*
** EPITECH PROJECT, 2019
** cpp_babel_2019
** File description:
** IEncoding
*/

#ifndef IENCODING_HPP_
#define IENCODING_HPP_

namespace Babel {
namespace audio {
class IEncoding {
	public:
		IEncoding() = default;
		~IEncoding() = default;

        virtual void encode_create(int Fs, int channels, int application, int *err) = 0;
        virtual int encode_float(const float * pcm, int frame_size, unsigned char * data, int max_data_bytes) = 0;

        virtual void decode_create(int Fs, int channels, int *err) = 0;
        virtual int decode_float(const unsigned char *data, int len, float *pcm, int frame_size, int decode_fec) = 0;

	protected:
	private:
};
}
}

#endif /* !IENCODING_HPP_ */