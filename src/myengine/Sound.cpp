#include "Sound.h"
#include "Core.h"

#include <rend/rend.h>

#include <iostream>
#include <fstream>

#include "stb_vorbis.h"

namespace myengine
{

void Sound::onLoad()
{
	alGenBuffers(1, &id);

	ALenum format = 0;
	ALsizei freq = 0;
	std::vector<char> bufferData;
	loadOgg(getPath() + ".ogg", bufferData, format, freq);

	alBufferData(id, format, &bufferData.at(0), static_cast<ALsizei>(bufferData.size()), freq);
}

void Sound::loadOgg(const std::string& filename, std::vector<char>& buffer, ALenum& format, ALsizei& freq)
{
	int channels = 0;
	int sampleRate = 0;
	short* output = NULL;
	size_t samples = stb_vorbis_decode_filename(filename.c_str(), &channels, &sampleRate, &output);

	if (samples == -1)
	{
		throw Exception("Failed to open file " + filename);
	}

	// Record the format required by OpenAL
	if (channels == 1)
	{
		format = AL_FORMAT_MONO16;
	}
	else
	{
		format = AL_FORMAT_STEREO16;
	}

	freq = sampleRate;

	buffer.resize(samples * 2);
	memcpy(&buffer.at(0), output, buffer.size());

	// Clean up the read data
	free(output);
}

}
