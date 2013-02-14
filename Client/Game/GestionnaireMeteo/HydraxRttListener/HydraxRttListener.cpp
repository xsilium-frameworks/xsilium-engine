/*
 * \file HydraxRttListener.cpp
 *
 *  Created on: \date 14 fŽvr. 2013
 *      Author: \author joda
 *  \brief :
 */

#include "HydraxRttListener.h"

HydraxRttListener::HydraxRttListener(SkyX::SkyX* mSkyX,Hydrax::Hydrax* mHydrax) {
	this->mSkyX = mSkyX;
	this->mHydrax = mHydrax;


}

HydraxRttListener::~HydraxRttListener() {
}

void HydraxRttListener::preRenderTargetUpdate(const Hydrax::RttManager::RttType& Rtt)
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
	}
}

void HydraxRttListener::postRenderTargetUpdate(const Hydrax::RttManager::RttType& Rtt)
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
	}
}
