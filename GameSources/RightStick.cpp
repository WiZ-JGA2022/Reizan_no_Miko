/* !
@file RightStick.cpp
@brief 耐久値スプライト
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	// コンストラクタ
	RightStick::RightStick(const shared_ptr<Stage>& stage) :
		Sprites(stage),
		m_DefaultSize(Vec2(200.0f, 200.0f))
	{
	}
	// デストラクタ
	RightStick::~RightStick() {}

	// 初期化
	void RightStick::OnCreate()
	{
		auto scene = App::GetApp()->GetScene<Scene>();
		if (scene->GetBeforePlacedTrap(1) > 0)
		{
			Sprites::CreateSprite(Vec3(-600.0f, -200.0f, 0.0f), m_DefaultSize, L"RIGHT_STICK");
		}
	}

	void RightStick::OnUpdate()
	{
		// コントローラーデバイスの取得
		auto& app = App::GetApp();
		auto device = app->GetInputDevice();
		auto& pad = device.GetControlerVec()[0];

		// Rスティックが押されたら
		if (pad.wPressedButtons & XINPUT_GAMEPAD_RIGHT_THUMB)
		{
			// このオブジェクトを消す
			GetStage()->RemoveGameObject<RightStick>(GetThis<RightStick>());
		}
	}
}