/*!
@file CrossKey.cpp
@brief �\���L�[��UI
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	constexpr float m_startScaleZ = 1.0f;// �傫��
	constexpr float m_startPosZ = 1.0f;	 // ���s��
	constexpr float m_helfSize = 0.5f;	 // �����̑傫��
	//--------------------------------------------------------------------------------------
	///	�R���g���[���[�{�^���̃X�v���C�g
	//--------------------------------------------------------------------------------------
	CrossKeySprites::CrossKeySprites(const shared_ptr<Stage>& StagePtr,
		const int& TextureNum,
		bool Trace,
		const Vec2& StartScale,
		const Vec2& StartPos,
		const int& TexNum
	) :
		GameObject(StagePtr),
		m_textureNum(TextureNum),
		m_alpha(Trace),
		m_defaultScale(StartScale),
		m_defaultPos(StartPos),
		m_texNum(TexNum)
	{}

	wstring CrossKeySprites::ControllerNum(int i) {
		if (i == 0)
		{
			m_textureKey = L"CROSSKEY_UP";
			return m_textureKey;
		}
		else if (i == 1)
		{
			m_textureKey = L"CROSSKEY_RIGHT";
			return m_textureKey;

		}
		else if (i == 2)
		{
			m_textureKey = L"CROSSKEY_DOWN";
			return m_textureKey;
		}
		else
		{

		}

	} // end ControllerNum

	// ������
	void CrossKeySprites::OnCreate()
	{
		float HelfSize = m_helfSize;

		// ���_�z��(�c��5���\��)
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
		PtrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 1.0f));
		SetDrawActive(true);

	} // end OnCreate

	// �X�V����
	void CrossKeySprites::OnUpdate() {
		auto& app = App::GetApp();
		auto stage = app->GetScene<Scene>()->GetActiveStage();	// �X�e�[�W�I�u�W�F�N�g���擾����
		auto objs = stage->GetGameObjectVec();					// �X�e�[�W�ɒǉ�����Ă��邷�ׂẴI�u�W�F�N�g

		// �����I����ɕ\�������摜����������
		for (auto& obj : objs)
		{
			// LevelUpButton�ւ̃L���X�g�����݂�
			auto levelUpButton = dynamic_pointer_cast<RandomSelectLevelUpButton>(obj);
			if (levelUpButton)
			{
				auto controllerKeyFlg = levelUpButton->GetEventActive();
				if (!controllerKeyFlg) {
					GetStage()->RemoveGameObject<CrossKeySprites>(GetThis<CrossKeySprites>());
				}
			}
		}
	} // end OnUpdate
}
