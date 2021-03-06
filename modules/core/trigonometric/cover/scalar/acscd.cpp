//==============================================================================
//         Copyright 2003 - 2014   LASMEA UMR 6602 CNRS/UBP
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
// cover for functor acscd in scalar mode
#include <nt2/trigonometric/include/functions/acscd.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <cmath>
#include <iostream>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/ten.hpp>
#include <nt2/sdk/unit/args.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/cover.hpp>
#include <vector>

extern "C" {extern long double cephes_asinl(long double);}

NT2_TEST_CASE_TPL(acscd_0,  NT2_SIMD_REAL_TYPES)
{
  using nt2::unit::args;
  const std::size_t NR = args("samples", NT2_NB_RANDOM_TEST);
  const double ulpd = args("ulpd", 7.0);
  const long double long_radindeg =  57.295779513082320876798154814105l;

  const T min = args("min", nt2::One<T>());
  const T max = args("max", nt2::Ten<T>());
  std::cout << "Argument samples #0 chosen in range: [" << min << ",  " << max << "]" << std::endl;
  NT2_CREATE_BUF(a0,T, NR, min, max);

  std::vector<T> ref(NR);
  for(std::size_t i=0; i!=NR; ++i)
    ref[i] = ::cephes_asinl(1.0l/(a0[i]))*long_radindeg;

  NT2_COVER_ULP_EQUAL(nt2::tag::acscd_, ((T, a0)), ref, ulpd);

}
