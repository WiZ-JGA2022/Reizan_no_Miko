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
	LevelUpSprites::LevelUpSprites(const shared_ptr<Stage>& stagePtr,
		const int& textureNum,
		bool trace,
		const Vec2& startScale,
		const Vec2& startPos,
		const int& texNum
	) :
		GameObject(stagePtr),
		m_textureNum(textureNum),
		m_alpha(trace),
		m_defaultScale(startScale),
		m_defaultPos(startPos),
		m_texNum(texNum)
	{}

	wstring LevelUpSprites::ControllerNum(int i) {
		if (i == 0)
		{
			m_textureKey = L"HP_LEVELUP";
			return m_textureKey;
		}
		else if (i == 1)
		{
			m_textureKey = L"ATK_LEVELUP";
			return m_textureKey;

		}
		else if (i == 2)
		{
			m_textureKey = L"DEF_LEVELUP";
			return m_textureKey;

		}
		else if (i == 3)
		{
			m_textureKey = L"SPD_LEVELUP";
			return m_textureKey;

		}
		else if (i == 4)
		{
			m_textureKey = L"HASTE_LEVELUP";
			return m_textureKey;

		}
		else if (i == 5)
		{
			m_textureKey = L"PICKUP_LEVELUP";
			return m_textureKey;

		}
		else if (i == 6)
		{
			m_textureKey = L"WEPON_1_LEVELUP";
			return m_textureKey;

		}
		else if (i == 7)
		{
			m_textureKey = L"WEPON_2_LEVELUP";
			return m_textureKey;
		}
		else
		{

		}
	} // end ControllerNum

	// 初期化
	void LevelUpSprites::OnCreate()
	{
		float HelfSize = m_helfSize;

		// 頂点配列
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
		PtrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, m_alphaNum));
		SetDrawActive(true);
	} // end OnCreate

	// 更新処理
	void LevelUpSprites::OnUpdate() {
		auto& app = App::GetApp();
		auto stage = app->GetScene<Scene>()->GetActiveStage();	// ステージオブジェクトを取得する
		auto objs = stage->GetGameObjectVec();					// ステージに追加されているすべてのオブジェクト
		auto scene = App::GetApp()->GetScene<Scene>();

		// 処理終了後に表示した画像を消す処理
		for (auto& obj : objs)
		{
			// LevelUpButtonへのキャストを試みる
			auto levelUpButton = dynamic_pointer_cast<RandomSelectLevelUpButton>(obj);
			if (levelUpButton)
			{
				auto controllerKeyFlg = levelUpButton->GetEventActive();
				if (!controllerKeyFlg) {
					GetStage()->RemoveGameObject<LevelUpSprites>(GetThis<LevelUpSprites>());
				}
			}
		}
	} // end OnUpdate
}