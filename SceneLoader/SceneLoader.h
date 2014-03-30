#ifndef __SceneLoader_h_
#define __SceneLoader_h_

#include "BaseApplication.h"


class SceneLoader : public BaseApplication
{
public:
    SceneLoader(void);
    virtual ~SceneLoader(void);

protected:
    virtual void createScene(void);

private:
    void defineTerrain(long x, long y);
    void initBlendMaps(Ogre::Terrain* terrain);
    void configureTerrainDefaults(Ogre::Light* light);

    Ogre::TerrainGlobalOptions* mTerrainGlobals;
    Ogre::TerrainGroup* mTerrainGroup;
    bool mTerrainsImported;
    OgreBites::Label* mInfoLabel;
};

#endif // #ifndef __SceneLoader_h_
