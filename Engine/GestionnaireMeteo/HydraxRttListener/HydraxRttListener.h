/*
 * \file HydraxRttListener.h
 *
 *  Created on: \date 14 févr. 2013
 *      Author: \author joda
 *  \brief :
 */

#ifndef HYDRAXRTTLISTENER_H_
#define HYDRAXRTTLISTENER_H_

#include "SkyX.h"
#include "Hydrax.h"
#include "Noise/Perlin/Perlin.h"
#include "Modules/ProjectedGrid/ProjectedGrid.h"

/*
 *
 */
class HydraxRttListener : public Hydrax::RttManager::RttListener {
public:
	HydraxRttListener(SkyX::SkyX* mSkyX,Hydrax::Hydrax* mHydrax);
	virtual ~HydraxRttListener();

	void preRenderTargetUpdate(const Hydrax::RttManager::RttType& Rtt);

	void postRenderTargetUpdate(const Hydrax::RttManager::RttType& Rtt);

private:
    SkyX::SkyX* mSkyX ;
    Hydrax::Hydrax* mHydrax;

};

#endif /* HYDRAXRTTLISTENER_H_ */
