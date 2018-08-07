#pragma once

#include "Transform.h"
#include "ECS.h"


class PlanetRotation : public ECS::Component<PlanetRotation>
{
	Transform* transform;
	float speed{ 0.0f };

public:
	PlanetRotation(Transform* transform);

	void Update(float elapsedTime);

	void SetSpeed(float s) { speed = s; }
};


class PlanetRotationSystem : public ECS::System<PlanetRotation>
{
private:
	virtual void OnComponentUpdate(PlanetRotation* component, float elapsedTime) override;
};