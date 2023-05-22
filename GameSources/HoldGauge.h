/* !
*
@file ExpBar.h
@brief �o���l��\������o�[
*
*/

#pragma once
#include "stdafx.h"
#include "GaugeSizeSetting.h"

namespace basecross {

	class HoldBar : public GameObject
	{
		int m_maxTime; // �ő�o���l

		// EXP�o�[�̏�������ϐ�
		shared_ptr<GaugeSizeSettings> m_bar[2];

	public:
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

