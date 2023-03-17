/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
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

        float delta = app->GetElapsedTime(); // �O�t���[������̌o�ߎ��ԁi60FPS�j

        // ���x���A�b�v�C�x���g���͏������~����
        //if (levelUpEvent.GetComponent<LevelUpEvent>().GetActiveOrUnActive())
        //{
        //    return;
        //}

        delayCount -= delta;

        if (delayCount < 0)
        {
            //GameObject Talisman = Instantiate(bulletPrefab, transform.position, player.transform.localRotation);
            //Rigidbody shellRb = Talisman.GetComponent<Rigidbody>();

            //// �e���͎��R�ɐݒ�
            //shellRb.AddForce(transform.forward * bulletSpeed);

            //// 5�b��ɖC�e��j�󂷂�
            //Destroy(Talisman, DESTROY_COUNT);

            delayCount = delaySeconds;
        }
    } // end Update

    void LevelUpShotDelay(float level)
    {
        delaySeconds = delaySeconds - level / 100;
    }

}
