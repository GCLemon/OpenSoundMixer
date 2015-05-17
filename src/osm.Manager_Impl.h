
#pragma once

#include "OpenSoundMixer.h"
#include "OpenSoundMixerInternal.h"
#include "osm.ReferenceObject.h"

#include <mutex>
#include <map>
#include <vector>
#include <float.h>

namespace osm
{
	class Sound_Impl;

	class Manager_Impl
		: public Manager
		, public ReferenceObject
	{
	private:

		struct SoundState
		{
			int32_t			SamplePos;
			Sound_Impl*		SoundPtr;
			bool			IsPaused;
			float			Volume;

			float			FadeGradient;
			float			FadeVolume;
			float			TargetedFadeVolume;
		};

		int32_t	m_stateID;
		int32_t	m_current;

		std::map<int32_t, SoundState>	m_soundStates;

		std::vector<Sample>			m_tempSamples;
		std::vector<int32_t>		m_tempIDs;

		std::recursive_mutex		m_mutex;

	protected:
		virtual bool InitializeInternal() = 0;
		virtual void FinalizeInternal() = 0;

		int32_t ReadSamples( Sample* samples, int32_t sampleCount );

		/**
		@brief	����p�̃~���[�e�b�N�X���擾����B
		@return	�~���[�e�b�N�X
		*/
		std::recursive_mutex& GetMutex(){ return m_mutex; }
	public:
		Manager_Impl();
		virtual ~Manager_Impl();

		bool Initialize() override;

		void Finalize() override;

		Sound* CreateSound(void* data, int32_t size, bool isDecompressed) override;

		int32_t Play(Sound* sound) override;
	
		bool IsPlaying(int32_t id) override;

		void StopAll() override;

		void Stop(int32_t id) override;

		void Pause(int32_t id) override;

		void Resume(int32_t id) override;

		void SetVolume(int32_t id, float volume) override;

		void FadeIn(int32_t id, float second) override;

		void FadeOut(int32_t id, float second) override;

		void Fade(int32_t id, float second, float targetedVolume) override;

		// IReference���p�������f�o�C�X�I�u�W�F�N�g������`
#if !SWIG
	public:
		virtual int GetRef() { return ReferenceObject::GetRef(); }
		virtual int AddRef() { return ReferenceObject::AddRef(); }
		virtual int Release() { return ReferenceObject::Release(); }
#endif
	};
}
