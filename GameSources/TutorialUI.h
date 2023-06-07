/* !
@file TrapUI.h
@brief �g���b�vUI
*/

#pragma once
#include "stdafx.h"
#include "Sprites.h"

namespace basecross {

	class TutorialUI : public Sprites {
		const Vec2 m_DefaultSize; //�����T�C�Y
		const Vec2 m_AfterSize; // �ύX��̃T�C�Y
	public:
		//�R���X�g���N�^
		TutorialUI(const shared_ptr<Stage>& stagePtr);
		//�f�X�g���N�^
		virtual ~TutorialUI() {}

		//������
		void OnCreate() override;
		//�X�V����
		void OnUpdate() override;
	};
}
//end basecross
