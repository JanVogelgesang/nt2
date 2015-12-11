//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_CONSTANTS_INVPI_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_CONSTANTS_INVPI_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>

namespace nt2
{
  namespace tag
  {
   /*!
     @brief Invpi generic tag

     Represents the Invpi constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Invpi, double
                                , 0, 0x3ea2f983
                                , 0x3fd45f306dc9c883ll
                                )
  }
  namespace ext
  {
   template<class Site, class... Ts>
   BOOST_FORCEINLINE generic_dispatcher<tag::Invpi, Site> dispatching_Invpi(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
   {
     return generic_dispatcher<tag::Invpi, Site>();
   }
   template<class... Args>
   struct impl_Invpi;
  }
  /*!
    Constant\f$\frac1\pi\f$.

    @par Semantic:

    For type T0:

    @code
    T0 r = Invpi<T0>();
    @endcode

    is similar to:

    @code
    T0 r = rec(Pi<T0>());
    @endcode

    @return a value of type T0
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Invpi, Invpi);
}

#endif

