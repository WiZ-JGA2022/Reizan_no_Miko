/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"
#include <time.h>

namespace basecross {

	float delayCount;

    float delaySeconds = 2.0f;
    float bulletSpeed = 10000.0f;
    const float DESTROY_COUNT = 5.0f;

	//--------------------------------------------------------------------------------------
	///	砲弾
	//--------------------------------------------------------------------------------------
	FireSphere::FireSphere(const shared_ptr<Stage>& StagePtr,
		const Vec3& Emitter, const Vec3& Velocity
	) :
		GameObject(StagePtr),
		m_Emitter(Emitter),
		m_Velocity(Velocity),
		m_Scale(0.25f),
		m_ActiveMaxY(-5.0f)
	{}
	FireSphere::~FireSphere() {}

	void FireSphere::OnCreate() {
		auto ptrTrans = GetComponent<Transform>();

		ptrTrans->SetScale(Vec3(m_Scale));
		ptrTrans->SetQuaternion(Quat());
		ptrTrans->SetPosition(m_Emitter);
		//コリジョンを付ける
		auto ptrColl = AddComponent<CollisionSphere>();
		//衝突判定はNoneにする
		ptrColl->SetAfterCollision(AfterCollision::None);
		ptrColl->SetSleepActive(true);
		//重力をつける
		auto ptrGra = AddComponent<Gravity>();
		//影をつける
		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(L"DEFAULT_SPHERE");

		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 1.0f));
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetMeshResource(L"DEFAULT_SPHERE");
		

		auto group = GetStage()->GetSharedObjectGroup(L"FireSphereGroup");
		group->IntoGroup(GetThis<GameObject>());


	}
	void FireSphere::OnUpdate()
	{
		auto ptrTrans = GetComponent<Transform>();
		if (ptrTrans->GetPosition().y > m_ActiveMaxY) {
			float elapsedTime = App::GetApp()->GetElapsedTime();
			auto Pos = ptrTrans->GetPosition();
			Pos += m_Velocity * elapsedTime;
			ptrTrans->SetPosition(Pos);
		}
		else {
			SetUpdateActive(false);
			SetDrawActive(false);
		}

	}
	void FireSphere::Reset(const Vec3& Emitter, const Vec3& Velocity)
	{
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->ResetPosition(Emitter);
		m_Velocity = Velocity;
		auto ptrGrav = GetComponent<Gravity>();
		ptrGrav->SetGravityVerocityZero();
		SetUpdateActive(true);
		SetDrawActive(true);

	}

	void  FireSphere::OnCollisionEnter(const CollisionPair& Pair)
	{
		auto ptrTrans = GetComponent<Transform>();

	}
    void PlayerShot::OnUpdate()
    {
        auto& app = App::GetApp();

        float delta = app->GetElapsedTime(); // 前フレームからの経過時間（60FPS）

        // レベルアップイベント中は処理を停止する
        //if (levelUpEvent.GetComponent<LevelUpEvent>().GetActiveOrUnActive())
        //{
        //    return;
        //}

        delayCount -= delta;

        if (delayCount < 0)
        {
            //GameObject Talisman = Instantiate(bulletPrefab, transform.position, player.transform.localRotation);
            //Rigidbody shellRb = Talisman.GetComponent<Rigidbody>();

            //// 弾速は自由に設定
            //shellRb.AddForce(transform.forward * bulletSpeed);

            //// 5秒後に砲弾を破壊する
            //Destroy(Talisman, DESTROY_COUNT);

            delayCount = delaySeconds;
        }
    } // end Update

    void LevelUpShotDelay(float level)
    {
        delaySeconds = delaySeconds - level / 100;
    }
	//Xボタン
	void PlayerShot::OnPushX() {
		auto ptrTrans = GetComponent<Transform>();
		Vec3 pos = ptrTrans->GetPosition();
		pos.y += 0.3f;
		Quat qt = ptrTrans->GetQuaternion();
		Vec3 rot = qt.toRotVec();
		float rotY = rot.y;
		Vec3 velo(sin(rotY), 0.1f, cos(rotY));
		velo.normalize();
		velo *= 15.0f;
		auto group = GetStage()->GetSharedObjectGroup(L"FireSphereGroup");
		auto& vec = group->GetGroupVector();
		for (auto& v : vec) {
			auto shObj = v.lock();
			if (shObj) {
				if (!shObj->IsUpdateActive()) {
					auto shFire = dynamic_pointer_cast<FireSphere>(shObj);
					if (shFire) {
						shFire->Reset(pos, velo);
						return;
					}
				}
			}
		}
		//空がなかったので新たに作成
		GetStage()->AddGameObject<FireSphere>(pos, velo);
	}

}
