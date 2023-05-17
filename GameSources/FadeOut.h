/*!
@file FadeOut.cpp
@brief �t�F�[�h�A�E�g�̒�`
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	class FadeOut : public Sprites {
		const Vec2 m_DefaultSize;

		wstring m_texKey;

	public:
		FadeOut(const shared_ptr<Stage>& stage, const wstring& texKey);
		~FadeOut();

		void OnCreate() override;
		void OnUpdate() override;

	};
}

