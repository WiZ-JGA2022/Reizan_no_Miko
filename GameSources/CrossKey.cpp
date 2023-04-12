/*!
@file CrossKey.cpp
@brief 十字キーのUI
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	constexpr float m_startScaleZ = 1.0f;// 大きさ
	constexpr float m_startPosZ = 1.0f;	 // 奥行き
	constexpr float m_helfSize = 0.5f;	 // 半分の大きさ
	//--------------------------------------------------------------------------------------
	///	コントローラーボタンのスプライト
	//--------------------------------------------------------------------------------------
	CrossKeySprites::CrossKeySprites(const shared_ptr<Stage>& StagePtr,
		const int& TextureNum,
		bool Trace,
		const Vec2& StartScale,
		const Vec2& StartPos,
		const int& TexNum
	) :
		GameObject(StagePtr),
		m_textureNum(TextureNum),
		m_alpha(Trace),
		m_defaultScale(StartScale),
		m_defaultPos(StartPos),
		m_texNum(TexNum)
	{}

	wstring CrossKeySprites::ControllerNum(int i) {
		if (i == 0)
		{
			m_textureKey = L"CROSSKEY_UP";
			return m_textureKey;
		}
		else if (i == 1)
		{
			m_textureKey = L"CROSSKEY_RIGHT";
			return m_textureKey;

		}
		else if (i == 2)
		{
			m_textureKey = L"CROSSKEY_DOWN";
			return m_textureKey;
		}
		else
		{

		}

	} // end ControllerNum

	// 初期化
	void CrossKeySprites::OnCreate()
	{
		float HelfSize = m_helfSize;

		// 頂点配列(縦横5個ずつ表示)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-HelfSize, HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize, HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-HelfSize,-HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(HelfSize,-HelfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 1.0f)) },
		};

		// インデックス配列
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_alpha);
		auto PtrTransform = GetComponent<Transform>();
		PtrTransform->SetScale(m_defaultScale.x, m_defaultScale.y, m_startScaleZ);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetPosition(m_defaultPos.x, m_defaultPos.y, m_startPosZ);

		std::wstring Key;
		Key = ControllerNum(m_textureNum);

		// 頂点とインデックスを指定してスプライト作成
		auto PtrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		PtrDraw->SetSamplerState(SamplerState::LinearWrap);
		PtrDraw->SetTextureResource(Key);
		PtrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 1.0f));
		SetDrawActive(true);

	} // end OnCreate

	// 更新処理
	void CrossKeySprites::OnUpdate() {
		auto& app = App::GetApp();
		auto stage = app->GetScene<Scene>()->GetActiveStage();	// ステージオブジェクトを取得する
		auto objs = stage->GetGameObjectVec();					// ステージに追加されているすべてのオブジェクト

		// 処理終了後に表示した画像を消す処理
		for (auto& obj : objs)
		{
			// LevelUpButtonへのキャストを試みる
			auto levelUpButton = dynamic_pointer_cast<RandomSelectLevelUpButton>(obj);
			if (levelUpButton)
			{
				auto controllerKeyFlg = levelUpButton->GetEventActive();
				if (!controllerKeyFlg) {
					GetStage()->RemoveGameObject<CrossKeySprites>(GetThis<CrossKeySprites>());
				}
			}
		}
	} // end OnUpdate
}
