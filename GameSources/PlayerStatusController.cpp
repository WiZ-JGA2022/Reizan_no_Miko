/*!
@file PlayerStatusController.cpp
@brief �v���C���[�̃X�e�[�^�X���Ǘ�����N���X�̎���
@prod ��I�t
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	PlayerStatusController::PlayerStatusController(const std::shared_ptr<Stage>& stage) :
		GameObject(stage)
	{
	}
	PlayerStatusController::~PlayerStatusController() {}

	void PlayerStatusController::OnCreate()
	{
		//�G�t�F�N�g�̏�����
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		wstring TestEffectStr = DataDir + L"Effects\\" + L"damage.efk";
		auto& app = App::GetApp();
		auto scene = app->GetScene<Scene>();
		auto ShEfkInterface = scene->GetEfkInterface();
		m_EfkEffect = ObjectFactory::Create<EfkEffect>(ShEfkInterface, TestEffectStr);
	}

	void PlayerStatusController::OnUpdate()
	{
		auto player = GetStage()->GetSharedGameObject<PlayerController>(L"Player");
		// �v���C���[�����Ȃ�������
		if (!player->GetDrawActive())
		{
			// �������~����
			return;
		}
	}

	// �G����󂯂�_���[�W�̏���
	void PlayerStatusController::PlayerDamageProcess(float damage)
	{
		// �h��͂̌y����ǉ������_���[�W�ʂ̌v�Z
		float totalDamage = damage - (damage * (m_statusValue[L"DEF"] - 1.0f));
		// �_���[�W�������̗̑͂����炷
		m_statusValue[L"HP"] -= totalDamage;

		// SE�̍Đ�
		auto& XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Start(L"PLAYERDAMAGE_SE", 0, 0.3f);

		//�G�t�F�N�g�̃v���C
		auto player = GetStage()->GetSharedGameObject<PlayerController>(L"Player");
		m_EfkPlay = ObjectFactory::Create<EfkPlay>(m_EfkEffect, player->GetComponent<Transform>()->GetPosition(), Vec3(1.0f));
	} // end PlayerTakenDamage
}
