//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::sum1 function"

#include <nt2/table.hpp>
#include <nt2/include/functions/binearest.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/repmat.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/isequal.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/expand_to.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/constants/nan.hpp>
#include <boost/core/ignore_unused.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>



NT2_TEST_CASE_TPL( binearest, NT2_REAL_TYPES )
{
  using nt2::_;
  nt2::table<T> x =  nt2::linspace(T(1),  T(3), 3);
  nt2::table<T> y =  nt2::linspace(T(1),  T(4), 4);
  nt2::table<T> z =  reshape(nt2::linspace(T(1),  T(12), 12), 4, 3);
  nt2::table<T> xi =  nt2::linspace(T(1),  T(3), 12);
  nt2::table<T> yi =  nt2::linspace(T(1),  T(3), 12);
  nt2::table<T> ri =  nt2::cons<T>(   1,    1,    1,    6,    6,    6,    6,    6,    6,   11,   11,   11);

  nt2::table<T> zi = nt2::binearest(x, y, z, xi, yi);
  NT2_DISPLAY(  nt2::binearest(x, y, z, xi, yi));
  NT2_TEST_EQUAL(ri, zi);

  xi =  nt2::linspace(T(1),  T(4), 12);
  yi =  nt2::linspace(T(0),  T(3), 12);
  zi = nt2::binearest(x, y, z, xi, yi);
  NT2_DISPLAY(zi);
  ri =  nt2::cons<T>( nt2::Nan<T>(), nt2::Nan<T>(), nt2::Nan<T>(), nt2::Nan<T>(), 5, 5, 10, 10
                    , nt2::Nan<T>(), nt2::Nan<T>(), nt2::Nan<T>(), nt2::Nan<T>());
  NT2_TEST_EQUAL(ri, zi);
}






