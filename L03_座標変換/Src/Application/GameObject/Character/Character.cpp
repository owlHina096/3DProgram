#include "Character.h"

void Character::Init()
{
	if (!m_spPoly)
	{
		m_spPoly = std::make_shared<KdSquarePolygon>();
		m_spPoly->SetMaterial("Asset/Data/LessonData/Character/Hamu.png");
		m_spPoly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	}

	m_spriteTex->Load("Asset/Textures/slime_idle.png");
}

void Character::Update()
{
	// キャラクターの移動速度(真似しちゃダメですよ)
	float moveSpd = 0.05f;
	Math::Vector3 nowPos = m_mWorld.Translation();

	Math::Vector3 moveVec = Math::Vector3::Zero;
	if (GetAsyncKeyState('D')) { moveVec.x = 1.0f; }
	if (GetAsyncKeyState('A')) { moveVec.x = -1.0f; }
	if (GetAsyncKeyState('W')) { moveVec.z = 1.0f; }
	if (GetAsyncKeyState('S')) { moveVec.z = -1.0f; }

	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		std::shared_ptr<KdCamera> _camera = m_wpCamera.lock();
		if (_camera)
		{
			POINT point;
			Math::Vector3 pos;
			Math::Vector3 dir;
			float range;
			//3D空間内のnearクリップの座標を計算する
			_camera->GenerateRayInfoFromClientPos(point, pos, dir, range);

			KdCollider::RayInfo ray;
			ray.m_pos = pos;
			ray.m_dir = dir;
			ray.m_range = range;
			ray.m_type = KdCollider::TypeGround;

			std::list<KdCollider::CollisionResult> retRayList;
			for (auto& obj : )
			{

			}
		}
	}

	moveVec.Normalize();
	moveVec *= moveSpd;
	nowPos += moveVec;

	// キャラクターのワールド行列を創る処理
	m_mWorld = Math::Matrix::CreateTranslation(nowPos);
}

void Character::DrawLit()
{
	if (!m_spPoly) return;

	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spPoly, m_mWorld);
}

void Character::DrawSprite()
{
	std::shared_ptr<KdCamera> _camera = m_wpCamera.lock();
	if (_camera)
	{
		Math::Vector3 pos = GetPos();
		Math::Vector3 result = Math::Vector3::Zero;
		_camera->ConvertWorldToScreenDetail(pos, result);

		//KdShaderManager::Instance().m_spriteShader.DrawCircle(result.x, result.y, 10, &kRedColor);

		result.y += 0.5f;
		Math::Rectangle rect = { 0,0,40,40 };
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_spriteTex, result.x, result.y, &rect);
	}
}
