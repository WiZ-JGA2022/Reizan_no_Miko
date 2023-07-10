/*!
@file PlayerController.cpp
@brief プレイヤーキャラ
@prod 矢吹悠葉
*/

#include "stdafx.h"
#include "Project.h"


namespace basecross {
	//--------------------------------------------------------------------------------------
	//	class PlayerController : public GameObject;
	//	用途: プレイヤー
	//--------------------------------------------------------------------------------------
	PlayerController::PlayerController(const std::shared_ptr<Stage>& stage, const int condition) :
		GameObject(stage),
		m_RecastCount(9.0f),
		m_position(Vec3(0)),
		m_quaternion(Quat(0)),
		m_condition((PlayerCondition)condition),
		m_recastFlame(m_RecastCount)
	{
	}
	PlayerController::PlayerController(const std::shared_ptr<Stage>& stage, const Vec3& position, const Quat& quaternion, const int condition) :
		GameObject(stage),
		m_RecastCount(6.0f),
		m_position(position),
		m_quaternion(quaternion),
		m_condition((PlayerCondition)condition),
		m_recastFlame(m_RecastCount)
	{
	}
	PlayerController::~PlayerController() {}


	void PlayerController::OnCreate()
	{
		m_transform = GetComponent<Transform>();
		m_transform->SetPosition(m_position.x, 0.4f, m_position.z);
		m_transform->SetQuaternion(m_quaternion);
		m_transform->SetScale(1.0f, 1.0f, 1.0f);

		// コリジョンをつける
		auto ptrColl = AddComponent<CollisionCapsule>();
		// 衝突判定はAuto
		ptrColl->SetAfterCollision(AfterCollision::Auto);
		ptrColl->SetSleepActive(false);

		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);
		//影をつける（シャドウマップを描画する）
		auto ptrShadow = AddComponent<Shadowmap>();
		//影の形を設定
		ptrShadow->SetMeshResource(L"MIKO");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		//描画コンポーネントの設定
		auto drawComp = AddComponent<BcPNTBoneModelDraw>();
		drawComp->SetFogEnabled(false);
		//描画するメッシュを設定
		drawComp->SetMeshResource(L"MIKO");
		drawComp->SetMeshToTransformMatrix(spanMat);
		// アニメーションの追加
		drawComp->AddAnimation(L"wait_player", 0, 30, true, 20.0f);
		drawComp->AddAnimation(L"died_player", 92, 30, false, 20.0f);
		drawComp->AddAnimation(L"walk_player", 124, 30, true, 20.0f);
		// 初期アニメーションを設定
		drawComp->ChangeCurrentAnimation(L"wait_player");

		// 透過処理を有効化
		SetAlphaActive(true);

