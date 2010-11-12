//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_BESSEL_FUNCTION_SCALAR_Y1_HPP_INCLUDED
#define NT2_TOOLBOX_BESSEL_FUNCTION_SCALAR_Y1_HPP_INCLUDED
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/sdk/constant/real.hpp>

#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/cos.hpp>
#include <nt2/include/functions/is_ltz.hpp>
#include <nt2/include/functions/is_eqz.hpp>

namespace nt2 { namespace functors
{

  //  no special validate for y1

  /////////////////////////////////////////////////////////////////////////////
  // Compute y1(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<y1_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : 
      boost::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL_DISPATCH(
      1,
      A0,
      (3, (float,double,arithmetic_))
    )

    NT2_FUNCTOR_CALL_EVAL_IF(1,  float)
    {
      typedef typename meta::scalar_of<A0>::type stype; 
	if (is_ltz(a0)) return Nan<float>();
	if (is_eqz(a0)) return Minf<float>();
	A0 x = nt2::abs(a0);
	if (lt(x,Two<A0>()))
	  {
	    A0 z = sqr(x); 
	    return (z-single_constant<float,0x416ae95a> ())*x*
	      horner< NT2_HORNER_COEFF_T(stype, 5,
				       (0xb1a7a246, 
					0x35214df5, 
					0xb83e7a4f, 
					0x3afdefd1, 
					0xbd0b7da6
					) ) > (z);
         }
	A0 q = rec(x);
	A0 w = sqrt(q);       
	A0 p3 = w *
	  horner< NT2_HORNER_COEFF_T(stype, 8,
				   (0x3d8d98f9, 
				    0xbe69f6b3, 
				    0x3ea0ad85, 
				    0xbe574699, 
				    0x3bb21b25, 
				    0x3e18ec50, 
				    0x36a6f7c5, 
				    0x3f4c4229
				    ) ) > (q);
          w = sqr(q);
          A0 xn =  q*
          horner< NT2_HORNER_COEFF_T(stype, 8,
			       (0xc233e16d,
				0x424af04a, 
				0xc1c6dca7, 
				0x40e72299, 
				0xbfc5bd69, 
				0x3eb364d9, 
				0xbe27bad7, 
				0x3ebfffdd
				) ) > (w)-single_constant<float,0x4016cbe4 > (); 
          return p3*nt2::cos(xn+x); 
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1, double)
    {
      return ::j1(a0);
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1, arithmetic_)
    {
      typedef typename NT2_CALL_RETURN_TYPE(1)::type type; 
      return nt2::y1(type(a0)); 
    }
  };
} }


      
#endif
