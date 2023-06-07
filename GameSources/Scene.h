/*!
@file Scene.h
@brief �V�[��
*/
#pragma once

#include "stdafx.h"
#include "EfkInterface.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	�Q�[���V�[��
	//--------------------------------------------------------------------------------------
	class Scene : public SceneBase{
		//�G�t�F�N�g�̃C���^�[�t�F�C�X
		shared_ptr<EfkInterface> m_EfkInterface;

		int m_trapCount[4] = { 0 }; // 㩂̐�

		Vec3 m_playerPosition; // �v���C���[�̈ʒu
		Quat m_playerRotation; // �v���C���[�̌���
		
		float m_cameraRadY; // �J������Y�����̈ʒu
		float m_cameraRadXZ; // �J������XZ�����̈ʒu
		float m_cameraAngle; // �J�����̃A���O��
		Vec3 m_cameraAt; // �J�����̒����_

		Vec3 m_spikePosition[5]; // ��㩂̈ʒu
		Vec3 m_lavaPosition[1]; // �n��㩂̈ʒu
		
	public:
		//--------------------------------------------------------------------------------------
		/**
		@brief ���\�[�X�̍쐬
		*/
		//--------------------------------------------------------------------------------------
		void CreateResourses();

		/**
		* �e�N�X�`���̓ǂݍ���
		*
		* @param UseTextureName basecross���Ŏg�p����e�N�X�`����
		* @param TextureDataName �e�N�X�`���f�[�^(png, jpg)�̖��O
		*/
		void RoadTexture(const wstring& UseTextureName, const wstring& TextureDataName);

		/**
		* �T�E���h�̓ǂݍ���
		*
		* @param soundName basecross���Ŏg�p����T�E���h��
		* @param soundDataName �T�E���h�f�[�^(wav)�̖��O
		*/
		void RoadSound(const wstring& soundName, const wstring& soundDataName);

		/**
		* �ÓI�ȃ��f���̓ǂݍ���
		*
		* @param staticModelMeshName basecross���Ŏg�p���郂�f����
		* @param staticModelbmfName ���f����bmf�t�@�C����
		*/
		void RoadStaticModelMesh(const wstring& staticModelMeshName, const wstring& staticModelbmfName);

		/**
		* �{�[�����f���̓ǂݍ���
		*
		* @param boneModelMeshName basecross���Ŏg�p���郂�f����
		* @param boneModelMeshTangentName basecross���Ŏg�p���郂�f����(�^���W�F���g�t��)
		* @param boneModelbmfName ���f����bmf�t�@�C����
		*/
		void RoadBoneModel(const wstring& boneModelbmfName, const wstring& boneModelMeshName, const wstring& boneModelMeshTangentName);

		//--------------------------------------------------------------------------------------
		/**
		@brief �R���X�g���N�^
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
		@brief �f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~Scene();
		//--------------------------------------------------------------------------------------
		/**
		@brief ������
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;

		// �X�V����
		virtual void OnUpdate() override;

		// �`�揈��
		virtual void OnDraw() override;
		//--------------------------------------------------------------------------------------
		/**
		@brief �C�x���g�擾
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnEvent(const shared_ptr<Event>& event) override;

		// �f�[�^������������֐�
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
		//�G�t�F�N�g�̃C���^�[�t�F�C�X�̎擾
		shared_ptr<EfkInterface> GetEfkInterface() const {
			return m_EfkInterface;
		}
	};

}

//end basecross
