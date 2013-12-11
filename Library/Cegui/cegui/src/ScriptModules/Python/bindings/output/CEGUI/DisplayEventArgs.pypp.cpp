// This file has been generated by Py++.

#include "boost/python.hpp"
#include "python_CEGUI.h"
#include "DisplayEventArgs.pypp.hpp"

namespace bp = boost::python;

void register_DisplayEventArgs_class(){

    { //::CEGUI::DisplayEventArgs
        typedef bp::class_< CEGUI::DisplayEventArgs, bp::bases< CEGUI::EventArgs > > DisplayEventArgs_exposer_t;
        DisplayEventArgs_exposer_t DisplayEventArgs_exposer = DisplayEventArgs_exposer_t( "DisplayEventArgs", "*!\n\
        \n\
            EventArgs based class that is used for notifications regarding the main\n\
            display.\n\
        *\n", bp::init< CEGUI::Sizef const & >(( bp::arg("sz") )) );
        bp::scope DisplayEventArgs_scope( DisplayEventArgs_exposer );
        bp::implicitly_convertible< CEGUI::Sizef const &, CEGUI::DisplayEventArgs >();
        DisplayEventArgs_exposer.def_readwrite( "size", &CEGUI::DisplayEventArgs::size, "! current  new size of the display.\n" );
    }

}
