// This file has been generated by Py++.

#include "boost/python.hpp"
#include "python_CEGUI.h"
#include "FontGlyph.pypp.hpp"

namespace bp = boost::python;

void register_FontGlyph_class(){

    { //::CEGUI::FontGlyph
        typedef bp::class_< CEGUI::FontGlyph > FontGlyph_exposer_t;
        FontGlyph_exposer_t FontGlyph_exposer = FontGlyph_exposer_t( "FontGlyph", bp::init< bp::optional< float, CEGUI::Image * > >(( bp::arg("advance")=0.0f, bp::arg("image")=bp::object() ), "! Constructor.\n") );
        bp::scope FontGlyph_scope( FontGlyph_exposer );
        bp::implicitly_convertible< float, CEGUI::FontGlyph >();
        { //::CEGUI::FontGlyph::getAdvance
        
            typedef float ( ::CEGUI::FontGlyph::*getAdvance_function_type )( float ) const;
            
            FontGlyph_exposer.def( 
                "getAdvance"
                , getAdvance_function_type( &::CEGUI::FontGlyph::getAdvance )
                , ( bp::arg("x_scale")=1.0e+0 )
                , "*!\n\
                \n\
                    Return the horizontal advance value for the glyph.\n\
            \n\
                    The returned value is the number of pixels the pen should move\n\
                    horizontally to position itself ready to render the next glyph.  This\n\
                    is not always the same as the glyph image width or rendererd advance,\n\
                    since it allows for horizontal overhangs.\n\
                *\n" );
        
        }
        { //::CEGUI::FontGlyph::getHeight
        
            typedef float ( ::CEGUI::FontGlyph::*getHeight_function_type )( float ) const;
            
            FontGlyph_exposer.def( 
                "getHeight"
                , getHeight_function_type( &::CEGUI::FontGlyph::getHeight )
                , ( bp::arg("y_scale") )
                , "! Return the scaled height of the glyph.\n" );
        
        }
        { //::CEGUI::FontGlyph::getImage
        
            typedef ::CEGUI::Image * ( ::CEGUI::FontGlyph::*getImage_function_type )(  ) const;
            
            FontGlyph_exposer.def( 
                "getImage"
                , getImage_function_type( &::CEGUI::FontGlyph::getImage )
                , bp::return_value_policy< bp::reference_existing_object >()
                , "! Return the CEGUI.Image object rendered for this glyph.\n" );
        
        }
        { //::CEGUI::FontGlyph::getRenderedAdvance
        
            typedef float ( ::CEGUI::FontGlyph::*getRenderedAdvance_function_type )( float ) const;
            
            FontGlyph_exposer.def( 
                "getRenderedAdvance"
                , getRenderedAdvance_function_type( &::CEGUI::FontGlyph::getRenderedAdvance )
                , ( bp::arg("x_scale") )
                , "*!\n\
                \n\
                    Return the rendered advance value for this glyph.\n\
            \n\
                    The rendered advance value is the total number of pixels from the\n\
                    current pen position that will be occupied by this glyph when rendered.\n\
                *\n" );
        
        }
        { //::CEGUI::FontGlyph::getSize
        
            typedef ::CEGUI::Sizef ( ::CEGUI::FontGlyph::*getSize_function_type )( float,float ) const;
            
            FontGlyph_exposer.def( 
                "getSize"
                , getSize_function_type( &::CEGUI::FontGlyph::getSize )
                , ( bp::arg("x_scale"), bp::arg("y_scale") )
                , "! Return the scaled pixel size of the glyph.\n" );
        
        }
        { //::CEGUI::FontGlyph::getWidth
        
            typedef float ( ::CEGUI::FontGlyph::*getWidth_function_type )( float ) const;
            
            FontGlyph_exposer.def( 
                "getWidth"
                , getWidth_function_type( &::CEGUI::FontGlyph::getWidth )
                , ( bp::arg("x_scale") )
                , "! Return the scaled width of the glyph.\n" );
        
        }
        { //::CEGUI::FontGlyph::setAdvance
        
            typedef void ( ::CEGUI::FontGlyph::*setAdvance_function_type )( float ) ;
            
            FontGlyph_exposer.def( 
                "setAdvance"
                , setAdvance_function_type( &::CEGUI::FontGlyph::setAdvance )
                , ( bp::arg("advance") )
                , "! Set the horizontal advance value for the glyph.\n" );
        
        }
        { //::CEGUI::FontGlyph::setImage
        
            typedef void ( ::CEGUI::FontGlyph::*setImage_function_type )( ::CEGUI::Image * ) ;
            
            FontGlyph_exposer.def( 
                "setImage"
                , setImage_function_type( &::CEGUI::FontGlyph::setImage )
                , ( bp::arg("image") )
                , "! Set the CEGUI.Image object rendered for this glyph.\n" );
        
        }
    }

}
