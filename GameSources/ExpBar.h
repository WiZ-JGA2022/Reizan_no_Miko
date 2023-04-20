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
	
	class ExpBar : public GameObject
	{
		int m_maxExp; // �ő�o���l

		// EXP�o�[�̏�������ϐ�
		shared_ptr<GaugeSizeSettings> m_bar[2];

	public:
		ExpBar(const std::shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_maxExp(0)
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
