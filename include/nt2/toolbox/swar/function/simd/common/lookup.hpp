//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_SWAR_FUNCTION_SIMD_COMMON_LOOKUP_HPP_INCLUDED
#define NT2_TOOLBOX_SWAR_FUNCTION_SIMD_COMMON_LOOKUP_HPP_INCLUDED
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/at.hpp>
#include <nt2/include/functions/load.hpp>
#include <nt2/include/functions/store.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::lookup_, tag::cpu_,
                         (A0)(X),
                         ((simd_<arithmetic_<A0>,X>))
                         ((simd_<arithmetic_<A0>,X>))
                        );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::lookup_(tag::simd_(tag::arithmetic_, X),
                           tag::simd_(tag::arithmetic_, X)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::scalar_of<A0>::type sA0;
      aligned::array < sA0,meta::cardinal_of<A0>::value,16/*NT2_SIMD_BYTE*/ > tmp, tmp1;
      store(tmp.begin(), a0);

      for(size_t i=0; i < meta::cardinal_of<A0>::value; i++) { tmp1[i] = tmp[a1[i]]; }// TODO unroll
      return load(tmp1.begin(), 0);
    }

  };
} }

#endif
// modified by jt the 05/01/2011