﻿#pragma once

class CameraBase;

class Character : public KdGameObject
{
public:
	Character() {}
	virtual ~Character()	override {}

	void Init()				override;
	void Update()			override;
	void DrawLit()			override;

	void SetCamera(const std::shared_ptr<CameraBase>& camera){ m_wpCamera = camera; }

private:

	void UpdateRotate(const Math::Vector3& _srcMoveVec);

	std::shared_ptr<KdSquarePolygon>	m_spPoly	= nullptr;
	std::weak_ptr<CameraBase> m_wpCamera;

	Math::Vector3 m_WorldRot = Math::Vector3::Zero;		//世界に対して自身が向いている方向
};