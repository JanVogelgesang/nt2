//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_SSE_SSE_LOAD_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_SSE_SSE_LOAD_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE_SUPPORT

#include <boost/simd/memory/functions/load.hpp>
#include <boost/simd/meta/is_pointing_to.hpp>
#include <boost/simd/sdk/simd/category.hpp>
#include <boost/dispatch/functor/preprocessor/call.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/mpl/if.hpp>
#include <boost/assert.hpp>

namespace boost { namespace simd { namespace ext
{
  /// INTERNAL ONLY - single load without offset
  BOOST_DISPATCH_IMPLEMENT          ( load_
                                    , boost::simd::tag::sse_
                                    , (A0)(A1)
                                    , (iterator_< scalar_< single_<A0> > >)
                                      ((target_< simd_< single_<A1>
                                                      , boost::simd::tag::sse_
                                                      >
                                                >
                                      ))
                                    )
  {
    typedef typename A1::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 a0, const A1&) const
    {
      return _mm_loadu_ps(a0);
    }
  };

} } }

#endif
#endif
