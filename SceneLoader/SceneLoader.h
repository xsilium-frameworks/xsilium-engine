#ifndef __SceneLoader_h_
#define __SceneLoader_h_

#include "BaseApplication.h"
#include "DotSceneLoader.h"

class SceneLoader : public BaseApplication
{
public:
    SceneLoader(void);
    virtual ~SceneLoader(void);

protected:
    virtual void createScene(void);
};

#endif // #ifndef __SceneLoader_h_
