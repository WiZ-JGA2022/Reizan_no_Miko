/*!
@file Sprites.h
@brief �X�v���C�g�̐e�N���X�̎���
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Sprites : public GameObject {
		Vec2 m_spriteSize;	// �傫��
		Vec2 m_afterSize;	// �T�C�Y�ύX��̑傫��
		Vec3 m_position;	// UI�̈ʒu

		float m_uiSizeCoefficient;	// UI�T�C�Y�̌W��
		float m_totalTime;			// ����
		float m_waitSecond;			// �T�C�Y�ω��܂ł̑ҋ@����

		float m_alphaNum;	// �����x
		float m_fadeSpeed;	// �t�F�[�h�̑��x

		// �X�v���C�g�̌��ɂȂ钸�_�f�[�^�ƒ��_�C���f�b�N�X
		vector<VertexPositionColorTexture> m_vertices;
		vector<uint16_t> m_indices;

		// �h���[�R���|�[�l���g�ƃg�����X�t�H�[���R���|�[�l���g���擾
		shared_ptr<PCTSpriteDraw> m_draw;
		shared_ptr<Transform> m_transform;

	protected :
		enum class SpriteType {
			Normal,			// �ʏ�
			ChangeColor,	// �F���ς��
			SeekSize,		// �T�C�Y���ς��
			Fade			// �t�F�[�h����
		};

		enum class FadeType {
			None,		// �������Ȃ�
			FadeOut,	// �t�F�[�h�A�E�g
			FadeIn		// �t�F�[�h�C��
		};

		enum class SeekSizeState
		{
			Wait,		// �ҋ@
			Stop,		// �I��
			SizeChange	// ���s
		};
		enum class SeekType {
			UpperLeft,	// ����
			GameSprite,	// �E��ɓ����Ȃ���k��
			BottomLeft,	// ����
			BottomRight	// �E��
		};

		enum class ChangeColorState {
			Wait,		// �ҋ@
			ChangeColor	// ���s
		};

		enum SpriteType m_spriteType = SpriteType::Normal; // �X�v���C�g�^�C�v
		enum FadeType m_fadeType = FadeType::None; // �t�F�[�h�^�C�v
		enum SeekSizeState m_isSeekSizeState = SeekSizeState::Wait; // �T�C�Y�ύX�̏��
		enum SeekType m_seekType = SeekType::BottomRight; // �ω��������
		enum ChangeColorState m_isChangeColorState = ChangeColorState::Wait; // �F�ύX�̏��

	public:
		Sprites(const shared_ptr<Stage>& stage);
		~Sprites();

		void OnCreate() override;
		void OnUpdate() override;

		/**
		* �X�v���C�g���쐬����֐�
		* 
		* @param position	�\���ʒu
		* @param size		�\���T�C�Y
		* @param texKey		�g�p�e�N�X�`��
		*/
		void CreateSprite(const Vec3& position, const Vec2& size, const wstring& texKey);

		/**
		* �F���ς��X�v���C�g���쐬����֐�
		*
		* @param position	�\���ʒu
		* @param size		�\���T�C�Y
		* @param texKey		�g�p�e�N�X�`��
		*/		
		void CreateColorChangeSprite(const Vec3& position, const Vec2& size, const wstring& texKey);

		/**
		* �T�C�Y���ς��X�v���C�g���쐬����֐�
		*
		* @param position	�\���ʒu
		* @param beforeSize �����\���T�C�Y
		* @param afterSize	�ύX��\���T�C�Y
		* @param texKey		�g�p�e�N�X�`��
		* @param seekType	�T�C�Y�ύX�^�C�v
		* @param waitSecond �T�C�Y�ύX�܂ł̑ҋ@����
		*/
		void CreateSeekSizeSprite(const Vec3& position, const Vec2& beforeSize, const Vec2& afterSize, const wstring& texKey, const SeekType& seekType, const float waitSecond);

		/**
		* �t�F�[�h����X�v���C�g���쐬����֐�
		*
		* @param position	�\���ʒu
		* @param size		�\���T�C�Y
		* @param texKey		�g�p�e�N�X�`��
		* @param fadeType	�t�F�[�h�^�C�v
		*/
		void CreateFadeSprite(const Vec3& position, const Vec2& size, const wstring& texKey, const FadeType& fadeType);
	};
}