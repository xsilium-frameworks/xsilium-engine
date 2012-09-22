/*=============================================================================
    Boost.Wave: A Standard compliant C++ preprocessor library
    Sample demonstrating the usage of advanced preprocessor hooks.
    
    http://www.boost.org/

    Copyright (c) 2001-2011 Hartmut Kaiser. Distributed under the Boost 
    Software License, Version 1.0. (See accompanying file 
    LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

///////////////////////////////////////////////////////////////////////////////
//  Include Wave itself
#include <boost/wave.hpp>

///////////////////////////////////////////////////////////////////////////////
// Include the lexer stuff
#include <boost/wave/cpplexer/cpp_lex_token.hpp>    // token class
#include <boost/wave/cpplexer/cpp_lex_iterator.hpp> // lexer class

#include "emit_custom_line_directives.hpp"

///////////////////////////////////////////////////////////////////////////////
//  Main entry point
//
//  This sample shows how to use the emit_line_directive preprocessing hooks 
//  to customize the format of any generated #line directive. The sample will 
//  emit #line directives formatted compatible with those generated by gcc:
//
//    # <lineno> <rel_file_name>
//
int main(int argc, char *argv[])
{
    if (2 != argc) {
        std::cerr << "Usage: emit_custom_line_directives infile" << std::endl;
        return -1;
    }

// current file position is saved for exception handling
boost::wave::util::file_position_type current_position;

    try {
    //  Open and read in the specified input file.
    std::ifstream instream(argv[1]);
    std::string instring;

        if (!instream.is_open()) {
            std::cerr << "Could not open input file: " << argv[1] << std::endl;
            return -2;
        }
        instream.unsetf(std::ios::skipws);
        instring = std::string(std::istreambuf_iterator<char>(instream.rdbuf()),
                               std::istreambuf_iterator<char>());

    //  The template boost::wave::cpplexer::lex_token<> is the token type to be 
    //  used by the Wave library.
        typedef boost::wave::cpplexer::lex_token<> token_type;

    //  The template boost::wave::cpplexer::lex_iterator<> is the lexer type to
    //  be used by the Wave library.
        typedef boost::wave::cpplexer::lex_iterator<token_type> lex_iterator_type;

    //  This is the resulting context type to use. The first template parameter
    //  should match the iterator type to be used during construction of the
    //  corresponding context object (see below).
        typedef boost::wave::context<std::string::iterator, lex_iterator_type,
                boost::wave::iteration_context_policies::load_file_to_string,
                emit_custom_line_directives_hooks
            > context_type;

    // The preprocessor iterator shouldn't be constructed directly. It is 
    // to be generated through a wave::context<> object. This wave:context<> 
    // object additionally may be used to initialize and define different 
    // parameters of the actual preprocessing (not done here).
    //
    // The preprocessing of the input stream is done on the fly behind the 
    // scenes during iteration over the context_type::iterator_type stream.
    context_type ctx (instring.begin(), instring.end(), argv[1]);

    ctx.set_language(boost::wave::enable_long_long(ctx.get_language()));
    ctx.set_language(boost::wave::enable_preserve_comments(ctx.get_language()));
    ctx.set_language(boost::wave::enable_prefer_pp_numbers(ctx.get_language()));

    // analyze the input file, print out the preprocessed tokens
    context_type::iterator_type first = ctx.begin();
    context_type::iterator_type last = ctx.end();

        while (first != last) {
            current_position = (*first).get_position();
            std::cout << (*first).get_value();
            ++first;
        }
    }
    catch (boost::wave::cpp_exception const& e) {
    // some preprocessing error
        std::cerr 
            << e.file_name() << "(" << e.line_no() << "): "
            << e.description() << std::endl;
        return 2;
    }
    catch (std::exception const& e) {
    // use last recognized token to retrieve the error position
        std::cerr 
            << current_position.get_file() 
            << "(" << current_position.get_line() << "): "
            << "exception caught: " << e.what()
            << std::endl;
        return 3;
    }
    catch (...) {
    // use last recognized token to retrieve the error position
        std::cerr 
            << current_position.get_file() 
            << "(" << current_position.get_line() << "): "
            << "unexpected exception caught." << std::endl;
        return 4;
    }
    return 0;
}
