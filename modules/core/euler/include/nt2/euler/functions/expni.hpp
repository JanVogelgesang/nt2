//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_EXPNI_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_EXPNI_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief expni generic tag

     Represents the expni function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct expni_ : BOOST_SIMD_EXT_NS::elementwise_<expni_> { typedef BOOST_SIMD_EXT_NS::elementwise_<expni_> parent; };
  }
  /*!
    Computes the exponential integral function
    @par Semantic:

    For every parameters of floating types respectively T0, T1:

    @code
    T0 r = expni(a0,a1);
    @endcode

    Computes \f$ E_{a_0}(a_1)=\int_0^\infty \frac{e^{-a_1t}}{t^{a_0}} \mbox{d}t\f$


    @param a0

    @param a1

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::expni_, expni, 2)
}

#endif

