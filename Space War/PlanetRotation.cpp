#include "PlanetRotation.h"



PlanetRotation::PlanetRotation(Transform* transform)
	: transform{ transform }
{
}

void PlanetRotation::Update(float elapsedTime)
{
	transform->SetAngle(elapsedTime * speed + transform->GetAngle());
}

void PlanetRotationSystem::OnComponentUpdate(PlanetRotation * component, float elapsedTime)
{
	component->Update(elapsedTime);
}
