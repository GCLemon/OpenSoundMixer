
#pragma once

#include "OpenSoundMixer.h"
#include "OpenSoundMixerInternal.h"

#include "osm.Decorder.h"
#include "osm.ReferenceObject.h"

namespace osm
{
	class Sound_Impl
		: public Sound
		, public ReferenceObject
	{
	private:
		bool						m_isDecompressed;
		std::vector<Sample>			m_samples;

		std::vector<uint8_t>		m_data;
		std::shared_ptr<Decorder>	m_decorder;
	
		float						m_loopStart;
		float						m_loopEnd;

	public:
		Sound_Impl();
		virtual ~Sound_Impl();

		bool Load(void* data, int32_t size, bool isDecompressed);
		int32_t GetSamples(Sample* samples, int32_t offset, int32_t count);
		int32_t GetSampleCount();

		void SetLoopPoint(float loopStart, float loopEnd) override;

		float GetLength() override;

		float GetLoopStart() { return m_loopStart; }
		float GetLoopEnd() { return m_loopEnd; }

		// IReference���p�������f�o�C�X�I�u�W�F�N�g������`
#if !SWIG
	public:
		virtual int GetRef() { return ReferenceObject::GetRef(); }
		virtual int AddRef() { return ReferenceObject::AddRef(); }
		virtual int Release() { return ReferenceObject::Release(); }
#endif
	};
}
