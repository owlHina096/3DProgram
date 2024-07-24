#include "CCTVCamera.h"

void CCTVCamera::Init()
{
	CameraBase::Init();

	m_mLocalPos = Math::Matrix::CreateTranslation(Math::Vector3(0, 5.0f, -3.0f));
	m_mWorld = m_mLocalPos;
}

void CCTVCamera::PostUpdate()
{
	Math::Matrix targetMat;
	std::shared_ptr<KdGameObject> wpTarget = m_wpTarget.lock();
	if (wpTarget)
	{
		//対象へのベクトルを求める
		targetMat = Math::Matrix::CreateTranslation(wpTarget->GetPos());
	}

	UpdateLookAtRotate(targetMat.Translation());
}

void CCTVCamera::UpdateLookAtRotate(const Math::Vector3& targetPos)
{
	Math::Matrix _shadowVP =
		DirectX::XMMatrixLookAtLH(GetPos(), targetPos, Math::Vector3::Up);

	m_mWorld = _shadowVP.Invert();

}
