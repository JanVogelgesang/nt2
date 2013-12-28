//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2013        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/sdk/unit/exhaustive.hpp>
#include <nt2/include/functions/fast_log.hpp>
#include <nt2/include/functions/log.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <cmath>

struct raw_fast_log
{
  float operator()(float x) const
  {
    return float(std::log((double)x));
  }
};


int main(int ac, char* av[])
{
  typedef BOOST_SIMD_DEFAULT_EXTENSION             ext_t;
  typedef boost::simd::native<float,ext_t>           n_t;

  float mini = nt2::Zero<float>();
  float maxi = nt2::Valmax<float>();
  if(ac == 3)
  {
    mini = std::atof(av[1]);
    maxi = std::atof(av[2]);
  }
  nt2::exhaustive_test<n_t> (mini
                            ,maxi
                            , nt2::functor<nt2::tag::fast_log_>()
                            , raw_fast_log()
                            );
  return 0;
}