		// 描画レイヤーを設定
		SetDrawLayer((int)DrawLayer::Bottom);
	}

	void PlayerController::OnUpdate()
	{
		// 各種情報の取得
		auto ptrDraw = GetComponent<BcPNTBoneModelDraw>();
		auto playerStatus = GetStage()->GetSharedGameObject<PlayerStatusController>(L"PlayerStatus");
		float elapsedTime = App::GetApp()->GetElapsedTime();

		// アニメーションの更新
		ptrDraw->UpdateAnimation(elapsedTime);

		// HPが0以下になった時
		if (playerStatus->GetStatusValue(L"HP") <= 0)
		{
			// プレイヤーがまだ死亡状態でなかったなら
			if (m_action != PlayerMotion::Died)
			{
				// 死亡アニメーションに切り替える
				ptrDraw->ChangeCurrentAnimation(L"died_player");
				// プレイヤーを死亡状態にする
				m_action = PlayerMotion::Died;
			}

			// 死亡アニメーションが終わった時
			if (ptrDraw->IsTargetAnimeEnd() && ptrDraw->GetCurrentAnimation() == L"died_player")
			{
				// プレイヤーの更新処理と描画処理を停止する
				SetUpdateActive(false);
				SetDrawActive(false);
			}
			// これ以降の処理は行わない
			return;
		}

		// 弾のリキャストタイムを減少させる
		m_recastFlame -= 0.1f;
		
		// プレイヤーの移動処理
		PlayerMoveProcess();

		// リキャストタイムが0以下かつプレイヤーの状態がスタンバイ状態でなければ
		if (m_recastFlame <= 0 && m_condition != PlayerCondition::Standby)
		{
			// 弾を発射する
			GetStage()->AddGameObject<PlayerBullet>();

			// リキャストタイムのリセット
			m_recastFlame = m_RecastCount - (m_RecastCount * (playerStatus->GetStatusValue(L"HASTE") - 1.0f));
		}

		// コントローラーデバイスの取得
		auto& app = App::GetApp();
		auto device = app->GetInputDevice();
		auto& pad = device.GetControlerVec()[0];
		// プレイヤーがスタンバイ状態のとき
		if (m_condition == PlayerCondition::Standby)
		{	
			// スパイク罠の設置数が上限未満なら
			if (m_trapCount[0] < (int)TrapLimit::SpikeTrap)
			{
				// Xボタンで
				if (pad.wPressedButtons & XINPUT_GAMEPAD_X)
				{
					// SEの再生
					auto XAPtr = app->GetXAudio2Manager();
					XAPtr->Start(L"SPIKE_SE", 0, 0.3f);

					// 罠を設置
					Vec3 trapPosition = Vec3(m_transform->GetPosition().x, -0.5f, m_transform->GetPosition().z);
					GetStage()->AddGameObject<SpikeTrap>(trapPosition, Vec3(5.0f, 0.5f, 5.0f));
					app->GetScene<Scene>()->SaveSpikePosition(trapPosition, m_trapCount[0]);
					m_trapCount[0]++;
				}
			}
			// 溶岩罠の設置数が上限未満なら
			if (m_trapCount[1] < (int)TrapLimit::SpurtLava)
			{
				// Yボタンで
				if (pad.wPressedButtons & XINPUT_GAMEPAD_Y)
				{
					// SEの再生
					auto XAPtr = app->GetXAudio2Manager();
					XAPtr->Start(L"SPIKE_SE", 0, 0.3f);

					// 罠の設置
					Vec3 trapPosition = Vec3(m_transform->GetPosition().x, -0.5f, m_transform->GetPosition().z);
					GetStage()->AddGameObject<SpurtLava>(trapPosition, Vec3(4.0f, 20.0f, 4.0f));
					app->GetScene<Scene>()->SaveLavaPosition(trapPosition, m_trapCount[1]);
					m_trapCount[1]++;
				}
			}
		}
	}

	void PlayerController::PlayerMoveProcess()
	{
		// コントローラーデバイスの取得
		auto& app = App::GetApp();
		auto device = app->GetInputDevice();
		auto& pad = device.GetControlerVec()[0];	
		// デルタタイムの取得
		float delta = app->GetElapsedTime();

		// Lスティックのベクトルを取得する変数
		Vec3 padLStick(pad.fThumbLX, 0.0f, pad.fThumbLY);

		// Lスティックが傾いているとき
		if (padLStick.length() > 0.0f)
		{
			auto ptrDraw = GetComponent<BcPNTBoneModelDraw>();
			if (m_action != PlayerMotion::Walk)
			{
				// 歩きモーションになる
				ptrDraw->ChangeCurrentAnimation(L"walk_player");
				m_action = PlayerMotion::Walk;
			}

			// ラジアンでスティックの角度を取得
			float stickRad = atan2(padLStick.z, padLStick.x);
			// カメラの取得
			auto camera = GetStage()->GetView()->GetTargetCamera();
			auto myCamera = dynamic_pointer_cast<MyCamera>(camera);
			if (myCamera)
			{
				// カメラの角度に合わせてプレイヤーの動きを調整する処理
				float cameraAngle = myCamera->GetAngle();
				stickRad += cameraAngle + XM_PIDIV2;
				padLStick.x = cos(stickRad);
				padLStick.z = sin(stickRad);
			}

			auto playerStatus = GetStage()->GetSharedGameObject<PlayerStatusController>(L"PlayerStatus");

			// 移動処理
			auto pos = m_transform->GetPosition();
			pos += padLStick * playerStatus->GetStatusValue(L"SPD") * delta;
			m_transform->SetPosition(pos);

			// 回転処理
			float rotY = atan2f(-padLStick.z, padLStick.x);
			m_transform->SetRotation(Vec3(0, rotY + XM_PIDIV2, 0)); 
		}
		else // Lスティックが傾いていない時
		{
			auto ptrDraw = GetComponent<BcPNTBoneModelDraw>();
			if (m_action != PlayerMotion::Wait)
			{
				// 待機モーションになる
				ptrDraw->ChangeCurrentAnimation(L"wait_player");
				m_action = PlayerMotion::Wait;
			}

		}
	}
}
