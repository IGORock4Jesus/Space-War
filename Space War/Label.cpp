#include "Label.h"



Label::Label()
{
}


Label::~Label()
{
}

void Label::OnInitialize(ECS::Entity * entity)
{
	transform = entity->GetComponent<Transform>();
}
