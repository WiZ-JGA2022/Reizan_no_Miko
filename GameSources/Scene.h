/*!
@file Scene.h
@brief シーン
*/
#pragma once

#include "stdafx.h"
#include "EfkInterface.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------
	class Scene : public SceneBase{
		//エフェクトのインターフェイス
		shared_ptr<EfkInterface> m_EfkInterface;

		int m_trapCount[4] = { 0 }; // 罠の数

		Vec3 m_playerPosition; // プレイヤーの位置
		Quat m_playerRotation; // プレイヤーの向き
		
		float m_cameraRadY; // カメラのY方向の位置
		float m_cameraRadXZ; // カメラのXZ方向の位置
		float m_cameraAngle; // カメラのアングル
		Vec3 m_cameraAt; // カメラの注視点

		Vec3 m_spikePosition[5]; // 棘罠の位置
		Vec3 m_lavaPosition[1]; // 溶岩罠の位置
		
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
		Scene() :
			SceneBase(),
			m_playerPosition(Vec3(0.0f)),
			m_playerRotation(Vec3(0.0f)),
			m_cameraRadY(0.0f),
			m_cameraRadXZ(0.0f),
			m_cameraAngle(XMConvertToRadians(270.0f)),
			m_cameraAt(Vec3(0.0f))
		{}
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

		// 更新処理
		virtual void OnUpdate() override;

		// 描画処理
		virtual void OnDraw() override;
		//--------------------------------------------------------------------------------------
		/**
		@brief イベント取得
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnEvent(const shared_ptr<Event>& event) override;

		// データを初期化する関数
		void ResetData();

		void SetBeforePlayerPosition(const Vec3& pos)
		{
			m_playerPosition = pos;
		}

		void SetBeforePlayerQuaternion(const Quat& rot)
		{
			m_playerRotation = rot;
		}

		void SetBeforeCameraRadY(const float radY)
		{
			m_cameraRadY = radY;
		}

		void SetBeforeCameraRadXZ(const float radXZ)
		{
			m_cameraRadXZ = radXZ;
		}

		void SetBeforeCameraAngle(const float angle)
		{
			m_cameraAngle = angle;
		}

		void SetBeforeCameraAt(const Vec3& at)
		{
			m_cameraAt = at;
		}
		void SetBeforeSpikePosition(const Vec3& pos, int index)
		{
			m_trapCount[0]++;
			m_spikePosition[index] = pos;
		}

		void SetBeforeLavaPosition(const Vec3& pos, int index)
		{
			m_trapCount[1]++;
			m_lavaPosition[index] = pos;
		}

		int GetBeforePlacedTrap(const int index)
		{
			return m_trapCount[index];
		}

		Vec3 GetBeforePlayerPosition() const
		{
			return m_playerPosition;
		}

		Quat GetBeforePlayerQuaternion() const
		{
			return m_playerRotation;
		}

		float GetBeforeCameraRadY() const
		{
			return m_cameraRadY;
		}

		float GetBeforeCameraRadXZ() const
		{
			return m_cameraRadXZ;
		}

		float GetBeforeCameraAngle() const
		{
			return m_cameraAngle;
		}

		Vec3 GetBeforeCameraAt() const
		{
			return m_cameraAt;
		}

		Vec3 GetBeforeSpikePosition(int index)
		{
			return m_spikePosition[index];
		}

		Vec3 GetBeforeLavaPosition(int index)
		{
			return m_lavaPosition[index];
		}
		//エフェクトのインターフェイスの取得
		shared_ptr<EfkInterface> GetEfkInterface() const {
			return m_EfkInterface;
		}
	};

}

//end basecross
