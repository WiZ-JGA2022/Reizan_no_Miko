/* !
@file KeyStoneHpGauge.h
@brief �v�΂̗̑͂�\������o�[
@prod ��I�t
*/

#pragma once
#include "stdafx.h"
#include "GaugeSizeSetting.h"
#include <vector>

namespace basecross {

	class HpBar : public GameObject
	{
		// �ő�HP
		float m_maxHP;

		// HP�o�[�̏�������ϐ�
		shared_ptr<GaugeSizeSettings> m_bar[2];
	public:
		// �R���X�g���N�^
		HpBar(const std::shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_maxHP(0)
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

