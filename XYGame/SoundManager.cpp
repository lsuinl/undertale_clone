#include "XYSystem.h"

namespace Music
{
    SoundManager* SoundManager::mInstance = nullptr;
    SoundManager* soundManager = SoundManager::GetInstance();

    SoundManager* SoundManager::GetInstance()
    {
        if (mInstance == nullptr)
        {
            mInstance = new SoundManager();
        }

        return mInstance;
    }

    void SoundManager::DestroyInstance()
    {
        delete mInstance;
        mInstance = nullptr;
    }

    void SoundManager::LoadMusic(eSoundList soundlist, bool loopcheck, const char* music)
    {
        if (loopcheck)
        {
            mSystem->createSound(music, FMOD_LOOP_NORMAL, 0, &mSoundList[static_cast<int>(soundlist)]);
        }
        else
        {
            mSystem->createSound(music, FMOD_LOOP_OFF, 0, &mSoundList[static_cast<int>(soundlist)]);
        }

    }

    void SoundManager::PlayMusic(eSoundList soundlist, eSoundChannel channel)
    {
        mChannel[static_cast<int>(channel)]->stop();
        mSystem->playSound(mSoundList[static_cast<int>(soundlist)], NULL, 0, &mChannel[static_cast<int>(channel)]);
        mChannel[static_cast<int>(channel)]->setVolume(mVolume);
    }

    void SoundManager::StopMusic(eSoundChannel channel)
    {
        mChannel[static_cast<int>(channel)]->stop();
    }

    void SoundManager::SetVolume(float volume, int channel)
    {
        mVolume = volume;
        for (unsigned int i = 0; i < static_cast<unsigned int>(eSoundChannel::Size); ++i)
        {
            mChannel[channel]->setVolume(mVolume);
        }
    }

    SoundManager::SoundManager()
        : mSystem()
        , mChannel{}
        , mSoundList{}
        , mVolume(0.5f)
    {
        System_Create(&mSystem);
        mSystem->init(3, FMOD_INIT_NORMAL, 0);
    }

    SoundManager::~SoundManager()
    {
        mSystem->release();
        mSystem->close();
    }
};