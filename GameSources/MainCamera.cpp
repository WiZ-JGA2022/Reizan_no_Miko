/*!
@file MyCamera.cpp
@brief カメラ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	MyCameraカメラ（コンポーネントではない）
	//--------------------------------------------------------------------------------------
	//構築と破棄
	MyCamera::MyCamera() :
		Camera(),
		m_toTargetLerp(1.0f),
		m_radY(0.5f),
		m_radXZ(0),
		m_CameraUpDownSpeed(0.5f),
		m_CameraUnderRot(0.1f),
		m_ArmLen(10.0f),
		m_RotSpeed(1.0f),
		m_angle(XMConvertToRadians(270.0f))
	{}
	MyCamera::~MyCamera() {}

	void MyCamera::OnCreate() {
		// 初期値の設定
		auto scene = App::GetApp()->GetScene<Scene>();
		m_radXZ = scene->GetBeforeCameraRadXZ();
		m_radY = scene->GetBeforeCameraRadY();
		m_angle = scene->GetBeforeCameraAngle();
	}

	void MyCamera::OnUpdate() {
	
		// コントローラーの取得
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		// 追従するオブジェクトのポインタを取得
		auto ptrTarget = GetTargetObject();
		// デルタタイム
		float elapsedTime = App::GetApp()->GetElapsedTime();

		// EyeとAtの設定
		Vec3 newEye = GetEye();
		Vec3 newAt = Vec3(
			ptrTarget->GetComponent<Transform>()->GetPosition().x,
			ptrTarget->GetComponent<Transform>()->GetPosition().y + 1.0f, 
			ptrTarget->GetComponent<Transform>()->GetPosition().z
		);

		// 計算に使うためのベクトル
		m_armVec = newEye - newAt;
		// 正規化
		m_armVec.normalize();

		// スティックの取得
		float fThumbRY = 0.0f;
		float fThumbRX = 0.0f;
		WORD wButtons = 0;
		if (cntlVec[0].bConnected) {
			fThumbRY = cntlVec[0].fThumbRY;
			fThumbRX = cntlVec[0].fThumbRX;
			wButtons = cntlVec[0].wButtons;
		}

		//上下角度の変更
		if (cntlVec[0].fThumbRY >= 0.5f ) {
			m_radY += m_CameraUpDownSpeed * elapsedTime;

		}
		else if (cntlVec[0].fThumbRY <= -0.5f ) {
			m_radY -= m_CameraUpDownSpeed * elapsedTime;
		}

		// ここで設定した高さ以上に行かない
		if (m_radY > XM_PI * 4 / 9.0f) {
			m_radY = XM_PI * 4 / 9.0f;
		}
		else if (m_radY <= m_CameraUnderRot) {
			// カメラが限界下に下がったらそれ以上下がらない
			m_radY = m_CameraUnderRot;
		}
		m_armVec.y = sin(m_radY); // Yの位置を設定

		// Y軸回転を作成
		if (cntlVec[0].fThumbRX != 0  ) {
			// 回転スピードを反映
			if (cntlVec[0].fThumbRX != 0) {
				m_radXZ += -cntlVec[0].fThumbRX * elapsedTime * m_RotSpeed;
			}
		}
		// クオータニオンでY回転を計算
		Quat qtXZ;
		qtXZ.rotation(-m_radXZ, bsm::Vec3(0, 1.0f, 0));
		qtXZ.normalize();
		// 移動先の行列を計算することで、XZの値を算出
		Mat4x4 Mat;
		Mat.strTransformation(
			bsm::Vec3(1.0f, 1.0f, 1.0f),
			bsm::Vec3(0.0f, 0.0f, -1.0f),
			qtXZ
		);

		Vec3 posXZ = Mat.transInMatrix();
		// 腕角度に代入
		m_armVec.x = posXZ.x;
		m_armVec.z = posXZ.z;
		// 腕角度を正規化
		m_armVec.normalize();

		// カメラアングルの設定
		m_angle += -fThumbRX * elapsedTime;

		// 目指したい場所にアームの値と腕ベクトルでEyeを調整
		Vec3 toEye = newAt + m_armVec * m_ArmLen;
		newEye = Lerp::CalculateLerp(GetEye(), toEye, 0, 1.0f, m_toTargetLerp, Lerp::Linear);

		// 位置の更新
		SetAt(newAt);
		SetEye(newEye);
		Camera::OnUpdate();	
	}
}
//end basecross