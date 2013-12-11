// This file has been generated by Py++.

#include "boost/python.hpp"
#include "python_CEGUI.h"
#include "Renderer.pypp.hpp"

namespace bp = boost::python;

struct Renderer_wrapper : CEGUI::Renderer, bp::wrapper< CEGUI::Renderer > {

    Renderer_wrapper()
    : CEGUI::Renderer()
      , bp::wrapper< CEGUI::Renderer >(){
        // null constructor
        
    }

    virtual void beginRendering(  ){
        bp::override func_beginRendering = this->get_override( "beginRendering" );
        func_beginRendering(  );
    }

    virtual ::CEGUI::GeometryBuffer & createGeometryBuffer(  ){
        throw std::logic_error("warning W1049: This method could not be overriden in Python - method returns reference to local variable!");
    }

    virtual ::CEGUI::Texture & createTexture( ::CEGUI::String const & name ){
        throw std::logic_error("warning W1049: This method could not be overriden in Python - method returns reference to local variable!");
    }

    virtual ::CEGUI::Texture & createTexture( ::CEGUI::String const & name, ::CEGUI::String const & filename, ::CEGUI::String const & resourceGroup ){
        throw std::logic_error("warning W1049: This method could not be overriden in Python - method returns reference to local variable!");
    }

    virtual ::CEGUI::Texture & createTexture( ::CEGUI::String const & name, ::CEGUI::Sizef const & size ){
        throw std::logic_error("warning W1049: This method could not be overriden in Python - method returns reference to local variable!");
    }

    virtual ::CEGUI::TextureTarget * createTextureTarget(  ){
        bp::override func_createTextureTarget = this->get_override( "createTextureTarget" );
        return func_createTextureTarget(  );
    }

    virtual void destroyAllGeometryBuffers(  ){
        bp::override func_destroyAllGeometryBuffers = this->get_override( "destroyAllGeometryBuffers" );
        func_destroyAllGeometryBuffers(  );
    }

    virtual void destroyAllTextureTargets(  ){
        bp::override func_destroyAllTextureTargets = this->get_override( "destroyAllTextureTargets" );
        func_destroyAllTextureTargets(  );
    }

    virtual void destroyAllTextures(  ){
        bp::override func_destroyAllTextures = this->get_override( "destroyAllTextures" );
        func_destroyAllTextures(  );
    }

    virtual void destroyGeometryBuffer( ::CEGUI::GeometryBuffer const & buffer ){
        bp::override func_destroyGeometryBuffer = this->get_override( "destroyGeometryBuffer" );
        func_destroyGeometryBuffer( boost::ref(buffer) );
    }

    virtual void destroyTexture( ::CEGUI::Texture & texture ){
        bp::override func_destroyTexture = this->get_override( "destroyTexture" );
        func_destroyTexture( boost::ref(texture) );
    }

    virtual void destroyTexture( ::CEGUI::String const & name ){
        bp::override func_destroyTexture = this->get_override( "destroyTexture" );
        func_destroyTexture( boost::ref(name) );
    }

    virtual void destroyTextureTarget( ::CEGUI::TextureTarget * target ){
        bp::override func_destroyTextureTarget = this->get_override( "destroyTextureTarget" );
        func_destroyTextureTarget( boost::python::ptr(target) );
    }

    virtual void endRendering(  ){
        bp::override func_endRendering = this->get_override( "endRendering" );
        func_endRendering(  );
    }

    virtual ::CEGUI::RenderTarget & getDefaultRenderTarget(  ){
        throw std::logic_error("warning W1049: This method could not be overriden in Python - method returns reference to local variable!");
    }

    virtual ::CEGUI::Vector2f const & getDisplayDPI(  ) const {
        throw std::logic_error("warning W1049: This method could not be overriden in Python - method returns reference to local variable!");
    }

    virtual ::CEGUI::Sizef const & getDisplaySize(  ) const {
        throw std::logic_error("warning W1049: This method could not be overriden in Python - method returns reference to local variable!");
    }

    virtual ::CEGUI::String const & getIdentifierString(  ) const {
        throw std::logic_error("warning W1049: This method could not be overriden in Python - method returns reference to local variable!");
    }

