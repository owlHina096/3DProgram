#include "Moon.h"

void Moon::Update()
{
	static float deg = 0;
	deg += 5.0f;
	if (deg > 360)
	{
		deg -= 360;
	}
	Math::Matrix _mRotationY =
		Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(deg));

	Math::Vector3 _pos = m_mWorld.Translation();
	Math::Matrix _mEarthTrans =
		Math::Matrix::CreateTranslation(_pos);
	Math::Matrix _mMoonTrans =
		Math::Matrix::CreateTranslation(2, 0, 0);

	//Earthクラスにすべて移すのもあり
	m_mWorld = (_mRotationY * _mMoonTrans) * _mRotationY * _mEarthTrans;
}

void Moon::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}

void Moon::Init()
{
	m_spModel = std::make_shared<KdModelData>();
	m_spModel->Load("Asset/Data/LessonData/Planets/moon.gltf");
}
