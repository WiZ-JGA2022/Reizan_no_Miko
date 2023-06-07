/**
* @file HoldGauge.h
* @brief �X�L�b�v�{�^�����������ɑ�����Q�[�W
*/

#pragma once
#include "stdafx.h"
#include "GaugeSizeSetting.h"

namespace basecross {

	class HoldBar : public GameObject
	{
		int m_maxTime; // �ő厞��

		shared_ptr<GaugeSizeSettings> m_bar[2];// �o�[�̏�������ϐ�

	public:
		// �R���X�g���N�^
		HoldBar(const std::shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_maxTime(3)
		{
		}

		// ������
		void OnCreate() override;
		// �X�V����
		void OnUpdate() override;
		// �`�揈��
		void OnDraw() override;
	};
}
//end basecross

