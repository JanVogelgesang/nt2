//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_CEPHES_FUNCTIONS_SQRT_HPP_INCLUDED
#define NT2_TOOLBOX_CEPHES_FUNCTIONS_SQRT_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/toolbox/cephes/include.hpp>

namespace nt2 { namespace cephes { namespace tag
  {         
    struct sqrt_ {};
  }
  NT2_FUNCTION_IMPLEMENTATION(cephes::tag::sqrt_, sqrt, 1)
  } }
 
#include <nt2/toolbox/cephes/functions/scalar/sqrt.hpp>
// #include <nt2/toolbox/cephes/functions/simd/all/sqrt.hpp> 

 
#endif

// modified by jt the 29/12/2010