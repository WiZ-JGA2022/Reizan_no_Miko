/*!
@file PlayerHpGauge.h
@brief �v���C���[��HP�o�[
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class PlayerHpGauge :public GameObject
	{
		const Vec2 m_DefaultSize; // PlayerHpGauge�̏����T�C�Y
		const wstring m_TexKey; // �e�N�X�`���L�[
		const float m_AddPosY; // PlayerHpGauge��pos
		
		// �h���[�R���|�[�l���g�ƃg�����X�t�H�[���R���|�[�l���g���擾
		weak_ptr<PlayerStatusController> m_playerStatus;
		shared_ptr<PCTStaticDraw> m_draw;
		
		// �X�v���C�g�̌��ɂȂ钸�_�f�[�^�ƒ��_�C���f�b�N�X
		vector<VertexPositionNormalTexture> m_vertices;
		vector<uint16_t> m_indices;

		Quat Billboard(const Vec3& Line) {
			Vec3 temp = Line;
			Mat4x4 rotMatrix;
			Vec3 defUp(0, 1.0f, 0);
			Vec2 tempVec2(temp.x, temp.z);
			if (tempVec2.length() < 0.1f) {
				defUp = Vec3(0, 0, 1.0f);
			}
			temp.normalize();
			rotMatrix = XMMatrixLookAtLH(Vec3(0, 0, 0), temp, defUp);
			rotMatrix.inverse();
			Quat qt;
			qt = rotMatrix.quatInMatrix();
			qt.normalize();
			return qt;
		}


	public:
		// �R���X�g���N�^
		PlayerHpGauge(const shared_ptr<Stage>& StagePtr,
			const shared_ptr<PlayerStatusController>& objectPtr,
			const wstring& texKey);
		// �f�X�g���N�^
		virtual ~PlayerHpGauge();
		// ������
		virtual void OnCreate() override;
		// �X�V����
		virtual void OnUpdate() override;
		// Gauge�̍X�V����
		void UpdateGaugeSize(int gaugeSizeLimit, float currentGaugeSize);
	};

}