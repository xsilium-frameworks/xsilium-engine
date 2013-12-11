// This file has been generated by Py++.

#include "boost/python.hpp"
#include "python_CEGUI.h"
#include "RegexMatcher.pypp.hpp"

namespace bp = boost::python;

struct RegexMatcher_wrapper : CEGUI::RegexMatcher, bp::wrapper< CEGUI::RegexMatcher > {

    RegexMatcher_wrapper()
    : CEGUI::RegexMatcher()
      , bp::wrapper< CEGUI::RegexMatcher >(){
        // null constructor
        
    }

    virtual ::CEGUI::RegexMatcher::MatchState getMatchStateOfString( ::CEGUI::String const & str ) const {
        bp::override func_getMatchStateOfString = this->get_override( "getMatchStateOfString" );
        return func_getMatchStateOfString( boost::ref(str) );
    }

    virtual ::CEGUI::String const & getRegexString(  ) const {
        throw std::logic_error("warning W1049: This method could not be overriden in Python - method returns reference to local variable!");
    }

    virtual void setRegexString( ::CEGUI::String const & regex ){
        bp::override func_setRegexString = this->get_override( "setRegexString" );
        func_setRegexString( boost::ref(regex) );
    }

};

void register_RegexMatcher_class(){

    { //::CEGUI::RegexMatcher
        typedef bp::class_< RegexMatcher_wrapper, boost::noncopyable > RegexMatcher_exposer_t;
        RegexMatcher_exposer_t RegexMatcher_exposer = RegexMatcher_exposer_t( "RegexMatcher" );
        bp::scope RegexMatcher_scope( RegexMatcher_exposer );
        bp::enum_< CEGUI::RegexMatcher::MatchState>("MatchState")
            .value("MS_VALID", CEGUI::RegexMatcher::MS_VALID)
            .value("MS_INVALID", CEGUI::RegexMatcher::MS_INVALID)
            .value("MS_PARTIAL", CEGUI::RegexMatcher::MS_PARTIAL)
            .export_values()
            ;
        { //::CEGUI::RegexMatcher::getMatchStateOfString
        
            typedef ::CEGUI::RegexMatcher::MatchState ( ::CEGUI::RegexMatcher::*getMatchStateOfString_function_type )( ::CEGUI::String const & ) const;
            
            RegexMatcher_exposer.def( 
                "getMatchStateOfString"
                , bp::pure_virtual( getMatchStateOfString_function_type(&::CEGUI::RegexMatcher::getMatchStateOfString) )
                , ( bp::arg("str") )
                , "! Return reference to current regex string set.\n\
            ! Return the MatchState result for the given String.\n" );
        
        }
        { //::CEGUI::RegexMatcher::getRegexString
        
            typedef ::CEGUI::String const & ( ::CEGUI::RegexMatcher::*getRegexString_function_type )(  ) const;
            
            RegexMatcher_exposer.def( 
                "getRegexString"
                , bp::pure_virtual( getRegexString_function_type(&::CEGUI::RegexMatcher::getRegexString) )
                , bp::return_value_policy< bp::copy_const_reference >()
                , "! Set the regex string that will be matched against.\n\
            ! Return reference to current regex string set.\n" );
        
        }
        { //::CEGUI::RegexMatcher::setRegexString
        
            typedef void ( ::CEGUI::RegexMatcher::*setRegexString_function_type )( ::CEGUI::String const & ) ;
            
            RegexMatcher_exposer.def( 
                "setRegexString"
                , bp::pure_virtual( setRegexString_function_type(&::CEGUI::RegexMatcher::setRegexString) )
                , ( bp::arg("regex") )
                , "! Destructor.\n\
            ! Set the regex string that will be matched against.\n" );
        
        }
    }

}
