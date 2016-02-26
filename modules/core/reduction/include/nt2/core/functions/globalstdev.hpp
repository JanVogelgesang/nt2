//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_GLOBALSTDEV_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_GLOBALSTDEV_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/include/functions/stdev.hpp>
#include <nt2/include/functions/colvect.hpp>

namespace nt2
{
  /*!
    @brief Standard Deviation  of all the elements of an expression

    Computes the standard deviation  of all the elements of a table expression

    @par Semantic

    For any table expression :

    @code
    T r = globalstdev(t, k);
    @endcode

    is equivalent to:

    @code
    T r = stdev(t(_), k)(1);
    @endcode


    @see @funcref{colon}, @funcref{stdev}
    @param a0 Table expression to process
    @param a1 Table expression or integer

    @return An expression eventually evaluated to the result
  **/
  template<typename A0, typename A1>
  BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE globalstdev(A0 const& a0,A1 const& a1)
  BOOST_AUTO_DECLTYPE_BODY( nt2::stdev(nt2::colvect(a0),a1) );

  /// @overload
  template<typename Args>
  BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE globalstdev(Args const& a0)
  BOOST_AUTO_DECLTYPE_BODY( nt2::stdev(nt2::colvect(a0)) );
}

#endif
