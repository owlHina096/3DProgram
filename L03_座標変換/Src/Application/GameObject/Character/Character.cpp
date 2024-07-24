#include "Character.h"
#include "../../main.h"

void Character::Init()
{
	if (!m_spPoly)
	{
		m_spPoly = std::make_shared<KdSquarePolygon>();
		m_spPoly->SetMaterial("Asset/Data/LessonData/Character/Hamu.png");
		m_spPoly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	}

	//m_spriteTex.Load("Asset/Textures/slime_idle.png");
}

void Character::Update()
{
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		//①マウス座標を取得する
		POINT _mousePos;
		GetCursorPos(&_mousePos);
		ScreenToClient(Application::Instance().GetWindowHandle(), &_mousePos);

		std::shared_ptr<KdCamera> _camera = m_wpCamera.lock();
		if (_camera)
		{
			//②レイの発射方向を求める
			Math::Vector3 _camPos = _camera->GetCameraMatrix().Translation();	//カメラの座標
			Math::Vector3 _rayDir = Math::Vector3::Zero;	//レイの発射方向
			float _rayRange = 1000.0f;		//レイの長さ
			//3D空間内のnearクリップの座標を計算する
			_camera->GenerateRayInfoFromClientPos(_mousePos, _camPos, _rayDir, _rayRange);

			//③実際にレイを飛ばして衝突位置（オブジェクト）を求める
			const std::shared_ptr<KdGameObject> _terrain = m_wpTerrain.lock();
			if (_terrain)
			{
				//実際の当たり判定の処理
				Math::Vector3 _endRayPos = _camPos + (_rayDir * _rayRange);
				KdCollider::RayInfo _rayInfo(KdCollider::TypeGround, _camPos, _endRayPos, _rayRange);

				std::list<KdCollider::CollisionResult>_results;
				_terrain->Intersects(_rayInfo, &_results);

				//結果が1つでも帰ってきていたら
				if (_results.size())
				{
					for (const KdCollider::CollisionResult& result : _results)
					{
						m_targetPos = result.m_hitPos;
					}
				}
			}
		}
	}

	// キャラクターの移動速度(真似しちゃダメですよ)
	float moveSpd = 0.05f;
	Math::Vector3 nowPos = GetPos();
	Math::Vector3 moveVec = m_targetPos - nowPos;
	
	if (moveVec.Length() <= moveSpd)
	{
		moveSpd = moveVec.Length();
	}

	moveVec.Normalize();
	moveVec *= moveSpd;
	nowPos += moveVec;
	//nowPos = m_targetPos;

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

		//result.y += 0.5f;
		//Math::Rectangle rect = { 0,0,40,40 };
		//KdShaderManager::Instance().m_spriteShader.DrawTex(&m_spriteTex, result.x, result.y, &rect);
	}
}
