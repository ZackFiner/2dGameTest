#include "heliSprite.h"

heliSprite::heliSprite(entityManager* em, collisionManager* cm) :
	solidEntity(em, cm, collisionHull())
{
	
}