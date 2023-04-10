/*!
@file MainCamera.h
@brief ƒJƒƒ‰
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class MainCamera : public Camera
	{
		std::shared_ptr<Transform> m_targetTrans;

	public:
		MainCamera()
		{
		}
		void OnCreate() override;
		void OnUpdate() override;

		void SetTarget(const std::shared_ptr<GameObject>& target)
		{
			m_targetTrans = target->GetComponent<Transform>();
		}
	};
}
