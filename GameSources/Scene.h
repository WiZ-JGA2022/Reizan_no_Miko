/*!
@file Scene.h
@brief �V�[��
*/
#pragma once

#include "stdafx.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	�Q�[���V�[��
	//--------------------------------------------------------------------------------------
	class Scene : public SceneBase{
		int m_TexNum = 0;
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
		Scene() :SceneBase(){}
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
		//--------------------------------------------------------------------------------------
		/**
		@brief �C�x���g�擾
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnEvent(const shared_ptr<Event>& event) override;
		//--------------------------------------------------------------------------------------
		/**
		@brief �e�N�X�`���̔ԍ����擾
		*/
		//--------------------------------------------------------------------------------------
		int GetTexNum()
		{
			return m_TexNum;
		}
	};

}

//end basecross
