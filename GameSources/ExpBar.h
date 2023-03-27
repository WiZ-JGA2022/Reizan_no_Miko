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
		// EXP�o�[�̏�������ϐ�
		shared_ptr<GaugeSizeSettings> m_bar;

	public:
		ExpBar(const std::shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}

		// ������ //
		void OnCreate() override;
		// �X�V���� //
		void OnUpdate() override;
		// �`�揈�� //
		void OnDraw() override;
	};
}
//end basecross
