/* !
@file HpBar.h
@brief �v���C���[�̗̑͂�\������o�[
*/

#pragma once
#include "stdafx.h"
#include "GaugeSizeSetting.h"
#include <vector>

namespace basecross {

	class HpBar : public GameObject
	{
		// HP�o�[�̏�������ϐ�
		shared_ptr<GaugeSizeSettings> m_bar;

	public:
		HpBar(const std::shared_ptr<Stage>& stage) :
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

