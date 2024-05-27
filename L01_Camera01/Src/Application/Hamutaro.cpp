#include "Hamutaro.h"

Hamu::Hamu()
{
}

Hamu::~Hamu()
{
}

void Hamu::Init()
{
	//ポリゴンの初期化
	m_spPoly = std::make_shared<KdSquarePolygon>();
	m_spPoly->
		SetMaterial("Asset/Data/LessonData/Character/Hamu.png");
	m_spPoly->
		SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
}

void Hamu::Update()
{
	//キャラクターの移動速度
	float moveSpd = 0.1f;
	Math::Vector3 nowPos = m_mWorld.Translation();

	//ベクトル(方向ベクトル)＝必ず「長さ(力)」が１でなければならない
	Math::Vector3 moveVec = Math::Vector3::Zero;
	if (GetKeyState('A') & 0x8000)
	{
		moveVec.x = -5.0f;
	}
	if (GetKeyState('D') & 0x8000)
	{
		moveVec.x = 5.0f;
	}
	if (GetKeyState('W') & 0x8000)
	{
		moveVec.z = 5.0f;
	}
	if (GetKeyState('S') & 0x8000)
	{
		moveVec.z = -5.0f;
	}
	moveVec.Normalize();

	moveVec *= moveSpd;
	nowPos += moveVec;

	//キャラクターのワールド行列を作成
	m_mWorld = Math::Matrix::CreateTranslation(nowPos);
}

void Hamu::DrawLit()
{
	//ポリゴンの描画
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spPoly, m_mWorld);
}
