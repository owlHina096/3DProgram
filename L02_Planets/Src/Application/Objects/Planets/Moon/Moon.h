#pragma once

class Moon :public KdGameObject
{
public:

	Moon() { Init(); }
	~Moon()override {}

	void Update();
	void DrawLit()override;

private:

	void Init()override;

	std::shared_ptr<KdModelData> m_spModel = nullptr;
};