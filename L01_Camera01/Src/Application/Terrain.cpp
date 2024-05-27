#include "Terrain.h"

Terrain::Terrain()
{
}

Terrain::~Terrain()
{
}

void Terrain::Init()
{
	//地形の初期化
	m_spModel = std::make_shared<KdModelData>();
	m_spModel->Load("Asset/Data/LessonData/Terrain/Terrain.gltf");
}

void Terrain::DrawLit()
{
	//地形の描画
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel);
}
