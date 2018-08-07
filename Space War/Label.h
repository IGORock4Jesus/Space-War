#pragma once

#include "ECS.h"
#include "Transform.h"

class Label : public ECS::Component<Label>
{
	Transform* transform;

public:
	Label();
	~Label();

	virtual void OnInitialize(ECS::Entity* entity) override;
};


class LabelSystem : public ECS::System<Label> {

};
