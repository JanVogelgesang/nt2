//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_GLOBALASUM2_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_GLOBALASUM2_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/include/functions/asum2.hpp>
#include <nt2/include/functions/colvect.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the globalasum2 functor
    **/
    struct globalasum2_ : ext::abstract_<globalasum2_>
    {
      /// @brief Parent hierarchy
      typedef ext::abstract_<globalasum2_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_globalasum2_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site, class... Ts>
    BOOST_FORCEINLINE generic_dispatcher<tag::globalasum2_, Site> dispatching_globalasum2_(adl_helper, boost::dispatch::meta::unknown_<Site>, boost::dispatch::meta::unknown_<Ts>...)
    {
      return generic_dispatcher<tag::globalasum2_, Site>();
    }
    template<class... Args>
    struct impl_globalasum2_;
  }
  /*!
    @brief Sum of the absolute square of all the elements of a table expression

    Computes the sum of the absolute square of all the elements of a
    table expression

    @par Semantic

    For any table @c t:

    @code
    T r = globalasum2(t);
    @endcode

    is equivalent to:

    @code
    T r = asum2(a(_))(1);
    @endcode

    @see @funcref{colon}, @funcref{asum2}
    @param a0 Table expression to process

    @return An expression eventually evaluated to the result
  **/

  template<typename Args>
  BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE globalasum2(Args const& a0)
  BOOST_AUTO_DECLTYPE_BODY( nt2::asum2(nt2::colvect(a0)) );
}

#endif
