/*
 * \file AnimationPersonnage.h
 *
 *  Created on: \date 8 mai 2013
 *      Author: \author joda
 *  \brief :
 */

#ifndef ANIMATIONPERSONNAGE_H_
#define ANIMATIONPERSONNAGE_H_

#include <Ogre.h>
/*
 *
 */

enum AnimID
{
	ANIM_IDLE_BASE,
	ANIM_IDLE_TOP,
	ANIM_RUN_BASE,
	ANIM_RUN_TOP,
	ANIM_HANDS_CLOSED,
	ANIM_HANDS_RELAXED,
	ANIM_DRAW_SWORDS,
	ANIM_SLICE_VERTICAL,
	ANIM_SLICE_HORIZONTAL,
	ANIM_DANCE,
	ANIM_JUMP_START,
	ANIM_JUMP_LOOP,
	ANIM_JUMP_END,
	ANIM_NONE
};


class AnimationPersonnage {
public:
	AnimationPersonnage();
	virtual ~AnimationPersonnage();

	void updateAnimation(Ogre::Real * deltaTime);
	void fadeAnimations(Ogre::Real * deltaTime);

};

#endif /* ANIMATIONPERSONNAGE_H_ */
