/*!
@file Scene.h
@brief シーン
*/
#pragma once

#include "stdafx.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------
	class Scene : public SceneBase{
		int m_texNum = 0;

		Vec3 m_playerPosition = Vec3(0);
	public:
		//--------------------------------------------------------------------------------------
		/**
		@brief リソースの作成
		*/
		//--------------------------------------------------------------------------------------
		void CreateResourses();

		/**
		* テクスチャの読み込み
		*
		* @param UseTextureName basecross内で使用するテクスチャ名
		* @param TextureDataName テクスチャデータ(png, jpg)の名前
		*/
		void RoadTexture(const wstring& UseTextureName, const wstring& TextureDataName);

		/**
		* サウンドの読み込み
		*
		* @param soundName basecross内で使用するサウンド名
		* @param soundDataName サウンドデータ(wav)の名前
		*/
		void RoadSound(const wstring& soundName, const wstring& soundDataName);

		/**
		* 静的なモデルの読み込み
		*
		* @param staticModelMeshName basecross内で使用するモデル名
		* @param staticModelbmfName モデルのbmfファイル名
		*/
		void RoadStaticModelMesh(const wstring& staticModelMeshName, const wstring& staticModelbmfName);

		/**
		* ボーンモデルの読み込み
		*
		* @param boneModelMeshName basecross内で使用するモデル名
		* @param boneModelMeshTangentName basecross内で使用するモデル名(タンジェント付き)
		* @param boneModelbmfName モデルのbmfファイル名
		*/
		void RoadBoneModel(const wstring& boneModelbmfName, const wstring& boneModelMeshName, const wstring& boneModelMeshTangentName);

		//--------------------------------------------------------------------------------------
		/**
		@brief コンストラクタ
		*/
		//--------------------------------------------------------------------------------------
		Scene() :SceneBase(){}
		//--------------------------------------------------------------------------------------
		/**
		@brief デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~Scene();
		//--------------------------------------------------------------------------------------
		/**
		@brief 初期化
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/**
		@brief イベント取得
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnEvent(const shared_ptr<Event>& event) override;
		//--------------------------------------------------------------------------------------
		/**
		@brief テクスチャの番号を取得
		*/
		//--------------------------------------------------------------------------------------
		int GetTexNum()
		{
			return m_texNum;
		}

		void SetBeforePlayerPosition(Vec3 pos)
		{
			m_playerPosition = pos;
		}

		Vec3 GetBeforePlayerPosition() const
		{
			return m_playerPosition;
		}
	};

}

//end basecross
