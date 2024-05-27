#pragma once

class Sun :public KdGameObject
{
public:

	Sun() { Init(); }
	~Sun()override {}

	void Update()override;
	void DrawLit()override;

private:

	void Init()override;

	std::shared_ptr<KdModelData> m_spModel = nullptr;
};