#include "Resource.h"
#include "Exception.h"
#include "Al/al.h"

#include <rend/rend.h>

#include <string>
#include <memory>

#include "Component.h"

namespace myengine
{

struct Sound : public Resource
{
	ALuint id;

	void onLoad();
	void loadOgg();
	void loadOgg(const std::string& filename, std::vector<char> &buffer, ALenum &format, ALsizei &freq);
};

struct AudioSource : Component
{
	ALuint sid;

	void onInitialize(std::shared_ptr<Sound> _sound)
	{
		alGenSources(1, &sid);

		alSourcei(sid, AL_BUFFER, _sound->id);
		alSourcePlay(sid);
	}

	void onTick()
	{
		ALint state = 0;

		alGetSourcei(sid, AL_SOURCE_STATE, &state);

		if (state == AL_STOPPED)
		{
			// destroy
			onDestroy();
		}
	}

	void onDestroy()
	{
		alDeleteSources(1, &sid);
	}
};
}

