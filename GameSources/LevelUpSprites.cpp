/*!
@file LevelUpSprites.cpp
@brief  LevelUpイベント中に出す画像の実装
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
	LevelUpSprites::LevelUpSprites(const shared_ptr<Stage>& StagePtr,
		const int& TextureNum,
		bool Trace,
		const Vec2& StartScale,
		const Vec2& StartPos,
		const int& TexNum
	) :
		GameObject(StagePtr),
		m_TextureNum(TextureNum),
		m_Alpha(Trace),
		m_DefaultScale(StartScale),
		m_DefaultPos(StartPos),
		m_TexNum(TexNum)
	{}

	wstring LevelUpSprites::ControllerNum(int i) {
		if (i == 0x0001)
		{
			m_TextureKey = L"ARROW_UP_TX";
			return m_TextureKey;
		}
		else if (i == 0x0002)
		{
			m_TextureKey = L"ARROW_DOWN_TX";
			return m_TextureKey;

		}
		else if (i == 0x0004)
		{
			m_TextureKey = L"ARROW_LEFT_TX";
			return m_TextureKey;

		}
		else if (i == 0x0008)
		{
			m_TextureKey = L"ARROW_RIGHT_TX";
			return m_TextureKey;

		}
		else if (i == 0x1000)
		{
			m_TextureKey = L"BUTTON_A_TX";
			return m_TextureKey;

		}
		else if (i == 0x2000)
		{
			m_TextureKey = L"BUTTON_B_TX";
			return m_TextureKey;

		}
		else if (i == 0x4000)
		{
			m_TextureKey = L"BUTTON_X_TX";
			return m_TextureKey;

		}
		else if (i == 0x8000)
		{
			m_TextureKey = L"BUTTON_Y_TX";
			return m_TextureKey;
		}
		else
		{
			return 0;
		}
	} // end ControllerNum

	// 初期化
	void LevelUpSprites::OnCreate()
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
		SetAlphaActive(m_Alpha);
		auto PtrTransform = GetComponent<Transform>();
		PtrTransform->SetScale(m_DefaultScale.x, m_DefaultScale.y, m_startScaleZ);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetPosition(m_DefaultPos.x, m_DefaultPos.y, m_startPosZ);

		std::wstring Key;
		Key = ControllerNum(m_TextureNum);

		// 頂点とインデックスを指定してスプライト作成
		auto PtrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		PtrDraw->SetSamplerState(SamplerState::LinearWrap);
		PtrDraw->SetTextureResource(Key);
		PtrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, m_AlphaNum));
		SetDrawActive(true);
	} // end OnCreate

	// 更新処理
	void LevelUpSprites::OnUpdate() {
		auto& app = App::GetApp();
		auto stage = app->GetScene<Scene>()->GetActiveStage();	// ステージオブジェクトを取得する
		auto objs = stage->GetGameObjectVec();					// ステージに追加されているすべてのオブジェクト
		auto scene = App::GetApp()->GetScene<Scene>();


		if (scene->GetTexNum() > m_TexNum) {
			auto PtrDraw = AddComponent<PCTSpriteDraw>();
			m_AlphaNum = 1.0f;
			PtrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, m_AlphaNum));
		}
		else
		{
			auto PtrDraw = AddComponent<PCTSpriteDraw>();
			m_AlphaNum = 0.5f;
			PtrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, m_AlphaNum));

		}


		for (auto& obj : objs)
		{
			// StageBlocksへのキャストを試みる
			auto stageBlocks = dynamic_pointer_cast<RandomSelectLevelUp>(obj);
			if (stageBlocks)
			{
				auto ControllerKeyFlg = stageBlocks->GetControllerSprite();
				if (!ControllerKeyFlg) {
					GetStage()->RemoveGameObject<LevelUpSprites>(GetThis<LevelUpSprites>());
				}
			}
		}
	} // end OnUpdate
}