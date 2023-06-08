/* !
@file TutorialUI.h
@brief �`���[�g���A��UI�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//�R���X�g���N�^�ƃf�X�g���N�^
	TutorialUI::TutorialUI(const shared_ptr<Stage>& stage
	) :
		Sprites(stage),
		m_DefaultSize(Vec2(250.0f, 200.0f)),
		m_AfterSize(Vec2(0.0f, 0.0f))
	{
	}
	//�I��

	// ������
	void TutorialUI::OnCreate()
	{
		Sprites::CreateSprite(Vec3(350.0f, 0.0f, 0.0f), m_DefaultSize, L"TUTORIAL");	//�ʒu���W�A�����T�C�Y�A�\�[�X�摜
	}

	//�X�V����
	void TutorialUI::OnUpdate()
	{
		Sprites::UpdateSeekSizeSprite(m_AfterSize, 0.5f, SeekType::BottomRight, 5.0f);	//�ύX��̃T�C�Y�A�ύX���ԁA�V�[�N�^�C�v�̏�ԁA�ҋ@����
	}
}
