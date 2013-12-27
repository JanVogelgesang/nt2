//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2013        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/sdk/unit/exhaustive.hpp>
#include <nt2/include/functions/log1p.hpp>

#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/valmax.hpp>

struct raw_log1p
{
  float operator()(float x) const
  {
    return float(nt2::log1p(double(x)));
  }
};

int main()
{
  nt2::exhaustive_test<float> ( nt2::Mone<float>()
                              , nt2::Valmax<float>()
                              , nt2::functor<nt2::tag::log1p_>()
                              , raw_log1p()
                              );

  return 0;
}
