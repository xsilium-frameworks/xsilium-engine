// This file has been generated by Py++.

#include "boost/python.hpp"
#include "python_CEGUI.h"
#include "WindowIterator.pypp.hpp"

namespace bp = boost::python;

struct ConstVectorIterator_less__std_scope_vector_less__CEGUI_scope_Window_ptr___greater___greater__wrapper : CEGUI::ConstVectorIterator< std::vector< CEGUI::Window* > >, bp::wrapper< CEGUI::ConstVectorIterator< std::vector< CEGUI::Window* > > > {

    ConstVectorIterator_less__std_scope_vector_less__CEGUI_scope_Window_ptr___greater___greater__wrapper(CEGUI::ConstVectorIterator<std::vector<CEGUI::Window*, std::allocator<CEGUI::Window*> > > const & arg )
    : CEGUI::ConstVectorIterator<std::vector<CEGUI::Window*, std::allocator<CEGUI::Window*> > >( arg )
      , bp::wrapper< CEGUI::ConstVectorIterator< std::vector< CEGUI::Window* > > >(){
        // copy constructor
        
    }

    virtual ::CEGUI::Window * getCurrentValue(  ) const  {
        if( bp::override func_getCurrentValue = this->get_override( "getCurrentValue" ) )
            return func_getCurrentValue(  );
        else{
            return this->CEGUI::ConstVectorIterator< std::vector< CEGUI::Window* > >::getCurrentValue(  );
        }
    }
    
    ::CEGUI::Window * default_getCurrentValue(  ) const  {
        return CEGUI::ConstVectorIterator< std::vector< CEGUI::Window* > >::getCurrentValue( );
    }

};

void Iterator_next(::CEGUI::ConstVectorIterator<std::vector<CEGUI::Window*, std::allocator<CEGUI::Window*> > >& t)
{
    t++;
}

void Iterator_previous(::CEGUI::ConstVectorIterator<std::vector<CEGUI::Window*, std::allocator<CEGUI::Window*> > >& t)
{
    t--;
}

void register_WindowIterator_class(){

    { //::CEGUI::ConstVectorIterator< std::vector< CEGUI::Window* > >
        typedef bp::class_< ConstVectorIterator_less__std_scope_vector_less__CEGUI_scope_Window_ptr___greater___greater__wrapper, bp::bases< CEGUI::ConstBaseIterator< std::vector< CEGUI::Window* >, CEGUI::Window* > > > WindowIterator_exposer_t;
        WindowIterator_exposer_t WindowIterator_exposer = WindowIterator_exposer_t( "WindowIterator", bp::no_init );
        bp::scope WindowIterator_scope( WindowIterator_exposer );
        { //::CEGUI::ConstVectorIterator< std::vector< CEGUI::Window* > >::getCurrentValue
        
            typedef CEGUI::ConstVectorIterator< std::vector< CEGUI::Window* > > exported_class_t;
            typedef ::CEGUI::Window * ( exported_class_t::*getCurrentValue_function_type )(  ) const;
            typedef ::CEGUI::Window * ( ConstVectorIterator_less__std_scope_vector_less__CEGUI_scope_Window_ptr___greater___greater__wrapper::*default_getCurrentValue_function_type )(  ) const;
            
            WindowIterator_exposer.def( 
                "getCurrentValue"
                , getCurrentValue_function_type(&::CEGUI::ConstVectorIterator< std::vector< CEGUI::Window* > >::getCurrentValue)
                , default_getCurrentValue_function_type(&ConstVectorIterator_less__std_scope_vector_less__CEGUI_scope_Window_ptr___greater___greater__wrapper::default_getCurrentValue)
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        WindowIterator_exposer.def("next", &::Iterator_next);
        WindowIterator_exposer.def("previous", &::Iterator_previous);
    }

}
