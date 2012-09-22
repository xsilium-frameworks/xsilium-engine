
#ifndef __BaseApplication_h_
#define __BaseApplication_h_

#include "FrameworkXsilium.h"

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>


class BaseApplication : public FrameworkXsilium
{
public:
    BaseApplication(void);
    virtual ~BaseApplication(void);

protected:
	CEGUI::OgreRenderer* mRenderer;

    virtual void createScene(void);

	virtual void createFrameListener(void);

	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt );

	virtual bool keyPressed( const OIS::KeyEvent &arg );
	virtual bool keyReleased( const OIS::KeyEvent &arg );
	virtual bool mouseMoved( const OIS::MouseEvent &arg );
	virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

	bool quit(const CEGUI::EventArgs &e);
	
};

#endif // #ifndef __BaseApplication_h_