    virtual ::CEGUI::uint getMaxTextureSize(  ) const {
        bp::override func_getMaxTextureSize = this->get_override( "getMaxTextureSize" );
        return func_getMaxTextureSize(  );
    }

    virtual ::CEGUI::Texture & getTexture( ::CEGUI::String const & name ) const {
        throw std::logic_error("warning W1049: This method could not be overriden in Python - method returns reference to local variable!");
    }

    virtual bool isTextureDefined( ::CEGUI::String const & name ) const {
        bp::override func_isTextureDefined = this->get_override( "isTextureDefined" );
        return func_isTextureDefined( boost::ref(name) );
    }

    virtual void setDisplaySize( ::CEGUI::Sizef const & size ){
        bp::override func_setDisplaySize = this->get_override( "setDisplaySize" );
        func_setDisplaySize( boost::ref(size) );
    }

};

void register_Renderer_class(){

    { //::CEGUI::Renderer
        typedef bp::class_< Renderer_wrapper, boost::noncopyable > Renderer_exposer_t;
        Renderer_exposer_t Renderer_exposer = Renderer_exposer_t( "Renderer" );
        bp::scope Renderer_scope( Renderer_exposer );
        { //::CEGUI::Renderer::beginRendering
        
            typedef void ( ::CEGUI::Renderer::*beginRendering_function_type )(  ) ;
            
            Renderer_exposer.def( 
                "beginRendering"
                , bp::pure_virtual( beginRendering_function_type(&::CEGUI::Renderer::beginRendering) )
                , "*!\n\
            \n\
                Perform any operations required to put the system into a state ready\n\
                for rendering operations to begin.\n\
            *\n" );
        
        }
        { //::CEGUI::Renderer::createGeometryBuffer
        
            typedef ::CEGUI::GeometryBuffer & ( ::CEGUI::Renderer::*createGeometryBuffer_function_type )(  ) ;
            
            Renderer_exposer.def( 
                "createGeometryBuffer"
                , bp::pure_virtual( createGeometryBuffer_function_type(&::CEGUI::Renderer::createGeometryBuffer) )
                , bp::return_value_policy< bp::reference_existing_object >()
                , "*!\n\
                \n\
                    Create a new GeometryBuffer and return a reference to it.  You should\n\
                    remove the GeometryBuffer from any RenderQueues and call\n\
                    destroyGeometryBuffer when you want to destroy the GeometryBuffer.\n\
            \n\
                @return\n\
                    GeometryBuffer object.\n\
                *\n" );
        
        }
        { //::CEGUI::Renderer::createTexture
        
            typedef ::CEGUI::Texture & ( ::CEGUI::Renderer::*createTexture_function_type )( ::CEGUI::String const & ) ;
            
            Renderer_exposer.def( 
                "createTexture"
                , bp::pure_virtual( createTexture_function_type(&::CEGUI::Renderer::createTexture) )
                , ( bp::arg("name") )
                , bp::return_value_policy< bp::reference_existing_object >()
                , "*!\n\
                \n\
                    Create a 'null' Texture object.\n\
            \n\
                @param name\n\
                    String holding the name for the new texture.  Texture names must be\n\
                    unique within the Renderer.\n\
            \n\
                @return\n\
                    A newly created Texture object.  The returned Texture object has no size\n\
                    or imagery associated with it.\n\
            \n\
                @exceptions\n\
                    - AlreadyExistsException - thrown if a Texture object named  name\n\
                      already exists within the system.\n\
                *\n" );
        
        }
        { //::CEGUI::Renderer::createTexture
        
            typedef ::CEGUI::Texture & ( ::CEGUI::Renderer::*createTexture_function_type )( ::CEGUI::String const &,::CEGUI::String const &,::CEGUI::String const & ) ;
            
            Renderer_exposer.def( 
                "createTexture"
                , bp::pure_virtual( createTexture_function_type(&::CEGUI::Renderer::createTexture) )
                , ( bp::arg("name"), bp::arg("filename"), bp::arg("resourceGroup") )
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::CEGUI::Renderer::createTexture
        
            typedef ::CEGUI::Texture & ( ::CEGUI::Renderer::*createTexture_function_type )( ::CEGUI::String const &,::CEGUI::Sizef const & ) ;
            
            Renderer_exposer.def( 
                "createTexture"
                , bp::pure_virtual( createTexture_function_type(&::CEGUI::Renderer::createTexture) )
                , ( bp::arg("name"), bp::arg("size") )
                , bp::return_value_policy< bp::reference_existing_object >()
                , "*!\n\
                \n\
                    Create a Texture object with the given pixel dimensions as specified by\n\
                     size.\n\
            \n\
                @param name\n\
                    String holding the name for the new texture.  Texture names must be\n\
                    unique within the Renderer.\n\
            \n\
                @param size\n\
                    Size object that describes the desired texture size.\n\
            \n\
                @return\n\
                    A newly created Texture object.  The initial contents of the texture\n\
                    memory is undefined.\n\
            \n\
                \note\n\
                    Due to possible limitations of the underlying hardware, API or engine,\n\
                    the final size of the texture may not match the requested size.  You can\n\
                    check the ultimate sizes by querying the Texture object after creation.\n\
            \n\
                @exceptions\n\
                    - AlreadyExistsException - thrown if a Texture object named  name\n\
                      already exists within the system.\n\
                *\n" );
        
        }
        { //::CEGUI::Renderer::createTextureTarget
        
            typedef ::CEGUI::TextureTarget * ( ::CEGUI::Renderer::*createTextureTarget_function_type )(  ) ;
            
            Renderer_exposer.def( 
                "createTextureTarget"
                , bp::pure_virtual( createTextureTarget_function_type(&::CEGUI::Renderer::createTextureTarget) )
                , bp::return_value_policy< bp::reference_existing_object >()
                , "*!\n\
                \n\
                    Create a TextureTarget that can be used to cache imagery; this is a\n\
                    RenderTarget that does not lose it's content from one frame to another.\n\
            \n\
                    If the renderer is unable to offer such a thing, 0 should be returned.\n\
            \n\
                @return\n\
                    Pointer to a TextureTarget object that is suitable for caching imagery,\n\
                    or 0 if the renderer is unable to offer such a thing.\n\
                *\n" );
        
        }
        { //::CEGUI::Renderer::destroyAllGeometryBuffers
        
            typedef void ( ::CEGUI::Renderer::*destroyAllGeometryBuffers_function_type )(  ) ;
            
            Renderer_exposer.def( 
                "destroyAllGeometryBuffers"
                , bp::pure_virtual( destroyAllGeometryBuffers_function_type(&::CEGUI::Renderer::destroyAllGeometryBuffers) )
                , "*!\n\
            \n\
                Destroy all GeometryBuffer objects created by this Renderer.\n\
            *\n" );
        
        }
        { //::CEGUI::Renderer::destroyAllTextureTargets
        
            typedef void ( ::CEGUI::Renderer::*destroyAllTextureTargets_function_type )(  ) ;
            
            Renderer_exposer.def( 
                "destroyAllTextureTargets"
                , bp::pure_virtual( destroyAllTextureTargets_function_type(&::CEGUI::Renderer::destroyAllTextureTargets) )
                , "*!\n\
            \n\
                Destory all TextureTarget objects created by this Renderer.\n\
            *\n" );
        
        }
        { //::CEGUI::Renderer::destroyAllTextures
        
            typedef void ( ::CEGUI::Renderer::*destroyAllTextures_function_type )(  ) ;
            
            Renderer_exposer.def( 
                "destroyAllTextures"
                , bp::pure_virtual( destroyAllTextures_function_type(&::CEGUI::Renderer::destroyAllTextures) )
                , "*!\n\
            \n\
                Destroy all Texture objects created by this Renderer.\n\
            *\n" );
        
        }
        { //::CEGUI::Renderer::destroyGeometryBuffer
        
            typedef void ( ::CEGUI::Renderer::*destroyGeometryBuffer_function_type )( ::CEGUI::GeometryBuffer const & ) ;
            
            Renderer_exposer.def( 
                "destroyGeometryBuffer"
                , bp::pure_virtual( destroyGeometryBuffer_function_type(&::CEGUI::Renderer::destroyGeometryBuffer) )
                , ( bp::arg("buffer") )
                , "*!\n\
                \n\
                    Destroy a GeometryBuffer that was returned when calling the\n\
                    createGeometryBuffer function.  Before destroying any GeometryBuffer\n\
                    you should ensure that it has been removed from any RenderQueue that\n\
                    was using it.\n\
            \n\
                @param buffer\n\
                    The GeometryBuffer object to be destroyed.\n\
                *\n" );
        
        }
        { //::CEGUI::Renderer::destroyTexture
        
            typedef void ( ::CEGUI::Renderer::*destroyTexture_function_type )( ::CEGUI::Texture & ) ;
            
            Renderer_exposer.def( 
                "destroyTexture"
                , bp::pure_virtual( destroyTexture_function_type(&::CEGUI::Renderer::destroyTexture) )
                , ( bp::arg("texture") )
                , "*!\n\
                \n\
                    Destroy a Texture object that was previously created by calling the\n\
                    createTexture functions.\n\
            \n\
                @param texture\n\
                    Texture object to be destroyed.\n\
                *\n" );
        
        }
        { //::CEGUI::Renderer::destroyTexture
        
            typedef void ( ::CEGUI::Renderer::*destroyTexture_function_type )( ::CEGUI::String const & ) ;
            
            Renderer_exposer.def( 
                "destroyTexture"
                , bp::pure_virtual( destroyTexture_function_type(&::CEGUI::Renderer::destroyTexture) )
                , ( bp::arg("name") )
                , "*!\n\
                \n\
                    Destroy a Texture object that was previously created by calling the\n\
                    createTexture functions.\n\
            \n\
                @param name\n\
                    String holding the name of the texture to destroy.\n\
                *\n" );
        
        }
        { //::CEGUI::Renderer::destroyTextureTarget
        
            typedef void ( ::CEGUI::Renderer::*destroyTextureTarget_function_type )( ::CEGUI::TextureTarget * ) ;
            
            Renderer_exposer.def( 
                "destroyTextureTarget"
                , bp::pure_virtual( destroyTextureTarget_function_type(&::CEGUI::Renderer::destroyTextureTarget) )
                , ( bp::arg("target") )
                , "*!\n\
                \n\
                    Function that cleans up TextureTarget objects created with the\n\
                    createTextureTarget function.\n\
            \n\
                @param target\n\
                    A pointer to a TextureTarget object that was previously returned from a\n\
                    call to createTextureTarget.\n\
                *\n" );
        
        }
        { //::CEGUI::Renderer::endRendering
        
            typedef void ( ::CEGUI::Renderer::*endRendering_function_type )(  ) ;
            
            Renderer_exposer.def( 
                "endRendering"
                , bp::pure_virtual( endRendering_function_type(&::CEGUI::Renderer::endRendering) )
                , "*!\n\
            \n\
                Perform any operations required to finalise rendering.\n\
            *\n" );
        
        }
        { //::CEGUI::Renderer::getDefaultRenderTarget
        
            typedef ::CEGUI::RenderTarget & ( ::CEGUI::Renderer::*getDefaultRenderTarget_function_type )(  ) ;
            
            Renderer_exposer.def( 
                "getDefaultRenderTarget"
                , bp::pure_virtual( getDefaultRenderTarget_function_type(&::CEGUI::Renderer::getDefaultRenderTarget) )
                , bp::return_value_policy< bp::reference_existing_object >()
                , "*!\n\
                \n\
                    Returns the default RenderTarget object.  The default render target is\n\
                    is typically one that targets the entire screen (or rendering window).\n\
            \n\
                @return\n\
                    Reference to a RenderTarget object.\n\
                *\n" );
        
        }
        { //::CEGUI::Renderer::getDisplayDPI
        
            typedef ::CEGUI::Vector2f const & ( ::CEGUI::Renderer::*getDisplayDPI_function_type )(  ) const;
            
            Renderer_exposer.def( 
                "getDisplayDPI"
                , bp::pure_virtual( getDisplayDPI_function_type(&::CEGUI::Renderer::getDisplayDPI) )
                , bp::return_value_policy< bp::copy_const_reference >()
                , "*!\n\
                \n\
                    Return the resolution of the display or host window in dots per inch.\n\
            \n\
                @return\n\
                    Vector2 object that describes the resolution of the display or host\n\
                    window in DPI.\n\
                *\n" );
        
        }
        { //::CEGUI::Renderer::getDisplaySize
        
            typedef ::CEGUI::Sizef const & ( ::CEGUI::Renderer::*getDisplaySize_function_type )(  ) const;
            
            Renderer_exposer.def( 
                "getDisplaySize"
                , bp::pure_virtual( getDisplaySize_function_type(&::CEGUI::Renderer::getDisplaySize) )
                , bp::return_value_policy< bp::copy_const_reference >()
                , "*!\n\
                \n\
                    Return the size of the display or host window in pixels.\n\
            \n\
                @return\n\
                    Size object describing the pixel dimesntions of the current display or\n\
                    host window.\n\
                *\n" );
        
        }
        { //::CEGUI::Renderer::getIdentifierString
        
            typedef ::CEGUI::String const & ( ::CEGUI::Renderer::*getIdentifierString_function_type )(  ) const;
            
            Renderer_exposer.def( 
                "getIdentifierString"
                , bp::pure_virtual( getIdentifierString_function_type(&::CEGUI::Renderer::getIdentifierString) )
                , bp::return_value_policy< bp::copy_const_reference >()
                , "*!\n\
                \n\
                    Return identification string for the renderer module.\n\
            \n\
                @return\n\
                    String object holding text that identifies the Renderer in use.\n\
                *\n" );
        
        }
        { //::CEGUI::Renderer::getMaxTextureSize
        
            typedef ::CEGUI::uint ( ::CEGUI::Renderer::*getMaxTextureSize_function_type )(  ) const;
            
            Renderer_exposer.def( 
                "getMaxTextureSize"
                , bp::pure_virtual( getMaxTextureSize_function_type(&::CEGUI::Renderer::getMaxTextureSize) )
                , "*!\n\
                \n\
                    Return the pixel size of the maximum supported texture.\n\
            \n\
                @return\n\
                    Size of the maximum supported texture in pixels.\n\
                *\n" );
        
        }
        { //::CEGUI::Renderer::getTexture
        
            typedef ::CEGUI::Texture & ( ::CEGUI::Renderer::*getTexture_function_type )( ::CEGUI::String const & ) const;
            
            Renderer_exposer.def( 
                "getTexture"
                , bp::pure_virtual( getTexture_function_type(&::CEGUI::Renderer::getTexture) )
                , ( bp::arg("name") )
                , bp::return_value_policy< bp::reference_existing_object >()
                , "*!\n\
                \n\
                    Return a Texture object that was previously created by calling the\n\
                    createTexture functions.\n\
            \n\
                @param name\n\
                    String holding the name of the Texture object to be returned.\n\
            \n\
                @exceptions\n\
                    - UnknownObjectException - thrown if no Texture object named  name\n\
                      exists within the system.\n\
                *\n" );
        
        }
        { //::CEGUI::Renderer::isTextureDefined
        
            typedef bool ( ::CEGUI::Renderer::*isTextureDefined_function_type )( ::CEGUI::String const & ) const;
            
            Renderer_exposer.def( 
                "isTextureDefined"
                , bp::pure_virtual( isTextureDefined_function_type(&::CEGUI::Renderer::isTextureDefined) )
                , ( bp::arg("name") )
                , "! Return whether a texture with the given name exists.\n" );
        
        }
        { //::CEGUI::Renderer::setDisplaySize
        
            typedef void ( ::CEGUI::Renderer::*setDisplaySize_function_type )( ::CEGUI::Sizef const & ) ;
            
            Renderer_exposer.def( 
                "setDisplaySize"
                , bp::pure_virtual( setDisplaySize_function_type(&::CEGUI::Renderer::setDisplaySize) )
                , ( bp::arg("size") )
                , "*!\n\
                \n\
                    Set the size of the display or host window in pixels for this Renderer\n\
                    object.\n\
            \n\
                    This is intended to be called by the System as part of the notification\n\
                    process when display size changes are notified to it via the\n\
                    System.notifyDisplaySizeChanged function.\n\
            \n\
                \note\n\
                    The Renderer implementation should not use this function other than to\n\
                    perform internal state updates on the Renderer and related objects.\n\
            \n\
                @param size\n\
                    Size object describing the dimesions of the current or host window in\n\
                    pixels.\n\
                *\n" );
        
        }
    }

}
