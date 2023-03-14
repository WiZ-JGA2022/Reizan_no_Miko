/*!
@file PlayerController.cpp
@brief プレイヤーキャラ
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void PlayerController::OnCreate() // UnityのStartメソッド(関数)のようなもの
	{
		// Playerオブジェクトの初期設定
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		drawComp->SetOwnShadowActive(true);

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(0.0f, 0.0f, 0.0f);
	}

	void PlayerController::OnUpdate()
	{
		// Playerの移動処理
		auto& app = App::GetApp();

		float delta = app->GetElapsedTime(); // 前フレームからの経過時間（60FPS）

		// ゲームパッドを使用する
		auto device = app->GetInputDevice(); // インプットデバイスオブジェクトを取得する
		auto& pad = device.GetControlerVec()[0]; // １個目のコントローラーの状態を取得する

		Vec3 padLStick(pad.fThumbLX, 0.0f, pad.fThumbLY);

		if (padLStick.length() > 0.0f)
		{
			float stickRad = atan2(padLStick.z, padLStick.x);

			// カメラの回り込みを取得
			auto camera = GetStage()->GetView()->GetTargetCamera();
			auto mainCamera = dynamic_pointer_cast<MainCamera>(camera);
			if (mainCamera)
			{
				float cameraAngle = mainCamera->GetAngle();

				stickRad += cameraAngle + XM_PIDIV2;
				padLStick.x = cos(stickRad);
				padLStick.z = sin(stickRad);
			}
		}	

		// カメラに回り込みの取得
		auto transComp = GetComponent<Transform>();
		auto pos = transComp->GetPosition();
		pos += padLStick * 3.0f * delta;

		if (padLStick.length() > 0.0f) // スティックの入力確認
		{
			// スティックの傾きに合わせてオブジェクトを回転させる
			float rotY = atan2f(-padLStick.z, padLStick.x); // 2次元ベクトルを角度(ラジアン)に変換する
			transComp->SetRotation(Vec3(0, rotY + XM_PIDIV2, 0)); // Y軸中心の回転（キャラクターをゼロ度方向に向かせるために90度多く回転させる）
		}
	}
}
