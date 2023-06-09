/*!
@file RightStick.h
@brief 耐久値スプライト
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	class RightStick : public Sprites {
		const Vec2 m_DefaultSize; // 初期サイズ

		wstring m_texKey; // テクスチャ名

	public:
		// コンストラクタ
		RightStick(const shared_ptr<Stage>& stage);
		// デストラクタ
		~RightStick();

		void OnCreate() override; // 初期化 
	};
}
