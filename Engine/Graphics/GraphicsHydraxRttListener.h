/*
 * \file GraphicsHydraxRttListener.h
 *
 *  Created on: \date 26 aožt 2014
 *      Author: \author joda
 *  \brief :
 */
#ifndef GRAPHICSHYDRAXRTTLISTENER_H_
#define GRAPHICSHYDRAXRTTLISTENER_H_

// ----------------------------------------------------------------------------
// SkyX plugin
// ----------------------------------------------------------------------------
#include "SkyX.h"

// ----------------------------------------------------------------------------
// Hydrax plugin.
// ----------------------------------------------------------------------------
#include <Hydrax.h>
#include <Noise/FFT/FFT.h>
#include <Noise/Perlin/Perlin.h>
#include <Modules/ProjectedGrid/ProjectedGrid.h>
#include <Modules/RadialGrid/RadialGrid.h>
#include <Modules/SimpleGrid/SimpleGrid.h>


namespace Engine {

/*
 *
 */
class GraphicsHydraxRttListener : public Hydrax::RttManager::RttListener {
public:
	GraphicsHydraxRttListener(/**SkyX::SkyX* mSkyX,*/Hydrax::Hydrax* mHydrax);
	virtual ~GraphicsHydraxRttListener();

	void preRenderTargetUpdate(const Hydrax::RttManager::RttType& Rtt);

	void postRenderTargetUpdate(const Hydrax::RttManager::RttType& Rtt);

private:
//	SkyX::SkyX* mSkyX ;
	Hydrax::Hydrax* mHydrax;
};

} /* namespace Engine */

#endif /* GRAPHICSHYDRAXRTTLISTENER_H_ */
