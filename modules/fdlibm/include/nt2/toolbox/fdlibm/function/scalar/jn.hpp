//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_FDLIBM_FUNCTION_SCALAR_JN_HPP_INCLUDED
#define NT2_TOOLBOX_FDLIBM_FUNCTION_SCALAR_JN_HPP_INCLUDED

  extern "C"{
    extern double fd_jn ( int,double );
  }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(fdlibm::tag::jn_, tag::cpu_,
                    (A0)(A1),
                    (integer_<A0>)(arithmetic_<A1>)
                   )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<fdlibm::tag::jn_(tag::integer_,tag::arithmetic_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
    struct result<This(A0, A1)> : meta::result_of<meta::floating(A1)>{};

    NT2_FUNCTOR_CALL(2)
    {
      return nt2::fdlibm::jn(a0, double(a1));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(fdlibm::tag::jn_, tag::cpu_,
                    (A0)(A1),
                    (integer_<A0>)(double_<A1>)
                   )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<fdlibm::tag::jn_(tag::integer_,tag::double_),
              tag::cpu_, Dummy> : callable
  {
    typedef double result_type; 

    NT2_FUNCTOR_CALL(2){ return fd_jn(a0, a1); }
  };
} }

#endif
// modified by jt the 29/12/2010
