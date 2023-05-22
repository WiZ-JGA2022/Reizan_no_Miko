/**
@file TimeNumber.cpp
@brief ��������UI�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	TimeNumber::TimeNumber(const shared_ptr<Stage>& stage, const float totalTime, const bool isPlay, const bool skipFlag) :
		GameObject(stage),
		m_NumberSize(Vec2(24.0f, 48.0f)),
		m_OneMinite(60),
		m_place(5),
		m_totalTime(totalTime),
		m_minutes(0),
		m_seconds(0),
		m_oldSeconds(0),
		m_isPlay(isPlay),
		m_skipFlag(skipFlag),
		m_timeSkip(0)
	
	{
	}
	TimeNumber::~TimeNumber() {}

	void TimeNumber::OnCreate()
	{
		m_numbers.reserve(m_place);

		for (int i = 0; i < m_place; i++)
		{
			auto numberObj = ObjectFactory::Create<NumberUI>(GetStage(), m_NumberSize, L"TIME_NUMBER"); // �I�u�W�F�N�g�𐶐����邯�ǃX�e�[�W�ɒǉ����Ȃ�
			numberObj->SetPosition(Vec2(680.0f - m_NumberSize.x * i, 0.0f), 0.47f);
			m_numbers.push_back(numberObj);
		}
	}

	void TimeNumber::OnUpdate()
	{
		auto player = GetStage()->GetSharedGameObject<PlayerController>(L"Player");

		// ���x���A�b�v�C�x���g���s���܂��̓v���C���[�����Ȃ��Ƃ�
		if (!player->GetDrawActive())
		{
			// �������~����
			return;
		}

		// ���Ԃ̍X�V
		auto& app = App::GetApp();
		auto delta = app->GetElapsedTime();

		auto device = app->GetInputDevice(); // �C���v�b�g�f�o�C�X�I�u�W�F�N�g���擾����
		auto& pad = device.GetControlerVec()[0]; // �P�ڂ̃R���g���[���[�̏�Ԃ��擾����

		m_totalTime -= delta;

		m_minutes = (int)m_totalTime / m_OneMinite;
		m_seconds = m_totalTime - m_minutes * m_OneMinite;

		if ((int)m_seconds != (int)m_oldSeconds)
		{
			UpdateValue(m_minutes, m_seconds);
		}
		m_oldSeconds = m_seconds;

		if (m_isPlay)
		{
			// ���Ԑ؂�ɂȂ�����
			if (m_totalTime <= 1 && player->GetCondition() == 1)
			{
				// �N���A
				PostEvent(1.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToClearStage");
				return;
			}
		}

		//RB�{�^���𒷉���������X�L�b�v
		if (pad.wButtons & BUTTON_TIMESKIP && m_skipFlag)
		{
			m_timeSkip += delta;
			if (m_timeSkip > 3) {
				dynamic_pointer_cast<StandbyStage>(GetStage())->ChangeStage();
			}
		}

	}

	void TimeNumber::OnDraw()
	{
		for (auto& number : m_numbers)
		{
			number->OnDraw();
		}
	}

	void TimeNumber::UpdateValue(int minites, float seconds)
	{
		int place = 1;
		for (auto& numberObj : m_numbers)
		{
			int secondsNumber = (int)seconds / place % 10; // 1���ڂ���\��
			int minitesNumber = minites * 1000 / place % 10; // 4���ڈȍ~����\��
			int coron = 10;
			if (place == 100)
			{
				numberObj->SetNumber(coron); // 3���ڂɃR������\��
			}
			else
			{
				numberObj->SetNumber(secondsNumber + minitesNumber); // ���݂̌����\�����l�����Ƀi���o�[�I�u�W�F�N�g�̕\�����e��ݒ肷��
			}

			place *= 10; // �������炷
		}
	}

	float TimeNumber::GetTimeLeft()
	{
		return m_totalTime;
	}
}
