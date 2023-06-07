/*!
@file StageCollision.h
@brief 地面を表すクラスを定義する
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class StageCollision : public GameObject
	{
		Vec3 m_position; // 位置
		Vec3 m_scale; // 大きさ

	public:
		// コンストラクタ
		StageCollision(const std::shared_ptr<Stage>& stage,const Vec3& potision,const Vec3& scale);
		// デストラクタ
		~StageCollision();

		// 初期化
		void OnCreate() override;
		// 更新処理
		void OnUpdate() override;
	};
}