//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_VMX_ALTIVEC_FNMS_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_VMX_ALTIVEC_FNMS_HPP_INCLUDED

#include <boost/simd/arithmetic/functions/fnms.hpp>

namespace boost { namespace simd { namespace BOOST_SIMD_EXT_NS
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::fnms_
                                    , boost::simd::tag::vmx_
                                    , (A0)
                                    , ((simd_<floating_<A0>,boost::simd::tag::vmx_>))
                                      ((simd_<floating_<A0>,boost::simd::tag::vmx_>))
                                      ((simd_<floating_<A0>,boost::simd::tag::vmx_>))
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 const& a0, A0 const& a1, A0 const& a2) const
    {
     return vec_nmsub(a0(),a1(),a2());
    }
  };
} } }

#endif
