/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_FORSYTHE_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_FORSYTHE_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/sqrteps.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_forsythe forsythe
 *
 * \par Description
 * forsythe matrix
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/forsythe.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \param x the fundamental column of the matrix,
 *        x is always treated as a big column vector
 *
 * \param n (optinnal) the number of column of the matrix (default is numel(x(_))
 *
**/
//==============================================================================
// forsythe actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag forsythe_ of functor forsythe
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct forsythe_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  NT2_FUNCTION_IMPLEMENTATION(tag::forsythe_, forsythe, 3)

  template<class T, class A0>
  typename meta::call<tag::forsythe_(const A0 &, const T &, const T &)>::type
  forsythe(const A0& n)
  {
    return nt2::forsythe(n, nt2::Sqrteps<T>(), nt2::Zero<T>());
  }
  template<class T, class A0, class A1>
  typename meta::call<tag::forsythe_(const A0 &, const A1 , const A1 &)>::type
  forsythe(const A0& n, const A1& alpha)
  {
    return nt2::forsythe(n, alpha, nt2::Zero<A1>());
  }
  template<class A0, class A1,  class Target>
  typename meta::call<tag::forsythe_(const A0 &,const A1 &,typename Target::type const &)>::type
  forsythe(const A0& n, const A1& alpha, const Target&)
  {
    typedef typename Target::type t_t;
    return nt2::forsythe(n,t_t(alpha), nt2::Zero<t_t>());
  }
  template<class A0, class A1,  class A2, class Target>
  typename meta::call<tag::forsythe_(const A0 &, typename Target::type const &, typename Target::type const &)>::type
  forsythe(const A0& n, const A1& alpha, const A2& lambda, const Target&)
  {
    typedef typename Target::type t_t;
    return nt2::forsythe(n,t_t(alpha), t_t(lambda));
  }

}

#endif
