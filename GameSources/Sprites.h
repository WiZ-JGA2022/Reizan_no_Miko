/*!
@file Sprites.h
@brief �X�v���C�g�̐e�N���X�̎���
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Sprites : public GameObject {
		enum class FadeType {
			None,
			FadeOut,
			FadeIn
		};
		enum FadeType m_fadeType = FadeType::None;

		Vec2 m_spriteSize;

		float m_tutorialUiSize = 0.0f;
		float m_TotalTime;

		bool m_Trace;
		bool m_selected;
		bool m_changeSize;

		enum class TutorialState
		{
			Wait,		// �ҋ@
			Stop,		// ���s
			SizeChange	// ���s�x��
		};
		enum TutorialState m_isState = TutorialState::Wait;

		float m_fadeCount;
		bool m_fade;
		float m_fadeSpeed;
		bool m_fadeIn;
		bool m_fadeOut;

		// �X�v���C�g�̌��ɂȂ钸�_�f�[�^�ƒ��_�C���f�b�N�X
		vector<VertexPositionColorTexture> m_vertices;
		vector<uint16_t> m_indices;

		// �h���[�R���|�[�l���g�ƃg�����X�t�H�[���R���|�[�l���g���擾
		shared_ptr<PCTSpriteDraw> m_draw;
		shared_ptr<Transform> m_transform;

	public:
		Sprites(const shared_ptr<Stage>& stage);
		~Sprites();

		void OnCreate() override;
		void OnUpdate() override;

		void CreateSprite(const Vec3 position, const Vec2 size, const wstring texKey, bool Trace, bool changeSize);
		void CreateSprite(const Vec3 position, const Vec2 size, const wstring texKey, bool Trace, bool fade, int fadeType);
	};
}