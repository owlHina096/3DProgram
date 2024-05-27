#pragma once

class Earth :public KdGameObject
{
public:

	Earth() { Init(); }
	~Earth()override {}

	void Update()override;
	void DrawLit()override;

private:

	void Init()override;

	std::shared_ptr<KdModelData> m_spModel = nullptr;

	std::shared_ptr<KdGameObject> m_Moon;
};