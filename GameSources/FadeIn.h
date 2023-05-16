/*!
@file FadeIn.cpp
@brief �t�F�[�h�C���̒�`
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	class FadeIn : public Sprites {
		const Vec2 m_DefaultSize;
		
		wstring m_texKey;

	public:
		FadeIn(const shared_ptr<Stage>& stage, const wstring& texKey);
		~FadeIn();

		void OnCreate() override;
		void OnUpdate() override;
	};
}
