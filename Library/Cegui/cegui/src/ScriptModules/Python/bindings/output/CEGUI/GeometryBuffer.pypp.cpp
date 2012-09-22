// This file has been generated by Py++.

#include "boost/python.hpp"
#include "python_CEGUI.h"
#include "GeometryBuffer.pypp.hpp"

namespace bp = boost::python;

struct GeometryBuffer_wrapper : CEGUI::GeometryBuffer, bp::wrapper< CEGUI::GeometryBuffer > {

    GeometryBuffer_wrapper( )
    : CEGUI::GeometryBuffer( )
      , bp::wrapper< CEGUI::GeometryBuffer >(){
        // null constructor
    
    }

    virtual void appendGeometry( ::CEGUI::Vertex const * const vbuff, ::CEGUI::uint vertex_count ){
        bp::override func_appendGeometry = this->get_override( "appendGeometry" );
        func_appendGeometry( vbuff, vertex_count );
    }

    virtual void appendVertex( ::CEGUI::Vertex const & vertex ){
        bp::override func_appendVertex = this->get_override( "appendVertex" );
        func_appendVertex( boost::ref(vertex) );
    }

    virtual void draw(  ) const {
        bp::override func_draw = this->get_override( "draw" );
        func_draw(  );
    }

    virtual ::CEGUI::Texture * getActiveTexture(  ) const {
        bp::override func_getActiveTexture = this->get_override( "getActiveTexture" );
        return func_getActiveTexture(  );
    }

    virtual ::CEGUI::uint getBatchCount(  ) const {
        bp::override func_getBatchCount = this->get_override( "getBatchCount" );
        return func_getBatchCount(  );
    }

    virtual ::CEGUI::BlendMode getBlendMode(  ) const  {
        if( bp::override func_getBlendMode = this->get_override( "getBlendMode" ) )
            return func_getBlendMode(  );
        else{
            return this->CEGUI::GeometryBuffer::getBlendMode(  );
        }
    }
    
    ::CEGUI::BlendMode default_getBlendMode(  ) const  {
        return CEGUI::GeometryBuffer::getBlendMode( );
    }

    virtual ::CEGUI::RenderEffect * getRenderEffect(  ){
        bp::override func_getRenderEffect = this->get_override( "getRenderEffect" );
        return func_getRenderEffect(  );
    }

    virtual ::CEGUI::uint getVertexCount(  ) const {
        bp::override func_getVertexCount = this->get_override( "getVertexCount" );
        return func_getVertexCount(  );
    }

    virtual bool isClippingActive(  ) const {
        bp::override func_isClippingActive = this->get_override( "isClippingActive" );
        return func_isClippingActive(  );
    }

    virtual void reset(  ){
        bp::override func_reset = this->get_override( "reset" );
        func_reset(  );
    }

    virtual void setActiveTexture( ::CEGUI::Texture * texture ){
        bp::override func_setActiveTexture = this->get_override( "setActiveTexture" );
        func_setActiveTexture( boost::python::ptr(texture) );
    }

    virtual void setBlendMode( ::CEGUI::BlendMode const mode ) {
        if( bp::override func_setBlendMode = this->get_override( "setBlendMode" ) )
            func_setBlendMode( mode );
        else{
            this->CEGUI::GeometryBuffer::setBlendMode( mode );
        }
    }
    
    void default_setBlendMode( ::CEGUI::BlendMode const mode ) {
        CEGUI::GeometryBuffer::setBlendMode( mode );
    }

    virtual void setClippingActive( bool const active ){
        bp::override func_setClippingActive = this->get_override( "setClippingActive" );
        func_setClippingActive( active );
    }

    virtual void setClippingRegion( ::CEGUI::Rectf const & region ){
        bp::override func_setClippingRegion = this->get_override( "setClippingRegion" );
        func_setClippingRegion( boost::ref(region) );
    }

    virtual void setPivot( ::CEGUI::Vector3f const & p ){
        bp::override func_setPivot = this->get_override( "setPivot" );
        func_setPivot( boost::ref(p) );
    }

    virtual void setRenderEffect( ::CEGUI::RenderEffect * effect ){
        bp::override func_setRenderEffect = this->get_override( "setRenderEffect" );
        func_setRenderEffect( boost::python::ptr(effect) );
    }

    virtual void setRotation( ::CEGUI::Quaternion const & r ){
        bp::override func_setRotation = this->get_override( "setRotation" );
        func_setRotation( boost::ref(r) );
    }

