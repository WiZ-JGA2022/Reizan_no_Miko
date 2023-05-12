/*!
@file EffectController.h
@brief エフェクト
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class EffectController : public GameObject
	{
		float m_TotalTime;
		Effekseer::Handle m_handle;
		Effekseer::ManagerRef m_manager;
		EffekseerRendererDX11::RendererRef m_renderer;
		Effekseer::EffectRef m_effect;


	public:
		EffectController(const shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_TotalTime(0.0f),
			m_handle(0),
			m_manager(nullptr),
			m_renderer(nullptr),
			m_effect(nullptr) {}
		virtual ~EffectController() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnDraw() override;
		virtual void OnDestroy()override;
	};

}
