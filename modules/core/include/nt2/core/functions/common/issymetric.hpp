//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_ISSYMETRIC_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_ISSYMETRIC_HPP_INCLUDED

#include <nt2/core/functions/issymetric.hpp>
#include <nt2/include/functions/issquare.hpp>
#include <nt2/include/functions/last_index.hpp>
#include <nt2/include/functions/first_index.hpp>
#include <nt2/include/functions/is_not_equal.hpp>
// #include <nt2/sdk/details/type_id.hpp>
// #include <iostream>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::issymetric_, tag::cpu_
                            , (A0), (unspecified_<A0>)
                            )
  {
    typedef bool result_type;

    BOOST_DISPATCH_FORCE_INLINE result_type operator()(const A0& a0) const
    {
      typedef typename A0::value_type value_type;

      // Non-square matrix can't be symmetric
      if (!issquare(a0)) return false;

      // Check for everything upward/below diagonal
      for(std::ptrdiff_t j=first_index<2>(a0); j <= last_index<2>(a0) ; ++j)
        for(std::ptrdiff_t i=j+1; i <= last_index<1>(a0) ; ++i)
          if( (value_type(a0(i, j)) != value_type(a0(j, i)))) return false;

      return true;
    }
  };
} }

#endif
