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

}