    virtual void setTranslation( ::CEGUI::Vector3f const & v ){
        bp::override func_setTranslation = this->get_override( "setTranslation" );
        func_setTranslation( boost::ref(v) );
    }

};

void register_GeometryBuffer_class(){

    { //::CEGUI::GeometryBuffer
        typedef bp::class_< GeometryBuffer_wrapper, boost::noncopyable > GeometryBuffer_exposer_t;
        GeometryBuffer_exposer_t GeometryBuffer_exposer = GeometryBuffer_exposer_t( "GeometryBuffer", bp::no_init );
        bp::scope GeometryBuffer_scope( GeometryBuffer_exposer );
        GeometryBuffer_exposer.def( bp::init< >("! Constructor.\n") );
        { //::CEGUI::GeometryBuffer::appendGeometry
        
            typedef void ( ::CEGUI::GeometryBuffer::*appendGeometry_function_type )( ::CEGUI::Vertex const * const,::CEGUI::uint ) ;
            
            GeometryBuffer_exposer.def( 
                "appendGeometry"
                , bp::pure_virtual( appendGeometry_function_type(&::CEGUI::GeometryBuffer::appendGeometry) )
                , ( bp::arg("vbuff"), bp::arg("vertex_count") )
                , "*!\n\
                \n\
                    Append a number of vertices from an array to the GeometryBuffer.\n\
            \n\
                @param vbuff\n\
                    Pointer to an array of Vertex objects that describe the vertices that\n\
                    are to be added to the GeometryBuffer.\n\
            \n\
                @param vertex_count\n\
                    The number of Vertex objects from the array  vbuff that are to be\n\
                    added to the GeometryBuffer.\n\
                *\n" );
        
        }
        { //::CEGUI::GeometryBuffer::appendVertex
        
            typedef void ( ::CEGUI::GeometryBuffer::*appendVertex_function_type )( ::CEGUI::Vertex const & ) ;
            
            GeometryBuffer_exposer.def( 
                "appendVertex"
                , bp::pure_virtual( appendVertex_function_type(&::CEGUI::GeometryBuffer::appendVertex) )
                , ( bp::arg("vertex") )
                , "*!\n\
                \n\
                    Append a single vertex to the buffer.\n\
            \n\
                @param vertex\n\
                    Vertex object describing the vertex to be added to the GeometryBuffer.\n\
                *\n" );
        
        }
        { //::CEGUI::GeometryBuffer::draw
        
            typedef void ( ::CEGUI::GeometryBuffer::*draw_function_type )(  ) const;
            
            GeometryBuffer_exposer.def( 
                "draw"
                , bp::pure_virtual( draw_function_type(&::CEGUI::GeometryBuffer::draw) )
                , "*!\n\
            \n\
                Draw the geometry buffered within this GeometryBuffer object.\n\
            *\n" );
        
        }
        { //::CEGUI::GeometryBuffer::getActiveTexture
        
            typedef ::CEGUI::Texture * ( ::CEGUI::GeometryBuffer::*getActiveTexture_function_type )(  ) const;
            
            GeometryBuffer_exposer.def( 
                "getActiveTexture"
                , bp::pure_virtual( getActiveTexture_function_type(&::CEGUI::GeometryBuffer::getActiveTexture) )
                , bp::return_value_policy< bp::reference_existing_object >()
                , "*!\n\
                \n\
                    Return a pointer to the currently active Texture object.  This may\n\
                    return 0 if no texture is set.\n\
            \n\
                @return\n\
                    Pointer the Texture object that is currently active, or 0 if texturing\n\
                    is not being used.\n\
                *\n" );
        
        }
        { //::CEGUI::GeometryBuffer::getBatchCount
        
            typedef ::CEGUI::uint ( ::CEGUI::GeometryBuffer::*getBatchCount_function_type )(  ) const;
            
            GeometryBuffer_exposer.def( 
                "getBatchCount"
                , bp::pure_virtual( getBatchCount_function_type(&::CEGUI::GeometryBuffer::getBatchCount) )
                , "*!\n\
                \n\
                    Return the number of batches of geometry that this GeometryBuffer has\n\
                    split the vertices into.\n\
            \n\
                \note\n\
                    How batching is done will be largely implementation specific, although\n\
                    it would be reasonable to expect that you will have <em>at least<em>\n\
                    one batch of geometry per texture switch.\n\
            \n\
                @return\n\
                    The number of batches of geometry held by the GeometryBuffer.\n\
                *\n" );
        
        }
        { //::CEGUI::GeometryBuffer::getBlendMode
        
            typedef ::CEGUI::BlendMode ( ::CEGUI::GeometryBuffer::*getBlendMode_function_type )(  ) const;
            typedef ::CEGUI::BlendMode ( GeometryBuffer_wrapper::*default_getBlendMode_function_type )(  ) const;
            
            GeometryBuffer_exposer.def( 
                "getBlendMode"
                , getBlendMode_function_type(&::CEGUI::GeometryBuffer::getBlendMode)
                , default_getBlendMode_function_type(&GeometryBuffer_wrapper::default_getBlendMode) );
        
        }
        { //::CEGUI::GeometryBuffer::getRenderEffect
        
            typedef ::CEGUI::RenderEffect * ( ::CEGUI::GeometryBuffer::*getRenderEffect_function_type )(  ) ;
            
            GeometryBuffer_exposer.def( 
                "getRenderEffect"
                , bp::pure_virtual( getRenderEffect_function_type(&::CEGUI::GeometryBuffer::getRenderEffect) )
                , bp::return_value_policy< bp::reference_existing_object >()
                , "*!\n\
            \n\
                Return the RenderEffect object that is assigned to this GeometryBuffer\n\
                or 0 if none.\n\
            *\n" );
        
        }
        { //::CEGUI::GeometryBuffer::getVertexCount
        
            typedef ::CEGUI::uint ( ::CEGUI::GeometryBuffer::*getVertexCount_function_type )(  ) const;
            
            GeometryBuffer_exposer.def( 
                "getVertexCount"
                , bp::pure_virtual( getVertexCount_function_type(&::CEGUI::GeometryBuffer::getVertexCount) )
                , "*!\n\
                \n\
                    Return the total number of vertices currently held by this\n\
                    GeometryBuffer object.\n\
            \n\
                @return\n\
                    The number of vertices that have been appended to this GeometryBuffer.\n\
                *\n" );
        
        }
        { //::CEGUI::GeometryBuffer::isClippingActive
        
            typedef bool ( ::CEGUI::GeometryBuffer::*isClippingActive_function_type )(  ) const;
            
            GeometryBuffer_exposer.def( 
                "isClippingActive"
                , bp::pure_virtual( isClippingActive_function_type(&::CEGUI::GeometryBuffer::isClippingActive) )
                , "*\n\
                \n\
                    Return whether clipping will be used for the current batch\n\
                    of vertices being defined.\n\
            \n\
                @return\n\
                    - true if vertices subsequently added to the GeometryBuffer will\n\
                      be clipped to the clipping region defined for this GeometryBuffer.\n\
                    - false if vertices subsequently added will not be clippled (other than\n\
                      to the edges of the rendering target).\n\
                *\n" );
        
        }
        { //::CEGUI::GeometryBuffer::reset
        
            typedef void ( ::CEGUI::GeometryBuffer::*reset_function_type )(  ) ;
            
            GeometryBuffer_exposer.def( 
                "reset"
                , bp::pure_virtual( reset_function_type(&::CEGUI::GeometryBuffer::reset) )
                , "*!\n\
            \n\
                Clear all buffered data and reset the GeometryBuffer to the default\n\
                state.\n\
            *\n" );
        
        }
        { //::CEGUI::GeometryBuffer::setActiveTexture
        
            typedef void ( ::CEGUI::GeometryBuffer::*setActiveTexture_function_type )( ::CEGUI::Texture * ) ;
            
            GeometryBuffer_exposer.def( 
                "setActiveTexture"
                , bp::pure_virtual( setActiveTexture_function_type(&::CEGUI::GeometryBuffer::setActiveTexture) )
                , ( bp::arg("texture") )
                , "*!\n\
                \n\
                    Set the active texture to be used with all subsequently added vertices.\n\
            \n\
                @param texture\n\
                    Pointer to a Texture object that shall be used for subsequently added\n\
                    vertices.  This may be 0, in which case texturing will be disabled for\n\
                    subsequently added vertices.\n\
                *\n" );
        
        }
        { //::CEGUI::GeometryBuffer::setBlendMode
        
            typedef void ( ::CEGUI::GeometryBuffer::*setBlendMode_function_type )( ::CEGUI::BlendMode const ) ;
            typedef void ( GeometryBuffer_wrapper::*default_setBlendMode_function_type )( ::CEGUI::BlendMode const ) ;
            
            GeometryBuffer_exposer.def( 
                "setBlendMode"
                , setBlendMode_function_type(&::CEGUI::GeometryBuffer::setBlendMode)
                , default_setBlendMode_function_type(&GeometryBuffer_wrapper::default_setBlendMode)
                , ( bp::arg("mode") ) );
        
        }
        { //::CEGUI::GeometryBuffer::setClippingActive
        
            typedef void ( ::CEGUI::GeometryBuffer::*setClippingActive_function_type )( bool const ) ;
            
            GeometryBuffer_exposer.def( 
                "setClippingActive"
                , bp::pure_virtual( setClippingActive_function_type(&::CEGUI::GeometryBuffer::setClippingActive) )
                , ( bp::arg("active") )
                , "*!\n\
                \n\
                    Set whether clipping will be active for subsequently added vertices.\n\
            \n\
                @param active\n\
                    - true if vertices added after this call should be clipped to the\n\
                      clipping region defined for this GeometryBuffer.\n\
                    - false if vertices added after this call should not be clipped\n\
                      (other than to the edges of rendering target.\n\
                *\n" );
        
        }
        { //::CEGUI::GeometryBuffer::setClippingRegion
        
            typedef void ( ::CEGUI::GeometryBuffer::*setClippingRegion_function_type )( ::CEGUI::Rectf const & ) ;
            
            GeometryBuffer_exposer.def( 
                "setClippingRegion"
                , bp::pure_virtual( setClippingRegion_function_type(&::CEGUI::GeometryBuffer::setClippingRegion) )
                , ( bp::arg("region") )
                , "*!\n\
            \n\
                Set the clipping region to be used when rendering this buffer.\n\
            *\n" );
        
        }
        { //::CEGUI::GeometryBuffer::setPivot
        
            typedef void ( ::CEGUI::GeometryBuffer::*setPivot_function_type )( ::CEGUI::Vector3f const & ) ;
            
            GeometryBuffer_exposer.def( 
                "setPivot"
                , bp::pure_virtual( setPivot_function_type(&::CEGUI::GeometryBuffer::setPivot) )
                , ( bp::arg("p") )
                , "*!\n\
                \n\
                    Set the pivot point to be used when applying the rotations.\n\
            \n\
                @param p\n\
                    Vector3 describing the location of the pivot point to be used when\n\
                    applying the rotation to the geometry.\n\
                *\n" );
        
        }
        { //::CEGUI::GeometryBuffer::setRenderEffect
        
            typedef void ( ::CEGUI::GeometryBuffer::*setRenderEffect_function_type )( ::CEGUI::RenderEffect * ) ;
            
            GeometryBuffer_exposer.def( 
                "setRenderEffect"
                , bp::pure_virtual( setRenderEffect_function_type(&::CEGUI::GeometryBuffer::setRenderEffect) )
                , ( bp::arg("effect") )
                , "*!\n\
                \n\
                    Set the RenderEffect to be used by this GeometryBuffer.\n\
            \n\
                @param effect\n\
                    Pointer to the RenderEffect to be used during renderng of the\n\
                    GeometryBuffer.  May be 0 to remove a previously added RenderEffect.\n\
            \n\
                \note\n\
                    When adding a RenderEffect, the GeometryBuffer <em>does not<em> take\n\
                    ownership of, nor make a copy of, the passed RenderEffect - this means\n\
                    you need to be careful not to delete the RenderEffect if it might still\n\
                    be in use!\n\
                *\n" );
        
        }
        { //::CEGUI::GeometryBuffer::setRotation
        
            typedef void ( ::CEGUI::GeometryBuffer::*setRotation_function_type )( ::CEGUI::Quaternion const & ) ;
            
            GeometryBuffer_exposer.def( 
                "setRotation"
                , bp::pure_virtual( setRotation_function_type(&::CEGUI::GeometryBuffer::setRotation) )
                , ( bp::arg("r") )
                , "*!\n\
                \n\
                    Set the rotations to be applied to the geometry in the buffer when it is\n\
                    subsequently rendered.\n\
            \n\
                @param r\n\
                    Quaternion describing the rotation to be used.\n\
                *\n" );
        
        }
        { //::CEGUI::GeometryBuffer::setTranslation
        
            typedef void ( ::CEGUI::GeometryBuffer::*setTranslation_function_type )( ::CEGUI::Vector3f const & ) ;
            
            GeometryBuffer_exposer.def( 
                "setTranslation"
                , bp::pure_virtual( setTranslation_function_type(&::CEGUI::GeometryBuffer::setTranslation) )
                , ( bp::arg("v") )
                , "*!\n\
                \n\
                    Set the translation to be applied to the geometry in the buffer when it\n\
                    is subsequently rendered.\n\
            \n\
                @param v\n\
                    Vector3 describing the three axis translation vector to be used.\n\
                *\n" );
        
        }
    }

}
