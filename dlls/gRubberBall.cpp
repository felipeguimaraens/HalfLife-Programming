#include "gRubberBall.h"

LINK_ENTITY_TO_CLASS(rubberball, CRubberBall);

void CRubberBall::Spawn()
{
	ALERT(at_console, "Spawned rubber ball! \n");
	CGrenade::Spawn();
}