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
	//1つずつ計算していく方法
	//{
	//	//対象へのベクトルの求める
	//	Math::Vector3 targetDir = targetPos - GetPos();

	//	//対象へのベクトルを角度に変換する
	//	Math::Vector3 degAng;
	//	degAng.y = DirectX::XMConvertToDegrees(atan2(targetDir.x, targetDir.z));
	//	degAng.x = DirectX::XMConvertToDegrees(atan2(targetDir.y, targetDir.z));
	//	//degAng.z = atan2(targetDir.x, targetDir.y);

	//	//求めた角度を行列にする
	//	Math::Matrix rotationX =
	//		Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(degAng.x));
	//	Math::Matrix rotationY =
	//		Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(degAng.y));
	//	m_mRotation = rotationX * rotationY;

	//	m_mWorld = m_mRotation * m_mLocalPos;
	//}

	Math::Matrix _shadowVP =
		DirectX::XMMatrixLookAtLH(GetPos(), targetPos, Math::Vector3::Up);

	m_mWorld = _shadowVP.Invert();
}
