/*
 * \file GraphicsHydraxRttListener.cpp
 *
 *  Created on: \date 26 aožt 2014
 *      Author: \author joda
 *  \brief :
 */
#include "GraphicsHydraxRttListener.h"

namespace Engine {

GraphicsHydraxRttListener::GraphicsHydraxRttListener(SkyX::SkyX* mSkyX,Hydrax::Hydrax* mHydrax) {
	this->mSkyX = mSkyX;
	this->mHydrax = mHydrax;

}

GraphicsHydraxRttListener::~GraphicsHydraxRttListener() {
	// TODO Auto-generated destructor stub
}

void GraphicsHydraxRttListener::preRenderTargetUpdate(const Hydrax::RttManager::RttType& Rtt)
{
	// If needed in any case...
	bool underwater = mHydrax->_isCurrentFrameUnderwater();

	switch (Rtt)
	{
		case Hydrax::RttManager::RTT_REFLECTION:
		{
			// No stars in the reflection map
			mSkyX->setStarfieldEnabled(false);
		}
		break;

		case Hydrax::RttManager::RTT_REFRACTION:
		{
		}
		break;

		case Hydrax::RttManager::RTT_DEPTH: case Hydrax::RttManager::RTT_DEPTH_REFLECTION:
		{
			// Hide SkyX components in depth maps
			mSkyX->getMeshManager()->getEntity()->setVisible(false);
			mSkyX->getMoonManager()->getMoonBillboard()->setVisible(false);
		}
		break;
		default:
		break;

	}
}

void GraphicsHydraxRttListener::postRenderTargetUpdate(const Hydrax::RttManager::RttType& Rtt)
{
	bool underwater = mHydrax->_isCurrentFrameUnderwater();

	switch (Rtt)
	{
		case Hydrax::RttManager::RTT_REFLECTION:
		{
			mSkyX->setStarfieldEnabled(true);
		}
		break;

		case Hydrax::RttManager::RTT_REFRACTION:
		{
		}
		break;

		case Hydrax::RttManager::RTT_DEPTH: case Hydrax::RttManager::RTT_DEPTH_REFLECTION:
		{
			mSkyX->getMeshManager()->getEntity()->setVisible(true);
			mSkyX->getMoonManager()->getMoonBillboard()->setVisible(true);
		}
		break;
		default:
		break;
	}
}

} /* namespace Engine */
