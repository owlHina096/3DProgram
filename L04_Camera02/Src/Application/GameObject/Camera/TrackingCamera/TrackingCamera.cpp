#include "TrackingCamera.h"

void TrackingCamera::Init()
{
	//親クラスの初期化を呼び出す
	CameraBase::Init();

	//基準点（ターゲット）からどれだけ離れているか
	m_mLocalPos = Math::Matrix::CreateTranslation(0, 6.0f, -5.0f);
	//どれだけ傾けているか
	m_mRotation = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(45));
}

void TrackingCamera::Update()
{
	//ターゲットの行列(有効な場合のみ)
	Math::Matrix _targetMat = Math::Matrix::Identity;
	const std::shared_ptr<KdGameObject> _spTarget = m_wpTarget.lock();
	if (_spTarget)
	{
		_targetMat = Math::Matrix::CreateTranslation(_spTarget->GetPos());
	}

	m_mWorld = m_mRotation * m_mLocalPos * _targetMat;

	//親クラスの更新処理(ワールド行列のセット)を呼び出す
	CameraBase::Update();
}
