/* !
@file TrapUI.h
@brief �g���b�vUI�̎���
*/

#include "stdafx.h"
#include <random>
#include "time.h"
#include "Project.h"

namespace basecross {

	constexpr float m_startScaleZ = 1.0f;// �傫��
	constexpr float m_startPosZ = 1.0f;	 // ���s��
	constexpr float m_helfSize = 0.5f;	 // �����̑傫��

	//�R���X�g���N�^�ƃf�X�g���N�^
	TrapSprite::TrapSprite(const shared_ptr<Stage>& stage,
		const int& textureNum,
		bool trace,
		const Vec2& startScale,
		const Vec2& startPos,
		const int& texNum
	) :
		GameObject(stage),
		m_textureNum(textureNum),
		m_alpha(trace),
		m_defaultScale(startScale),
		m_defaultPos(startPos),
		m_texNum(texNum)
	{
	}
	//�I��

	//�A���ŕ\��������摜�̎擾
	wstring TrapSprite::ControllerNum(int i) {
		if (i == 0)
		{
			m_textureKey = L"TRAP_1";
			return m_textureKey;
		}
		else if (i == 1)
		{
			m_textureKey = L"TRAP_2";
			return m_textureKey;

		}
		else if (i == 2)
		{
			m_textureKey = L"TRAP";
			return m_textureKey;

		}
		else if (i == 3)
		{
			m_textureKey = L"TRAP";
			return m_textureKey;

		}
	}

	// ������
	void TrapSprite::OnCreate()
	{
		float HelfSize = m_helfSize;

		// ���_�z��
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-HelfSize, HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-HelfSize,-HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize,-HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 1.0f)) },
		};

		// �C���f�b�N�X�z��
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_alpha);
		auto PtrTransform = GetComponent<Transform>();
		PtrTransform->SetScale(m_defaultScale.x, m_defaultScale.y, m_startScaleZ);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetPosition(m_defaultPos.x, m_defaultPos.y, m_startPosZ);

		std::wstring Key;
		Key = ControllerNum(m_textureNum);

		// ���_�ƃC���f�b�N�X���w�肵�ăX�v���C�g�쐬
		auto PtrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		PtrDraw->SetSamplerState(SamplerState::LinearWrap);
		PtrDraw->SetTextureResource(Key);
		PtrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, m_alphaNum));
		SetDrawActive(true);
	} // end OnCreate

	// �X�V����
	void TrapSprite::OnUpdate() {
		auto& app = App::GetApp();
		auto stage = app->GetScene<Scene>()->GetActiveStage();	// �X�e�[�W�I�u�W�F�N�g���擾����
		auto objs = stage->GetGameObjectVec();					// �X�e�[�W�ɒǉ�����Ă��邷�ׂẴI�u�W�F�N�g
		auto scene = App::GetApp()->GetScene<Scene>();
		auto player = GetStage()->GetSharedGameObject<PlayerController>(L"Player");

		if (player->GetCondition() == 1) {
			// �����I����ɕ\�������摜����������

			GetStage()->RemoveGameObject<TrapSprite>(GetThis<TrapSprite>());
		}
	} // end OnUpdate
}