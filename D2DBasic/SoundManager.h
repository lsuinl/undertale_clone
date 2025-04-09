#pragma once

#ifdef _WIN64
#include "fmod.hpp"
#pragma comment (lib, "fmod_vc.lib")
using namespace FMOD;
#endif

    enum class eSoundChannel
    {
        BGM,
        Effect,
        typing,
        Size
    };

    enum class eSoundList
    {
        Title,
        Story,
        Battle,
        snowMap,
        Ending,
        GameOver,
        //이펙트,
        BattleStart,
        TitleEffect,
        click,
        Attack,
        Death,
        //타이핑사운드
        typeing,
        Size
    };
    class SoundManager;

    class SoundManager final
    {
    public:
        static SoundManager* GetInstance();
        static void DestroyInstance();

        void LoadMusic(eSoundList list, bool loopcheck, const char* music);

        void PlayMusic(eSoundList list, eSoundChannel channel);
        void StopMusic(eSoundChannel channel);

        void SetVolume(float volume, int channel = 1);

    private:
        SoundManager();
        ~SoundManager();

    private:
        static SoundManager* mInstance;

        FMOD::System* mSystem;
        FMOD::Channel* mChannel[static_cast<int>(eSoundChannel::Size)];
        FMOD::Sound* mSoundList[static_cast<int>(eSoundList::Size)];
        float mVolume;
    };