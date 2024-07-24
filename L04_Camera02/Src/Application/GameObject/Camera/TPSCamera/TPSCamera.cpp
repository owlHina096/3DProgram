#include "TPSCamera.h"

void TPSCamera::Init()
{
	//親クラスの初期化を呼び出す
	CameraBase::Init();

	//基準点（ターゲット）からどれだけ離れているか
	m_mLocalPos = Math::Matrix::CreateTranslation(0.f, 1.5f, -10.0f);

	//マウスカーソルを画面中央に固定する
	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);
}

void TPSCamera::Update()
{
	//ターゲットの行列(有効な場合のみ)
	Math::Matrix _targetMat = Math::Matrix::Identity;
	const std::shared_ptr<KdGameObject> _spTarget = m_wpTarget.lock();
	if (_spTarget)
	{
		_targetMat = Math::Matrix::CreateTranslation(_spTarget->GetPos());
	}

	//カメラの回転処理
	UpdateRotateByMouse();
	m_mRotation = GetRotationMatrix();
	//移動した後に回転させる
	m_mWorld = m_mLocalPos * m_mRotation * _targetMat;

	KdCollider::RayInfo _ray;
	//レイの発射位置
	_ray.m_pos = GetPos();
	//レイの発射方向
	_ray.m_dir = Math::Vector3::Down;
	//レイの長さ
	_ray.m_range = 1000.0f;
	//レイの当たり判定を行うタイプの設定
	_ray.m_type = KdCollider::TypeGround;

	if (_spTarget)
	{
		Math::Vector3 _targetPos = _spTarget->GetPos();
		_targetPos.y += 0.5f;
		_ray.m_dir = _targetPos - GetPos();
		_ray.m_range = _ray.m_dir.Length();
		_ray.m_dir.Normalize();
	}

	//当たり判定を行う全てのオブジェクトに総当たり
	for (std::weak_ptr<KdGameObject> wpGameObj : m_wpHitObjectList)
	{
		std::shared_ptr<KdGameObject> _spGameObj = wpGameObj.lock();
		if (_spGameObj)
		{
			std::list<KdCollider::CollisionResult> _retResultList;
			_spGameObj->Intersects(_ray, &_retResultList);

			//レイに当たったリストから一番近いオブジェクトを検出
			float _maxOverLap = 0;
			Math::Vector3 _hitPos = {};
			bool _isHit = false;
			for (auto& ret : _retResultList)
			{
				if(_maxOverLap < ret.m_overlapDistance)
				{
					_maxOverLap = ret.m_overlapDistance;
					_hitPos = ret.m_hitPos;
					_isHit = true;
				}
			}
			//何かしらの障害物に当たっている
			if (_isHit)
			{
				Math::Vector3 _shiftPos = _hitPos;
				_shiftPos += _ray.m_dir * 0.4f;
				SetPos(_shiftPos);
			}
		}
	}

	//親クラスの更新処理(ワールド行列のセット)を呼び出す
	CameraBase::Update();
}
