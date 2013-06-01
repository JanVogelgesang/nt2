//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 arithmetic toolbox - ifloor/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// cover test behavior of arithmetic components in scalar mode
//////////////////////////////////////////////////////////////////////////////
#include <nt2/arithmetic/include/functions/ifloor.hpp>
#include <vector>
#include <nt2/include/constants/valmin.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/standard/include/functions/floor.hpp>
#include <nt2/sdk/meta/as_integer.hpp>



NT2_TEST_CASE_TPL ( ifloor_real__1_0,  NT2_REAL_TYPES)
{

  using nt2::ifloor;
  using nt2::tag::ifloor_;
  typedef typename nt2::meta::call<ifloor_(T)>::type r_t;

  nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  std::vector<T> in1(NR);
  nt2::roll(in1, nt2::Valmin<T>()/2, nt2::Valmax<T>()/2);
  std::vector<r_t>  ref(NR);
  for(nt2::uint32_t i=0; i < NR ; ++i)
  {
    ref[i] = nt2::standard::floor(in1[i]);
  }

  NT2_COVER_ULP_EQUAL(ifloor_, ((T, in1)), ref, 0);
}

NT2_TEST_CASE_TPL ( ifloor_real__1_1,  NT2_INTEGRAL_TYPES)
{

  using nt2::ifloor;
  using nt2::tag::ifloor_;
  typedef typename nt2::meta::call<ifloor_(T)>::type r_t;

  nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  std::vector<T> in1(NR);
  nt2::roll(in1, nt2::Valmin<T>()/2, nt2::Valmax<T>()/2);
  std::vector<r_t>  ref(NR);
  for(nt2::uint32_t i=0; i < NR ; ++i)
  {
    ref[i] = in1[i];
  }

  NT2_COVER_ULP_EQUAL(ifloor_, ((T, in1)), ref, 0);
}
