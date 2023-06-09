/*!
@file EnemyController.h
@brief �G�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class EnemySpawn :public GameObject
	{
		Vec3 m_enemyInterval;//�G�̏o���Ԋu

	public:
		EnemySpawn(const shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_enemyInterval(5.0f,0.0f,5.0f)
		{
		}

		//�o���p�^�[��
		/**
		* �G��1�̐����ʒu�����߂�֐�
		*
		* @param pos �����ʒu
		*/
		void Spawn1(Vec3 pos);

		/**
		* �G��2�̐����ʒu�����߂�֐�
		*
		* @param pos �����ʒu
		*
		*/
		void Spawn2(Vec3 pos);//2��

		/**
		* �G��3�̐����ʒu�����߂�֐�
		*
		* @param pos �����ʒu
		*/
		void Spawn3(Vec3 pos);

		/**
		* �G��4�̐�������֐�
		*
		* @param pos �����ʒu
		*/
		void Spawn4(Vec3 pos);

		/**
		* �G��5�̐����ʒu�����߂�֐�
		*
		* @param pos �����ʒu
		*/
		void Spawn5(Vec3 pos);

		/**
		* �G��6�̐����ʒu�����߂�֐�
		*
		* @param pos �����ʒu
		*/
		void Spawn6(Vec3 pos);

		/**
		* �G�𐶐�����֐�
		*
		* @param pos �����ʒu
		*/
		void EnemyCreate(Vec3 transPos);
	};

}