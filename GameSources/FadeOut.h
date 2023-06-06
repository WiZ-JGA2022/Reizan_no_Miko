/*!
@file FadeOut.cpp
@brief フェードアウトの定義
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	class FadeOut : public Sprites {
		// 画面のデフォルトサイズ
		const Vec2 m_DefaultSize; 

		wstring m_texKey; //テクスチャ名

	public:
		//コンストラクタ
		FadeOut(const shared_ptr<Stage>& stage, const wstring& texKey);
		//デストラクタ
		~FadeOut();

		//初期化
		void OnCreate() override;
		//更新処理
		void OnUpdate() override;

	};
}

