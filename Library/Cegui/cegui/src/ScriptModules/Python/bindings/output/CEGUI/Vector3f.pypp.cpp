// This file has been generated by Py++.

#include "boost/python.hpp"
#include "python_CEGUI.h"
#include "Vector3f.pypp.hpp"

namespace bp = boost::python;

void register_Vector3f_class(){

    { //::CEGUI::Vector3< float >
        typedef bp::class_< CEGUI::Vector3< float > > Vector3f_exposer_t;
        Vector3f_exposer_t Vector3f_exposer = Vector3f_exposer_t( "Vector3f", bp::init< >() );
        bp::scope Vector3f_scope( Vector3f_exposer );
        Vector3f_exposer.def( bp::init< float, float, float >(( bp::arg("x"), bp::arg("y"), bp::arg("z") )) );
        Vector3f_exposer.def( bp::init< CEGUI::Vector2< float > const &, float >(( bp::arg("v"), bp::arg("z") )) );
        Vector3f_exposer.def( bp::init< CEGUI::Vector3< float > const & >(( bp::arg("v") )) );
        { //::CEGUI::Vector3< float >::one
        
            typedef CEGUI::Vector3< float > exported_class_t;
            typedef ::CEGUI::Vector3< float > ( *one_function_type )(  );
            
            Vector3f_exposer.def( 
                "one"
                , one_function_type( &::CEGUI::Vector3< float >::one )
                , "!  finger saving alias for Vector3(1, 1, 1)\n" );
        
        }
        { //::CEGUI::Vector3< float >::one_x
        
            typedef CEGUI::Vector3< float > exported_class_t;
            typedef ::CEGUI::Vector3< float > ( *one_x_function_type )(  );
            
            Vector3f_exposer.def( 
                "one_x"
                , one_x_function_type( &::CEGUI::Vector3< float >::one_x )
                , "!  finger saving alias for Vector3(1, 0, 0)\n" );
        
        }
        { //::CEGUI::Vector3< float >::one_y
        
            typedef CEGUI::Vector3< float > exported_class_t;
            typedef ::CEGUI::Vector3< float > ( *one_y_function_type )(  );
            
            Vector3f_exposer.def( 
                "one_y"
                , one_y_function_type( &::CEGUI::Vector3< float >::one_y )
                , "!  finger saving alias for Vector3(0, 1, 0)\n" );
        
        }
        { //::CEGUI::Vector3< float >::one_z
        
            typedef CEGUI::Vector3< float > exported_class_t;
            typedef ::CEGUI::Vector3< float > ( *one_z_function_type )(  );
            
            Vector3f_exposer.def( 
                "one_z"
                , one_z_function_type( &::CEGUI::Vector3< float >::one_z )
                , "!  finger saving alias for Vector3(0, 0, 1)\n" );
        
        }
        Vector3f_exposer.def( bp::self != bp::self );
        Vector3f_exposer.def( bp::self * bp::other< float >() );
        Vector3f_exposer.def( bp::self + bp::self );
        Vector3f_exposer.def( bp::self - bp::self );
        Vector3f_exposer.def( bp::self == bp::self );
        { //::CEGUI::Vector3< float >::zero
        
            typedef CEGUI::Vector3< float > exported_class_t;
            typedef ::CEGUI::Vector3< float > ( *zero_function_type )(  );
            
            Vector3f_exposer.def( 
                "zero"
                , zero_function_type( &::CEGUI::Vector3< float >::zero )
                , "!  finger saving alias for Vector3(0, 0, 0)\n" );
        
        }
        Vector3f_exposer.def_readwrite( "d_x", &CEGUI::Vector3< float >::d_x );
        Vector3f_exposer.def_readwrite( "d_y", &CEGUI::Vector3< float >::d_y );
        Vector3f_exposer.def_readwrite( "d_z", &CEGUI::Vector3< float >::d_z );
        Vector3f_exposer.staticmethod( "one" );
        Vector3f_exposer.staticmethod( "one_x" );
        Vector3f_exposer.staticmethod( "one_y" );
        Vector3f_exposer.staticmethod( "one_z" );
        Vector3f_exposer.staticmethod( "zero" );
    }

}
