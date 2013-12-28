//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2013        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_UNIT_EXHAUSTIVE_HPP_INCLUDED
#define NT2_SDK_UNIT_EXHAUSTIVE_HPP_INCLUDED

#include <nt2/include/functions/load.hpp>
#include <nt2/include/functions/extract.hpp>
#include <nt2/include/functions/is_invalid.hpp>
#include <nt2/include/functions/successor.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/constants/valmin.hpp>
#include <nt2/include/functions/iround.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/ilog2.hpp>
#include <nt2/include/functions/exp2.hpp>
#include <nt2/include/functions/all.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/constants/nan.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <nt2/sdk/meta/type_id.hpp>
#include <iostream>
#include <iomanip>
#include <cstdio>

#define NT2_ASSERTS_AS_TRAP
#include <nt2/sdk/error/assert_as_trap.hpp>

namespace nt2
{
  /*!
    @brief Exhaustive precision test for single precision driver

    Perform a ULP test on every representable single precision value
    in a given interval. Results are reported using a bucket histogram that
    gives hint on how many values fall in a given range of ULPs, a sample input
    leading to this precision and the awaited result.

    @par Note:
    Currently this function is designed to take care of single precision only as
    running such a test on double precision values take an absurd amount of time.

    @tparam Type          Data type used for computation
    @param  mini Lower    bound of the test interval
    @param  maxi Upper    bound of the test interval
    @param  test_f        Function to test
    @param  reference_f   Reference function to compare to
  **/
  template<typename Type, typename TestF, typename RefF> inline
  void exhaustive_test(float mini, float maxi, TestF test_f, RefF reference_f)
  {
    typedef Type                                                    n_t;
    typedef typename boost::dispatch::meta::as_integer<Type>::type  in_t;

    const nt2::uint32_t M = 128;
    const nt2::uint32_t N = boost::simd::meta::cardinal_of<n_t>::value;
    const in_t vN = nt2::splat<in_t>(N);

    float a[N];
    float maxin[M+2];
    float minin[M+2];
    float minref[M+2];
    float minval[M+2];
    bool  hit[M+2];
    nt2::uint32_t histo[M+2];

    for(std::size_t i = 0; i < M+2; i++)
    {
      histo[i] = 0;
      minval[i] = nt2::Nan<float>();
      minin[i]  = nt2::Valmin<float>();
      maxin[i]  = nt2::Valmax<float>();
      hit[i] =  false;
    }

    // Fill up the reference SIMD register data
    a[0] = mini;
    for(std::size_t i = 1; i < N; i++)
      a[i] = nt2::successor(a[i-1], 1);

    n_t a0 = nt2::load<n_t>(&a[0],0);

    nt2::uint32_t k = 0, j = 0;

    std::cout << "Exhaustive test for: " << nt2::type_id(test_f)      << "\n"
              << "             versus: " << nt2::type_id(reference_f) << "\n"
              << "             With T: " << nt2::type_id<Type>()      << "\n"
              << "    in the interval: [" << mini << ",  " << maxi << "]" << "\n";
    std::cout << std::endl;
    std::cout << "[" << std::flush;

    while( nt2::extract(a0,N-1) < maxi )
    {
      n_t z = test_f(a0);

      for(std::size_t i = 0; i < N; i++)
      {
        float v = reference_f(nt2::extract(a0,i));

        float sz = nt2::extract(z,i);
        double u = nt2::ulpdist(v, sz)*2.0+1.0;

        if(nt2::is_invalid(u))
        {
          ++histo[M+1];
          if (!hit[M+1])
          {
            maxin [M+1] = minin [M+1] = nt2::extract(a0,i);
            minref[M+1] = v;
            minval[M+1] = nt2::extract(z,i);
            hit[M+1] = true;
          }
          else
          {
            maxin [M+1] = nt2::extract(a0,i);
          }
        }
        else
        {
          int p = nt2::min(int(M), int(nt2::ilog2(nt2::iround(u))));
          if (!hit[p])
          {
            maxin [p] = minin [p] = nt2::extract(a0,i);
            minref[p] = v;
            minval[p] = nt2::extract(z,i);
            hit[p] = true;
          }
          else
          {
            maxin [p] = nt2::extract(a0,i);
          }
          ++histo[p];
        }

        ++k;
        if (k%100000000 == 0)
        {
          if (k%1000000000 == 0)
            std::cout << "*" << std::flush;
          else
            std::cout << "." << std::flush;

          ++j;
          if (j == 80)
          {
            std::cout << std::endl;
            j = 0;
          }
        }
      }

      a0 = nt2::successor(a0, vN);
    }

    std::cout << "]" << std::endl;
    std::cout << k << " values computed.\n";

    double d = 1;
    for(std::size_t i = 0; i < M+1; i++, d*= 2.0)
    {
      if(histo[i])
      {
        printf("%10u values (%.2f%%)\twithin %1.1f ULPs.\t"
              , histo[i], (histo[i]*100.0/k), (d < 2 ? 0 : d/4)
              );
        if(i)
          std::cout << std::scientific << std::setprecision(7)
                    << "All samples values are in = [" << minin[i] << ",  "<< maxin[i] << "]"
                    << " Example: "<< minin[i] << " returns " << minval[i]
                    << " instead of " << minref[i];
        std::cout << std::endl;
      }
    }

    if( histo[M+1])
    {
        printf("%10u values (%.2f%%)\twith invalid result.\t"
              , histo[M+1], (histo[M+1]*100.0/k)
              );
        std::cout << std::scientific << std::setprecision(7)
                  << "All samples value in = [" << minin[M+1] << ",  "<< maxin[M+1] << "]"
                  << " Example: "<< minin[M+1] << " returns " << minval[M+1]
                  << " instead of " << minref[M+1]
                  << std::endl;

    }
  }
}

#endif
