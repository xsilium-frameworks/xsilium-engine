// This file has been generated by Py++.

#include "boost/python.hpp"
#include "python_CEGUI.h"
#include "MouseCursor.pypp.hpp"

namespace bp = boost::python;

struct MouseCursor_wrapper : CEGUI::MouseCursor, bp::wrapper< CEGUI::MouseCursor > {

    MouseCursor_wrapper( )
    : CEGUI::MouseCursor( )
      , bp::wrapper< CEGUI::MouseCursor >(){
        // null constructor
    
    }

    virtual void onDefaultImageChanged( ::CEGUI::MouseCursorEventArgs & e ){
        if( bp::override func_onDefaultImageChanged = this->get_override( "onDefaultImageChanged" ) )
            func_onDefaultImageChanged( boost::ref(e) );
        else{
            this->CEGUI::MouseCursor::onDefaultImageChanged( boost::ref(e) );
        }
    }
    
    virtual void default_onDefaultImageChanged( ::CEGUI::MouseCursorEventArgs & e ){
        CEGUI::MouseCursor::onDefaultImageChanged( boost::ref(e) );
    }

    virtual void onImageChanged( ::CEGUI::MouseCursorEventArgs & e ){
        if( bp::override func_onImageChanged = this->get_override( "onImageChanged" ) )
            func_onImageChanged( boost::ref(e) );
        else{
            this->CEGUI::MouseCursor::onImageChanged( boost::ref(e) );
        }
    }
    
    virtual void default_onImageChanged( ::CEGUI::MouseCursorEventArgs & e ){
        CEGUI::MouseCursor::onImageChanged( boost::ref(e) );
    }

    virtual void fireEvent( ::CEGUI::String const & name, ::CEGUI::EventArgs & args, ::CEGUI::String const & eventNamespace="" ) {
        if( bp::override func_fireEvent = this->get_override( "fireEvent" ) )
            func_fireEvent( boost::ref(name), boost::ref(args), boost::ref(eventNamespace) );
        else{
            this->CEGUI::EventSet::fireEvent( boost::ref(name), boost::ref(args), boost::ref(eventNamespace) );
        }
    }
    
    void default_fireEvent( ::CEGUI::String const & name, ::CEGUI::EventArgs & args, ::CEGUI::String const & eventNamespace="" ) {
        CEGUI::EventSet::fireEvent( boost::ref(name), boost::ref(args), boost::ref(eventNamespace) );
    }

    void fireEvent_impl( ::CEGUI::String const & name, ::CEGUI::EventArgs & args ){
        CEGUI::EventSet::fireEvent_impl( boost::ref(name), boost::ref(args) );
    }

    ::CEGUI::ScriptModule * getScriptModule(  ) const {
        return CEGUI::EventSet::getScriptModule(  );
    }

    virtual ::CEGUI::RefCounted< CEGUI::BoundSlot > subscribeScriptedEvent( ::CEGUI::String const & name, ::CEGUI::String const & subscriber_name ) {
        if( bp::override func_subscribeScriptedEvent = this->get_override( "subscribeScriptedEvent" ) )
            return func_subscribeScriptedEvent( boost::ref(name), boost::ref(subscriber_name) );
        else{
            return this->CEGUI::EventSet::subscribeScriptedEvent( boost::ref(name), boost::ref(subscriber_name) );
        }
    }
    
    ::CEGUI::RefCounted< CEGUI::BoundSlot > default_subscribeScriptedEvent( ::CEGUI::String const & name, ::CEGUI::String const & subscriber_name ) {
        return CEGUI::EventSet::subscribeScriptedEvent( boost::ref(name), boost::ref(subscriber_name) );
    }

    virtual ::CEGUI::RefCounted< CEGUI::BoundSlot > subscribeScriptedEvent( ::CEGUI::String const & name, unsigned int group, ::CEGUI::String const & subscriber_name ) {
        if( bp::override func_subscribeScriptedEvent = this->get_override( "subscribeScriptedEvent" ) )
            return func_subscribeScriptedEvent( boost::ref(name), group, boost::ref(subscriber_name) );
        else{
            return this->CEGUI::EventSet::subscribeScriptedEvent( boost::ref(name), group, boost::ref(subscriber_name) );
        }
    }
    
    ::CEGUI::RefCounted< CEGUI::BoundSlot > default_subscribeScriptedEvent( ::CEGUI::String const & name, unsigned int group, ::CEGUI::String const & subscriber_name ) {
        return CEGUI::EventSet::subscribeScriptedEvent( boost::ref(name), group, boost::ref(subscriber_name) );
    }

};

