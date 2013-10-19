//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_TBB_TBB_HPP_INCLUDED
#define NT2_SDK_TBB_TBB_HPP_INCLUDED

#include <boost/dispatch/functor/forward.hpp>
#include <nt2/sdk/shared_memory/shared_memory.hpp>

namespace nt2 { namespace tag
{
  template<typename Site> struct tbb_ : shared_memory_< tbb_<Site>, Site >
  {
    typedef shared_memory_< tbb_<Site>, Site > parent;
  };
} }

#if defined(NT2_USE_TBB)
BOOST_DISPATCH_COMBINE_SITE( nt2::tag::tbb_<tag::cpu_> )
#include <tbb/tbb.h>
#include <nt2/sdk/tbb/blocked_range.hpp>
#include <nt2/sdk/tbb/worker.hpp>
#include <nt2/sdk/tbb/spawner.hpp>
#endif

#endif
