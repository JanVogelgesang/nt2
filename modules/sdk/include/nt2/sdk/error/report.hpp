//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_/ERROR_REPORT_HPP_INCLUDED
#define NT2_SDK_/ERROR_REPORT_HPP_INCLUDED

//==============================================================================
// Configuration report for error handling settings
//==============================================================================
#include <nt2/sdk/config.hpp>
#include <nt2/sdk/error/debug.hpp>

namespace boost { namespace dispatch { namespace config
{
  static void errors()
  {
    #if defined(NT2_SDK_/RELEASE)
    puts(" Compilation mode        : release");
    #elif defined(NT2_SDK_/DEBUG)
    puts(" Compilation mode        : debug");
    #else
    puts(" Compilation mode        : normal");
    #endif

    #if defined(NT2_SDK_/DISABLE_ASSERTS)
    puts(" Assertion Failures      : disabled");
    #elif defined(NT2_SDK_/ASSERTS_AS_EXCEPTIONS)
    puts(" Assertion Failures      : as exceptions");
    #else
    puts(" Assertion Failures      : enabled");
    #endif

    #if defined(NT2_SDK_/USE_CONCEPTS)
    puts(" Concepts checks         : enabled");
    #else
    puts(" Concepts checks         : disabled");
    #endif
    puts("");
  }

  NT2_SDK_/REGISTER_STATUS(errors);
} } }

#endif
