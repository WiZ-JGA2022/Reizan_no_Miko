/*!
@file Field.h
@brief �n�ʂ�\���N���X���`����
@prod ��I�t
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Field : public GameObject
	{
	public:
		// �R���X�g���N�^
		Field(const std::shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}

		// ������
		void OnCreate() override;
		// �X�V����
		void OnUpdate() override;
	};

	class KeyStone : public GameObject
	{
		const int m_DefaultDelay; // �_���[�W���󂯂�Ԋu
		const float m_DefaultHp = 100.0f; // ����HP
		
		float m_hp; // ����HP
		int m_delay;
		bool m_broken; // ��ꂽ���ǂ���

	public:
		// �R���X�g���N�^
		KeyStone(const std::shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_DefaultDelay(5),
			m_delay(0),
			m_hp(m_DefaultHp),
			m_broken(false)
		{
		}

		// ������
		void OnCreate() override;
		// �X�V����
		void OnUpdate() override;

		// �_���[�W����
		void DamageProcess();

		// �ő�HP���擾����
		int GetMaxHp()
		{
			return (int)m_DefaultHp;
		}
		// ���݂�HP���擾����
		float GetCurrentHp()
		{
			return m_hp;
		}
	};
}

//end basecross

