/* !
@file EventBackGround.h
@brief LevelUpEvent���s���̔w�i
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	EventBackGround::EventBackGround(const shared_ptr<Stage>& stage) :
		GameObject(stage)
	{
	}
	EventBackGround::~EventBackGround() {}

	void EventBackGround::OnCreate()
	{
		auto& app = App::GetApp();

		const Col4 white(1.0f, 1.0f, 1.0f, 1.0f); // �F��(�摜�t�@�C���̐F���̂܂�)��

		m_vertices = {
			{Vec3(0.0f				, 0.0f				, 0.0f), white, Vec2(0.0f, 0.0f)}, // ����
			{Vec3(m_DefaultSize.x	, 0.0f				, 0.0f), white, Vec2(1.0f, 0.0f)}, // �E��
			{Vec3(0.0f				, -m_DefaultSize.y	, 0.0f), white, Vec2(0.0f, 1.0f)}, // ����
			{Vec3(m_DefaultSize.x	, -m_DefaultSize.y	, 0.0f), white, Vec2(1.0f, 1.0f)}, // �E��
		};

		m_indices = {
			0, 1, 2,
			2, 1, 3
		};

		m_draw = AddComponent<PCTSpriteDraw>(m_vertices, m_indices);
		m_draw->SetTextureResource(L"EVENT_BACK_GROUND");

		m_transform = GetComponent<Transform>();
		m_transform->SetPosition(-m_DefaultSize.x / 2, m_DefaultSize.y / 2, 0.0f);

		// ���ߏ�����L���ɂ���
		SetAlphaActive(true);
	}

	void EventBackGround::OnUpdate()
	{
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
					GetStage()->RemoveGameObject<EventBackGround>(GetThis<EventBackGround>());
				}
			}
		}
	}
}