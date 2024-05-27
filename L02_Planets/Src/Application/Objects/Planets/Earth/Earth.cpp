#include "Earth.h"
#include "../Moon/Moon.h"

void Earth::Update()
{
	static float deg = 0;
	deg += 0.5f;
	if (deg > 360)
	{
		deg -= 360;
	}

	Math::Matrix _mRotationY =
		Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(deg));

	Math::Matrix _mTrans =
		Math::Matrix::CreateTranslation(5, 0, 0);

	m_mWorld = (_mRotationY * _mTrans) * _mRotationY;

	m_Moon->SetPos(m_mWorld.Translation());
	m_Moon->Update();
}

void Earth::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
	
	m_Moon->DrawLit();
}

void Earth::Init()
{
	m_spModel = std::make_shared<KdModelData>();
	m_spModel->Load("Asset/Data/LessonData/Planets/earth.gltf");

	m_Moon = std::make_shared<Moon>();
	m_Moon->Init();
}