void register_MouseCursor_class(){

    { //::CEGUI::MouseCursor
        typedef bp::class_< MouseCursor_wrapper, bp::bases< CEGUI::EventSet >, boost::noncopyable > MouseCursor_exposer_t;
        MouseCursor_exposer_t MouseCursor_exposer = MouseCursor_exposer_t( "MouseCursor", bp::init< >("*!\n\
        \n\
           Constructor for MouseCursor objects\n\
        *\n") );
        bp::scope MouseCursor_scope( MouseCursor_exposer );
        { //::CEGUI::MouseCursor::draw
        
            typedef void ( ::CEGUI::MouseCursor::*draw_function_type )(  ) const;
            
            MouseCursor_exposer.def( 
                "draw"
                , draw_function_type( &::CEGUI::MouseCursor::draw )
                , "*!\n\
               \n\
                  Makes the cursor draw itself\n\
            \n\
               @return\n\
                  Nothing\n\
               *\n" );
        
        }
        { //::CEGUI::MouseCursor::getConstraintArea
        
            typedef ::CEGUI::Rectf ( ::CEGUI::MouseCursor::*getConstraintArea_function_type )(  ) const;
            
            MouseCursor_exposer.def( 
                "getConstraintArea"
                , getConstraintArea_function_type( &::CEGUI::MouseCursor::getConstraintArea )
                , "*!\n\
               \n\
                  return the current constraint area of the mouse cursor.\n\
            \n\
               @return\n\
                  Rect object describing the active area that the mouse cursor is constrained to.\n\
               *\n" );
        
        }
        { //::CEGUI::MouseCursor::getDefaultImage
        
            typedef ::CEGUI::Image const * ( ::CEGUI::MouseCursor::*getDefaultImage_function_type )(  ) const;
            
            MouseCursor_exposer.def( 
                "getDefaultImage"
                , getDefaultImage_function_type( &::CEGUI::MouseCursor::getDefaultImage )
                , bp::return_value_policy< bp::reference_existing_object >()
                , "*!\n\
                \n\
                    Return the currently set default mouse cursor image\n\
            \n\
                @return\n\
                    Pointer to the current default image used for the mouse cursor.  May\n\
                    return 0 if default cursor has not been set, or has intentionally\n\
                    been set to 0 - which results in a blank default cursor.\n\
                *\n" );
        
        }
        { //::CEGUI::MouseCursor::getDisplayIndependantPosition
        
            typedef ::CEGUI::Vector2f ( ::CEGUI::MouseCursor::*getDisplayIndependantPosition_function_type )(  ) const;
            
            MouseCursor_exposer.def( 
                "getDisplayIndependantPosition"
                , getDisplayIndependantPosition_function_type( &::CEGUI::MouseCursor::getDisplayIndependantPosition )
                , "*!\n\
               \n\
                  Return the current mouse cursor position as display resolution independant values.\n\
            \n\
               @return\n\
                  Point object describing the current mouse cursor position as resolution independant values\
                  that\n\
                  range from 0.0f to 1.0f, where 0.0f represents the left-most and top-most positions, and\
                  1.0f\n\
                  represents the right-most and bottom-most positions.\n\
               *\n" );
        
        }
        { //::CEGUI::MouseCursor::getExplicitRenderSize
        
            typedef ::CEGUI::Sizef const & ( ::CEGUI::MouseCursor::*getExplicitRenderSize_function_type )(  ) const;
            
            MouseCursor_exposer.def( 
                "getExplicitRenderSize"
                , getExplicitRenderSize_function_type( &::CEGUI::MouseCursor::getExplicitRenderSize )
                , bp::return_value_policy< bp::copy_const_reference >()
                , "*!\n\
            \n\
                Return the explicit render size currently set.  A return size of (0, 0)\n\
                indicates that the real image size will be used.\n\
            *\n" );
        
        }
        { //::CEGUI::MouseCursor::getImage
        
            typedef ::CEGUI::Image const * ( ::CEGUI::MouseCursor::*getImage_function_type )(  ) const;
            
            MouseCursor_exposer.def( 
                "getImage"
                , getImage_function_type( &::CEGUI::MouseCursor::getImage )
                , bp::return_value_policy< bp::reference_existing_object >()
                , "*!\n\
            \n\
               Get the current mouse cursor image\n\
            @return\n\
               The current image used to draw mouse cursor.\n\
            *\n" );
        
        }
        { //::CEGUI::MouseCursor::getPosition
        
            typedef ::CEGUI::Vector2f ( ::CEGUI::MouseCursor::*getPosition_function_type )(  ) const;
            
            MouseCursor_exposer.def( 
                "getPosition"
                , getPosition_function_type( &::CEGUI::MouseCursor::getPosition )
                , "*!\n\
               \n\
                  Return the current mouse cursor position as a pixel offset from the top-left corner of the\
                  display.\n\
            \n\
               @return\n\
                  Point object describing the mouse cursor position in screen pixels.\n\
               *\n" );
        
        }
        { //::CEGUI::MouseCursor::getUnifiedConstraintArea
        
            typedef ::CEGUI::URect const & ( ::CEGUI::MouseCursor::*getUnifiedConstraintArea_function_type )(  ) const;
            
            MouseCursor_exposer.def( 
                "getUnifiedConstraintArea"
                , getUnifiedConstraintArea_function_type( &::CEGUI::MouseCursor::getUnifiedConstraintArea )
                , bp::return_value_policy< bp::copy_const_reference >()
                , "*!\n\
               \n\
                  return the current constraint area of the mouse cursor.\n\
            \n\
               @return\n\
                  URect object describing the active area that the mouse cursor is constrained to.\n\
               *\n" );
        
        }
        { //::CEGUI::MouseCursor::hide
        
            typedef void ( ::CEGUI::MouseCursor::*hide_function_type )(  ) ;
            
            MouseCursor_exposer.def( 
                "hide"
                , hide_function_type( &::CEGUI::MouseCursor::hide )
                , "*!\n\
               \n\
                  Hides the mouse cursor.\n\
            \n\
               @return\n\
                  Nothing.\n\
               *\n" );
        
        }
        { //::CEGUI::MouseCursor::invalidate
        
            typedef void ( ::CEGUI::MouseCursor::*invalidate_function_type )(  ) ;
            
            MouseCursor_exposer.def( 
                "invalidate"
                , invalidate_function_type( &::CEGUI::MouseCursor::invalidate )
                , "*!\n\
            \n\
                Mark the cached geometry as invalid so it will be recached next time the\n\
                mouse cursor is drawn.\n\
            *\n" );
        
        }
        { //::CEGUI::MouseCursor::isVisible
        
            typedef bool ( ::CEGUI::MouseCursor::*isVisible_function_type )(  ) const;
            
            MouseCursor_exposer.def( 
                "isVisible"
                , isVisible_function_type( &::CEGUI::MouseCursor::isVisible )
                , "*!\n\
               \n\
                  return whether the mouse cursor is visible.\n\
            \n\
               @return\n\
                  true if the mouse cursor is visible, false if the mouse cursor is hidden.\n\
               *\n" );
        
        }
        { //::CEGUI::MouseCursor::notifyDisplaySizeChanged
        
            typedef void ( ::CEGUI::MouseCursor::*notifyDisplaySizeChanged_function_type )( ::CEGUI::Sizef const & ) ;
            
            MouseCursor_exposer.def( 
                "notifyDisplaySizeChanged"
                , notifyDisplaySizeChanged_function_type( &::CEGUI::MouseCursor::notifyDisplaySizeChanged )
                , ( bp::arg("new_size") )
                , "*!\n\
                \n\
                    Function used to notify the MouseCursor of changes in the display size.\n\
            \n\
                    You normally would not call this directly; rather you would call the\n\
                    function System.notifyDisplaySizeChanged and that will then call this\n\
                    function for you.\n\
            \n\
                @param new_size\n\
                    Size object describing the new display size in pixels.\n\
                *\n" );
        
        }
        { //::CEGUI::MouseCursor::offsetPosition
        
            typedef void ( ::CEGUI::MouseCursor::*offsetPosition_function_type )( ::CEGUI::Vector2f const & ) ;
            
            MouseCursor_exposer.def( 
                "offsetPosition"
                , offsetPosition_function_type( &::CEGUI::MouseCursor::offsetPosition )
                , ( bp::arg("offset") )
                , "*!\n\
               \n\
                  Offset the mouse cursor position by the deltas specified in  offset.\n\
            \n\
               @param offset\n\
                  Point object which describes the amount to move the cursor in each axis.\n\
            \n\
               @return\n\
                  Nothing.\n\
               *\n" );
        
        }
        { //::CEGUI::MouseCursor::onDefaultImageChanged
        
            typedef void ( MouseCursor_wrapper::*onDefaultImageChanged_function_type )( ::CEGUI::MouseCursorEventArgs & ) ;
            
            MouseCursor_exposer.def( 
                "onDefaultImageChanged"
                , onDefaultImageChanged_function_type( &MouseCursor_wrapper::default_onDefaultImageChanged )
                , ( bp::arg("e") )
                , "*************************************************************************\n\
               New event handlers\n\
            *************************************************************************\n\
             ! Event triggered internally when mouse cursor image is changed.\n\
             ! Event triggered internally when mouse cursor default image is changed.\n" );
        
        }
        { //::CEGUI::MouseCursor::onImageChanged
        
            typedef void ( MouseCursor_wrapper::*onImageChanged_function_type )( ::CEGUI::MouseCursorEventArgs & ) ;
            
            MouseCursor_exposer.def( 
                "onImageChanged"
                , onImageChanged_function_type( &MouseCursor_wrapper::default_onImageChanged )
                , ( bp::arg("e") )
                , "*************************************************************************\n\
               New event handlers\n\
            *************************************************************************\n\
             ! Event triggered internally when mouse cursor image is changed.\n" );
        
        }
        { //::CEGUI::MouseCursor::setConstraintArea
        
            typedef void ( ::CEGUI::MouseCursor::*setConstraintArea_function_type )( ::CEGUI::Rectf const * ) ;
            
            MouseCursor_exposer.def( 
                "setConstraintArea"
                , setConstraintArea_function_type( &::CEGUI::MouseCursor::setConstraintArea )
                , ( bp::arg("area") )
                , "*!\n\
               \n\
                  Set the area that the mouse cursor is constrained to.\n\
            \n\
               @param area\n\
                  Pointer to a Rect object that describes the area of the display that the mouse is allowed to\
                  occupy.  The given area will be clipped to\n\
                  the current Renderer screen area - it is never possible for the mouse to leave this area.  If\
                  this parameter is NULL, the\n\
                  constraint is set to the size of the current Renderer screen area.\n\
            \n\
               @return\n\
                  Nothing.\n\
               *\n" );
        
        }
        { //::CEGUI::MouseCursor::setDefaultImage
        
            typedef void ( ::CEGUI::MouseCursor::*setDefaultImage_function_type )( ::CEGUI::Image const * ) ;
            
            MouseCursor_exposer.def( 
                "setDefaultImage"
                , setDefaultImage_function_type( &::CEGUI::MouseCursor::setDefaultImage )
                , ( bp::arg("image") )
                , "*!\n\
                \n\
                    Set the image to be used as the default mouse cursor.\n\
            \n\
                @param image\n\
                    Pointer to an image object that is to be used as the default mouse\n\
                    cursor.  To have no cursor rendered by default, you can specify 0 here.\n\
                *\n" );
        
        }
        { //::CEGUI::MouseCursor::setDefaultImage
        
            typedef void ( ::CEGUI::MouseCursor::*setDefaultImage_function_type )( ::CEGUI::String const & ) ;
            
            MouseCursor_exposer.def( 
                "setDefaultImage"
                , setDefaultImage_function_type( &::CEGUI::MouseCursor::setDefaultImage )
                , ( bp::arg("name") )
                , "*!\n\
                \n\
                    Set the image to be used as the default mouse cursor.\n\
            \n\
                @param name\n\
                    String object that contains the name of the Image that is to be used.\n\
            \n\
                @exception\n\
                    UnknownObjectException thrown if no Image named  name exists.\n\
                *\n" );
        
        }
        { //::CEGUI::MouseCursor::setExplicitRenderSize
        
            typedef void ( ::CEGUI::MouseCursor::*setExplicitRenderSize_function_type )( ::CEGUI::Sizef const & ) ;
            
            MouseCursor_exposer.def( 
                "setExplicitRenderSize"
                , setExplicitRenderSize_function_type( &::CEGUI::MouseCursor::setExplicitRenderSize )
                , ( bp::arg("size") )
                , "*!\n\
                \n\
                    Set an explicit size for the mouse cursor image to be drawn at.\n\
            \n\
                    This will override the size that is usually obtained directly from the\n\
                    mouse cursor image and will stay in effect across changes to the mouse\n\
                    cursor image.\n\
            \n\
                    Setting this size to (0, 0) will revert back to using the size as\n\
                    obtained from the Image itself.\n\
            \n\
                @param size\n\
                    Reference to a Size object that describes the size at which the cursor\n\
                    image should be drawn in pixels.\n\
                *\n" );
        
        }
        { //::CEGUI::MouseCursor::setImage
        
            typedef void ( ::CEGUI::MouseCursor::*setImage_function_type )( ::CEGUI::String const & ) ;
            
            MouseCursor_exposer.def( 
                "setImage"
                , setImage_function_type( &::CEGUI::MouseCursor::setImage )
                , ( bp::arg("name") )
                , "*!\n\
               \n\
                  Set the current mouse cursor image\n\
            \n\
               @param name\n\
                  String object holding the name of the desired Image.\n\
            \n\
               @return\n\
                  Nothing.\n\
            \n\
               @exception UnknownObjectException   thrown if Image  name is not known.\n\
               *\n" );
        
        }
        { //::CEGUI::MouseCursor::setImage
        
            typedef void ( ::CEGUI::MouseCursor::*setImage_function_type )( ::CEGUI::Image const * ) ;
            
            MouseCursor_exposer.def( 
                "setImage"
                , setImage_function_type( &::CEGUI::MouseCursor::setImage )
                , ( bp::arg("image") )
                , "*!\n\
            \n\
               Set the current mouse cursor image\n\
            *\n" );
        
        }
        { //::CEGUI::MouseCursor::setInitialMousePosition
        
            typedef void ( *setInitialMousePosition_function_type )( ::CEGUI::Vector2f const & );
            
            MouseCursor_exposer.def( 
                "setInitialMousePosition"
                , setInitialMousePosition_function_type( &::CEGUI::MouseCursor::setInitialMousePosition )
                , ( bp::arg("position") )
                , "*!\n\
                \n\
                    Static function to pre-initialise the mouse cursor position (prior to\n\
                    MouseCursor instantiation).\n\
                    \n\
                    Calling this function prior to instantiating MouseCursor will prevent\n\
                    the mouse having it's position set to the middle of the initial view.\n\
                    Calling this function after the MouseCursor is instantiated will have\n\
                    no effect.\n\
            \n\
                @param position\n\
                    Reference to a point object describing the initial pixel position to\n\
                    be used for the mouse cursor.\n\
                *\n" );
        
        }
        { //::CEGUI::MouseCursor::setPosition
        
            typedef void ( ::CEGUI::MouseCursor::*setPosition_function_type )( ::CEGUI::Vector2f const & ) ;
            
            MouseCursor_exposer.def( 
                "setPosition"
                , setPosition_function_type( &::CEGUI::MouseCursor::setPosition )
                , ( bp::arg("position") )
                , "*!\n\
               \n\
                  Set the current mouse cursor position\n\
            \n\
               @param position\n\
                  Point object describing the new location for the mouse.  This will be clipped to within the\
                  renderer screen area.\n\
               *\n" );
        
        }
        { //::CEGUI::MouseCursor::setUnifiedConstraintArea
        
            typedef void ( ::CEGUI::MouseCursor::*setUnifiedConstraintArea_function_type )( ::CEGUI::URect const * ) ;
            
            MouseCursor_exposer.def( 
                "setUnifiedConstraintArea"
                , setUnifiedConstraintArea_function_type( &::CEGUI::MouseCursor::setUnifiedConstraintArea )
                , ( bp::arg("area") )
                , "*!\n\
               \n\
                  Set the area that the mouse cursor is constrained to.\n\
            \n\
               @param area\n\
                  Pointer to a URect object that describes the area of the display that the mouse is allowed to\
                  occupy.  The given area will be clipped to\n\
                  the current Renderer screen area - it is never possible for the mouse to leave this area.  If\
                  this parameter is NULL, the\n\
                  constraint is set to the size of the current Renderer screen area.\n\
            \n\
               @return\n\
                  Nothing.\n\
               *\n" );
        
        }
        { //::CEGUI::MouseCursor::setVisible
        
            typedef void ( ::CEGUI::MouseCursor::*setVisible_function_type )( bool ) ;
            
            MouseCursor_exposer.def( 
                "setVisible"
                , setVisible_function_type( &::CEGUI::MouseCursor::setVisible )
                , ( bp::arg("visible") )
                , "*!\n\
                \n\
                    Set the visibility of the mouse cursor.\n\
            \n\
                @param visible\n\
                    'true' to show the mouse cursor, 'false' to hide it.\n\
            \n\
                @return\n\
                    Nothing.\n\
                *\n" );
        
        }
        { //::CEGUI::MouseCursor::show
        
            typedef void ( ::CEGUI::MouseCursor::*show_function_type )(  ) ;
            
            MouseCursor_exposer.def( 
                "show"
                , show_function_type( &::CEGUI::MouseCursor::show )
                , "*!\n\
               \n\
                  Shows the mouse cursor.\n\
            \n\
               @return\n\
                  Nothing.\n\
               *\n" );
        
        }
        MouseCursor_exposer.add_static_property( "EventDefaultImageChanged"
                        , bp::make_getter( &CEGUI::MouseCursor::EventDefaultImageChanged
                                , bp::return_value_policy< bp::return_by_value >() ) );
        MouseCursor_exposer.add_static_property( "EventImageChanged"
                        , bp::make_getter( &CEGUI::MouseCursor::EventImageChanged
                                , bp::return_value_policy< bp::return_by_value >() ) );
        { //::CEGUI::EventSet::fireEvent
        
            typedef void ( ::CEGUI::EventSet::*fireEvent_function_type )( ::CEGUI::String const &,::CEGUI::EventArgs &,::CEGUI::String const & ) ;
            typedef void ( MouseCursor_wrapper::*default_fireEvent_function_type )( ::CEGUI::String const &,::CEGUI::EventArgs &,::CEGUI::String const & ) ;
            
            MouseCursor_exposer.def( 
                "fireEvent"
                , fireEvent_function_type(&::CEGUI::EventSet::fireEvent)
                , default_fireEvent_function_type(&MouseCursor_wrapper::default_fireEvent)
                , ( bp::arg("name"), bp::arg("args"), bp::arg("eventNamespace")="" ) );
        
        }
        { //::CEGUI::EventSet::fireEvent_impl
        
            typedef void ( MouseCursor_wrapper::*fireEvent_impl_function_type )( ::CEGUI::String const &,::CEGUI::EventArgs & ) ;
            
            MouseCursor_exposer.def( 
                "fireEvent_impl"
                , fireEvent_impl_function_type( &MouseCursor_wrapper::fireEvent_impl )
                , ( bp::arg("name"), bp::arg("args") )
                , "! Implementation event firing member\n" );
        
        }
        { //::CEGUI::EventSet::getScriptModule
        
            typedef ::CEGUI::ScriptModule * ( MouseCursor_wrapper::*getScriptModule_function_type )(  ) const;
            
            MouseCursor_exposer.def( 
                "getScriptModule"
                , getScriptModule_function_type( &MouseCursor_wrapper::getScriptModule )
                , bp::return_value_policy< bp::reference_existing_object >()
                , "! Implementation event firing member\n\
            ! Helper to return the script module pointer or throw.\n" );
        
        }
        { //::CEGUI::EventSet::subscribeScriptedEvent
        
            typedef ::CEGUI::RefCounted< CEGUI::BoundSlot > ( ::CEGUI::EventSet::*subscribeScriptedEvent_function_type )( ::CEGUI::String const &,::CEGUI::String const & ) ;
            typedef ::CEGUI::RefCounted< CEGUI::BoundSlot > ( MouseCursor_wrapper::*default_subscribeScriptedEvent_function_type )( ::CEGUI::String const &,::CEGUI::String const & ) ;
            
            MouseCursor_exposer.def( 
                "subscribeScriptedEvent"
                , subscribeScriptedEvent_function_type(&::CEGUI::EventSet::subscribeScriptedEvent)
                , default_subscribeScriptedEvent_function_type(&MouseCursor_wrapper::default_subscribeScriptedEvent)
                , ( bp::arg("name"), bp::arg("subscriber_name") ) );
        
        }
        { //::CEGUI::EventSet::subscribeScriptedEvent
        
            typedef ::CEGUI::RefCounted< CEGUI::BoundSlot > ( ::CEGUI::EventSet::*subscribeScriptedEvent_function_type )( ::CEGUI::String const &,unsigned int,::CEGUI::String const & ) ;
            typedef ::CEGUI::RefCounted< CEGUI::BoundSlot > ( MouseCursor_wrapper::*default_subscribeScriptedEvent_function_type )( ::CEGUI::String const &,unsigned int,::CEGUI::String const & ) ;
            
            MouseCursor_exposer.def( 
                "subscribeScriptedEvent"
                , subscribeScriptedEvent_function_type(&::CEGUI::EventSet::subscribeScriptedEvent)
                , default_subscribeScriptedEvent_function_type(&MouseCursor_wrapper::default_subscribeScriptedEvent)
                , ( bp::arg("name"), bp::arg("group"), bp::arg("subscriber_name") ) );
        
        }
        MouseCursor_exposer.staticmethod( "setInitialMousePosition" );
    }

}
