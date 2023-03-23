/*!
@file GameStage.cpp
@brief �Q�[���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	void GameStage::CreateViewLight() {
		const Vec3 eye(0.0f, 5.0f, -5.0f);
		const Vec3 at(0.0f, 1.0f ,0.0f);

		auto PtrView = CreateView<SingleView>();
		
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);

		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();
	}



	void GameStage::OnCreate() {
		try {

			auto player = AddGameObject<PlayerController>();
			auto playerK = AddGameObject<Player>();
			AddGameObject<EnemyController>(playerK);


			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();

			// Exp�o�[��Hp�o�[�̍쐬
			AddGameObject<ExpBar>();
			AddGameObject<HpBar>();

			// �n�ʂ̍쐬
			AddGameObject<Field>();

			// ���C���J�����Ƀv���C���[���Z�b�g����
			auto camera = GetView()->GetTargetCamera();
			auto maincamera = dynamic_pointer_cast<MainCamera>(camera);
			if (maincamera) // �G���[�`�F�b�N
			{
				maincamera->SetTarget(player);
			}

		}
		catch (...) {
			throw;
		}
	}

}
//end basecross
