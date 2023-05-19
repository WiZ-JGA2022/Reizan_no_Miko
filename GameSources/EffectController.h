/*!
@file EffectController.h
@brief エフェクト
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class EffectController : public GameObject
	{
		float m_totalTime;
		Effekseer::Handle m_handle;
		Effekseer::ManagerRef m_manager;
		EffekseerRendererDX11::RendererRef m_renderer;

		Effekseer::EffectRef m_spurtLava;
		Effekseer::EffectRef m_fireBall;
		Effekseer::EffectRef m_runDust;
		Effekseer::EffectRef m_damage;

		map<wstring, Effekseer::EffectRef> m_effects = {
			{L"SpurtLava_Efc", m_spurtLava},
			{L"FireBall_Efc", m_fireBall},
			{L"RunDust_Efc", m_runDust},
			{L"Damage_Efc", m_damage}
		};

	public:
		EffectController(const shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_totalTime(0.0f),
			m_handle(0),
			m_manager(nullptr),
			m_renderer(nullptr),
			m_spurtLava(nullptr),
			m_fireBall(nullptr),
			m_runDust(nullptr),
			m_damage(nullptr)
		{}
		virtual ~EffectController() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnDraw() override;
		virtual void OnDestroy()override;

		void PlayEffect(const wstring& effectKey, const Vec3& position, const float stopTime);
	};

}
