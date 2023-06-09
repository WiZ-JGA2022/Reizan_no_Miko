/*!
@file EnemyController.h
@brief 敵など
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class EnemySpawn :public GameObject
	{
		Vec3 m_enemyInterval;//敵の出現間隔

	public:
		EnemySpawn(const shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_enemyInterval(5.0f,0.0f,5.0f)
		{
		}

		//出現パターン
		/**
		* 敵を1体生成位置を求める関数
		*
		* @param pos 初期位置
		*/
		void Spawn1(Vec3 pos);

		/**
		* 敵を2体生成位置を求める関数
		*
		* @param pos 初期位置
		*
		*/
		void Spawn2(Vec3 pos);//2体

		/**
		* 敵を3体生成位置を求める関数
		*
		* @param pos 初期位置
		*/
		void Spawn3(Vec3 pos);

		/**
		* 敵を4体生成する関数
		*
		* @param pos 初期位置
		*/
		void Spawn4(Vec3 pos);

		/**
		* 敵を5体生成位置を求める関数
		*
		* @param pos 初期位置
		*/
		void Spawn5(Vec3 pos);

		/**
		* 敵を6体生成位置を求める関数
		*
		* @param pos 初期位置
		*/
		void Spawn6(Vec3 pos);

		/**
		* 敵を生成する関数
		*
		* @param pos 生成位置
		*/
		void EnemyCreate(Vec3 transPos);
	};

}