//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/geqrf.hpp>
#include <nt2/include/functions/fliplr.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/mtimes.hpp>

#include <nt2/table.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL(qrf, NT2_REAL_TYPES )
{
  using nt2::_;

  typedef nt2::table<T>           t_t;

  t_t in  = nt2::ones (2000, 2000, nt2::meta::as_<T>())
          + T(10)*nt2::eye  (2000,2000, nt2::meta::as_<T>());
  t_t tau;

  nt2_la_int p = 5;
  p = nt2::geqrf(boost::proto::value(in),boost::proto::value(tau));

  NT2_TEST_EQUAL(p, 0);
}


NT2_TEST_CASE_TPL(qrfc, NT2_REAL_TYPES )
{
  using nt2::_;

  typedef std::complex<T>         cT;
  typedef nt2::table<cT>          t_t;

  t_t in  = nt2::ones (2000, 2000, nt2::meta::as_<cT>())
          + T(10)*nt2::eye  (2000,2000, nt2::meta::as_<cT>());
  t_t tau;

  nt2_la_int p = 5;
  p = nt2::geqrf(boost::proto::value(in),boost::proto::value(tau));

  NT2_TEST_EQUAL(p, 0);
}
