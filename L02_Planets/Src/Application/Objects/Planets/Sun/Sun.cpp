#include "Sun.h"

void Sun::Update()
{
	static float deg = 0;
	deg += 0.5f;
	if (deg > 360)
	{
		deg -= 360;
	}

	m_mWorld = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(deg));
}

void Sun::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}

void Sun::Init()
{
	m_spModel = std::make_shared<KdModelData>();
	m_spModel->Load("Asset/Data/LessonData/Planets/sun.gltf");
}
