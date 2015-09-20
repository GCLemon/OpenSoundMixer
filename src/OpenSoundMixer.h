
#pragma once

#include <stdio.h>
#include <stdint.h>

namespace osm
{
	struct Sample
	{
		int16_t	Left;
		int16_t	Right;
	};

	/**
	@brief	�Q�ƃJ�E���^�̃C���^�[�t�F�[�X
	*/
	class IReference
	{
	public:
		/**
		@brief	�Q�ƃJ�E���^�����Z����B
		@return	���Z��̎Q�ƃJ�E���^
		*/
		virtual int AddRef() = 0;

		/**
		@brief	�Q�ƃJ�E���^���擾����B
		@return	�Q�ƃJ�E���^
		*/
		virtual int GetRef() = 0;

		/**
		@brief	�Q�ƃJ�E���^�����Z����B0�ɂȂ������A�C���X�^���X���폜����B
		@return	���Z��̎Q�ƃJ�E���^
		*/
		virtual int Release() = 0;
	};

	class Sound
		: public IReference
	{
	protected:
		Sound() {}
		virtual ~Sound() {}
	public:

		virtual float GetLoopStartingPoint() const = 0;

		virtual void SetLoopStartingPoint(float startingPoint) = 0;

		virtual float GetLoopEndPoint() const = 0;

		virtual void SetLoopEndPoint(float endPoint) = 0;

		virtual bool GetIsLoopingMode() const = 0;

		virtual void SetIsLoopingMode(bool isLoopingMode) = 0;

		virtual float GetLength() const = 0;

		virtual bool GetIsPlaybackSpeedEnabled() const = 0;

		virtual void SetIsPlaybackSpeedEnabled(bool isPlaybackSpeedEnabled) = 0;

		virtual float GetPlaybackSpeed() const = 0;

		virtual void SetPlaybackSpeed(float playbackSpeed) = 0;

		virtual float GetPanningPosition() const = 0;

		virtual void SetPanningPosition(float panningPosition) = 0;
	};

	class Manager
		: public IReference
	{
	protected:
		Manager(){}
		~Manager(){}
	public:

		virtual bool Initialize() = 0;

		virtual void Finalize() = 0;

		virtual Sound* CreateSound(void* data, int32_t size, bool isDecompressed) = 0;

		virtual int32_t Play(Sound* sound) = 0;

		virtual bool IsPlaying(int32_t id) = 0;

		virtual void StopAll() = 0;

		virtual void Stop(int32_t id) = 0;

		virtual void Pause(int32_t id) = 0;

		virtual void Resume(int32_t id) = 0;

		virtual void SetVolume(int32_t id, float volume) = 0;

		virtual void FadeIn(int32_t id, float second) = 0;

		virtual void FadeOut(int32_t id, float second) = 0;

		/**
			@brief	�C�ӂ̉��ʂɉ��ʂ���莞�Ԃ����ĕύX����B
			@param	id		����ID
			@param	second	�ύX�ɂ����鎞��(�b)
			@param	targetedVolume	�ύX��̉���(0.0�`1.0)
			@note
			���̎w�肳��鉹�ʂ�SetVolume�Ɏw�肳��鉹�ʂƂ͈قȂ�AFadeIn�AFadeOut�Ɏg�p����鉹�ʂƋ��ʂł���B
			�܂�A���̃��\�b�h��FadeIn�AFadeOut�̔C�Ӊ��ʎw��łƌ�����B
		*/
		virtual void Fade(int32_t id, float second, float targetedVolume) = 0;

		static Manager* Create();
	};
}
