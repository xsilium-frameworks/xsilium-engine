/*
 * \file GraphicsSky.h
 *
 *  Created on: \date 25 sept. 2014
 *      Author: \author joda
 *  \brief :
 */
#ifndef GRAPHICSSKY_H_
#define GRAPHICSSKY_H_

namespace Engine {

/*
 *
 */
class GraphicsSky {
public:
	GraphicsSky();
	virtual ~GraphicsSky();

	/** Get the SkyX manager
	 * @return SkyX manager
	 */
	SkyX::SkyX* skyxMgr() const {
		return mSkyX;
	}
	/** Get the SkyX controller
	 * @return SkyX controller
	 */
	SkyX::BasicController* skyxCtrl() const {
		return mSkyXController;
	}

	/** Update method, that must be called every frame.
	 * @param dt Time elapsed between frames (Time
	 * multiplier will be imposed into the function).
	 */
	void update(float dt);

private:
	SkyX::SkyX* mSkyX;
	SkyX::BasicController * mSkyXController;

	/// Water color gradient
	SkyX::ColorGradient mWaterGradient;
	/// Sun color gradient
	SkyX::ColorGradient mSunGradient;
	/// Diffuse color gradient
	SkyX::ColorGradient mDiffuseGradient;
	/// Ambient color gradient
	SkyX::ColorGradient mAmbientGradient;

};

} /* namespace Engine */

#endif /* GRAPHICSSKY_H_ */
