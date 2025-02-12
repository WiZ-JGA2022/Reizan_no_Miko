/*!
@file EfkInterface.h
@brief Effekseerエフェクトのインターフェイス
*/

#pragma once

#include "stdafx.h"

#include <Effekseer.h>
#include <EffekseerRendererDX11.h>
//#include <EffekseerSoundXAudio2.h>


#pragma comment(lib, "Effekseer.lib" )
#pragma comment(lib, "EffekseerRendererDX11.lib" )
//#pragma comment(lib, "EffekseerSoundXAudio2.lib" )


namespace basecross {

	class EfkInterface;

	//--------------------------------------------------------------------------------------
	///	Effekseerエフェクトのエフェクト
	//--------------------------------------------------------------------------------------
	class EfkEffect: public ObjectInterface {
		wstring m_FileName;
		Effekseer::EffectRef m_Effect;
		weak_ptr<EfkInterface> m_EfkInterface;
		friend class EfkPlay;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンスラトクタ
		@param[in]	iface	インターフェイス
		@param[in]	filename	エフェクトファイル名
		*/
		//--------------------------------------------------------------------------------------
		EfkEffect(const shared_ptr<EfkInterface>& iface,const wstring& filename);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		//virtual ~EfkEffect();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	初期化
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
	};

	//--------------------------------------------------------------------------------------
	///	EffekseerエフェクトのPlayオブジェクト
	//--------------------------------------------------------------------------------------
	class EfkPlay : public ObjectInterface {
		::Effekseer::Handle m_Handle;
		weak_ptr<EfkInterface> m_EfkInterface;
	public:

		/**
		@brief	コンスラトクタ
		@param[in]	effect	エフェクト
		@param[in]	emitter	エミッター
		*/
		EfkPlay(const shared_ptr<EfkEffect>& effect, const bsm::Vec3& emitter, const bsm::Vec3& scale);
		virtual ~EfkPlay();

		/**
		@brief	初期化（空関数）
		@return	なし
		*/
		void OnCreate() override {}
		
		/**
		@brief	エフェクトをストップさせる
		@return	なし
		*/
		void StopEffect();

		/**
		@brief	エフェクトを移動する
		@param[in]	Location	移動ベクトル（相対方向）
		@return	なし
		*/
		void AddLocation(const bsm::Vec3& Location);
	};


	//--------------------------------------------------------------------------------------
	///	Effekseerエフェクトのインターフェイス
	//--------------------------------------------------------------------------------------
	class EfkInterface : public ObjectInterface, public ShapeInterface {
		::Effekseer::ManagerRef m_Manager;
		::EffekseerRenderer::RendererRef m_Renderer;
		friend class EfkPlay;
		friend class EfkEffect;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンスラトクタ
		*/
		//--------------------------------------------------------------------------------------
		EfkInterface();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
+		*/
		//--------------------------------------------------------------------------------------
		//virtual ~EfkInterface();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	ビューと射影行列を設定する
		@param[in]	view	ビュー行列
		@param[in]	proj	射影行列
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetViewProj(const bsm::Mat4x4& view, const bsm::Mat4x4& proj);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	初期化
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	更新処理
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	描画処理。
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override;
	};



}
//end basecross
