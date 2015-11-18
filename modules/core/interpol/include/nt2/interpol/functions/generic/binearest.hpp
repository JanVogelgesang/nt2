//==============================================================================
//         Copyright 2015          J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_INTERPOL_FUNCTIONS_GENERIC_BINEAREST_HPP_INCLUDED
#define NT2_INTERPOL_FUNCTIONS_GENERIC_BINEAREST_HPP_INCLUDED

#include <nt2/interpol/functions/binearest.hpp>
#include <nt2/include/functions/colvect.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/inc.hpp>
#include <nt2/include/functions/is_equal.hpp>
#include <nt2/include/functions/issorted.hpp>
#include <nt2/include/functions/isvector.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/pow2.hpp>
#include <nt2/include/functions/selinc.hpp>
#include <nt2/include/functions/sub2ind.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <boost/assert.hpp>
#include <nt2/core/container/colon/colon.hpp>
#include <nt2/interpol/functions/details/bsearch.hpp>
#include <nt2/interpol/functions/details/extrapol2.hpp>
#include <nt2/interpol/functions/details/check2.hpp>


namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( binearest_, tag::cpu_
                            , (A0)(A1)(A2)(A3)
                            , (scalar_<arithmetic_<A0> > )
                              (unspecified_<A1> )
                              (unspecified_<A2> )
                              (unspecified_<A3> )
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE
    result_type operator()(const A0 &, const A1 &, const A2 &, const A3 &) const

    {
      BOOST_ASSERT_MSG(false, "Interpolation requires at least two sample points in each dimension.");
      return Nan<A0>();
    }
  };
  BOOST_DISPATCH_IMPLEMENT  ( binearest_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (scalar_<arithmetic_<A0> > )
                              (unspecified_<A1> )
                              (unspecified_<A2> )
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE
    result_type operator()(const A0 &, const A1 &, const A2 &) const

    {
      BOOST_ASSERT_MSG(false, "Interpolation requires at least two sample points in each dimension.");
      return Nan<A0>();
    }
  };
  BOOST_DISPATCH_IMPLEMENT  ( binearest_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_<arithmetic_<A0> > )
                              (unspecified_<A1> )
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE
    result_type operator()(const A0 &, const A1 &) const

    {
      BOOST_ASSERT_MSG(false, "Interpolation requires at least two sample points in each dimension.");
      return Nan<A0>();
    }
  };
  BOOST_DISPATCH_IMPLEMENT  ( binearest_, tag::cpu_
                            , (A0)
                            , (scalar_<arithmetic_<A0> > )
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE
    result_type operator()(const A0 &) const

    {
      BOOST_ASSERT_MSG(false, "Interpolation requires at least two sample points in each dimension.");
      return Nan<A0>();
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( run_assign_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1,nt2::tag::binearest_,boost::mpl::long_<1>,nt2::container::domain>))
                            )
  {
    typedef typename boost::proto::result_of::child_c<A1&,0>::value_type  child0;
    typedef A0& result_type;
    BOOST_FORCEINLINE
    result_type operator()(const A0 & zi, A1& inputs) const
    {
      const child0 & z = boost::proto::child_c<0>(inputs);
      zi = binearest(z, 1);
      return zi;
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( run_assign_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1,nt2::tag::binearest_,boost::mpl::long_<2>,nt2::container::domain>))
                            )
  {
    typedef typename boost::proto::result_of::child_c<A1&,0>::value_type  child0;
    typedef typename boost::proto::result_of::child_c<A1&,1>::value_type  child1;
    typedef A0& result_type;
    BOOST_FORCEINLINE
    result_type operator()(const A0 & zi, A1& inputs) const
    {
      const child0 & z = boost::proto::child_c<0>(inputs);
      using value_type = typename child0::value_type;
      using x_type = typename meta::as_real<value_type>::type;
      size_t n = boost::proto::child_c<1>(inputs);
      //     Calculate the interleaved input vectors.
      x_type p = x_type(pow2(n));
      size_t hz = height(z);
      size_t wz = width(z);
      auto hind = colvect(_(p, p*hz)/p);
      size_t h = x_type(numel(hind));
      auto wind = _(p, p*wz)/p;
      size_t w = x_type(numel(wind));
      auto xi = expand_to(wind, of_size(h, w));
      auto yi = expand_to(hind, of_size(h, w));
      zi = binearest(_(One<x_type>(), wz),
                     _(One<x_type>(), hz), z, xi, yi);
      return zi;
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( run_assign_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1,nt2::tag::binearest_,boost::mpl::long_<4>,nt2::container::domain>))
                            )
  {
    typedef typename boost::proto::result_of::child_c<A1&,0>::value_type  child0;
    typedef typename boost::proto::result_of::child_c<A1&,1>::value_type  child1;
    typedef typename boost::proto::result_of::child_c<A1&,2>::value_type  child2;
    typedef A0& result_type;
    BOOST_FORCEINLINE
    result_type operator()(const A0 & zi, A1& inputs) const
    {
      const child0 & z = boost::proto::child_c<0>(inputs);
      using value_type = typename child0::value_type;
      using x_type = typename meta::as_real<value_type>::type;
      zi = binearest(_(One<x_type>(), width(z)), _(One<x_type>(), height(z)),
                     z,
                     boost::proto::child_c<1>(inputs),
                     boost::proto::child_c<1>(inputs),
                     boost::proto::child_c<3>(inputs)
                    );
      return zi;
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( run_assign_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1,nt2::tag::binearest_,boost::mpl::long_<3>,nt2::container::domain>))
                            )
  {
    typedef typename boost::proto::result_of::child_c<A1&,0>::value_type  child0;
    typedef typename boost::proto::result_of::child_c<A1&,1>::value_type  child1;
    typedef typename boost::proto::result_of::child_c<A1&,2>::value_type  child2;
    typedef A0& result_type;
    BOOST_FORCEINLINE
    result_type operator()(const A0 & zi, A1& inputs) const
    {
       const child0 & z   =  boost::proto::child_c<0>(inputs);
       const child1 & xi  =  boost::proto::child_c<1>(inputs);
       const child2 & yi  =  boost::proto::child_c<2>(inputs);
       zi = binearest(z, xi, yi, false);
      return zi;
    }
  };


  BOOST_DISPATCH_IMPLEMENT  ( binearest_, tag::cpu_
                            , (A0)(A1)(A2)(A3)(A4)
                            , (scalar_<arithmetic_<A0> > )
                              (unspecified_<A1> )
                              (unspecified_<A2> )
                              (unspecified_<A3> )
                              (unspecified_<A4> )
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE
    result_type operator()(const A0 &, const A1 &, const A2 &) const

    {
      BOOST_ASSERT_MSG(false, "Interpolation requires at least two sample points in each dimension.");
      return Nan<A0>();
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( binearest_, tag::cpu_
                            , (A0)(A1)(A2)(A3)(A4)(A5)
                            , (scalar_<arithmetic_<A0> > )
                              (unspecified_<A1> )
                              (unspecified_<A2> )
                              (unspecified_<A3> )
                              (unspecified_<A4> )
                              (unspecified_<A5> )
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE
    result_type operator()(const A0 &, const A0 & , const A0 & , const A0 & ) const
    {
      BOOST_ASSERT_MSG(false, "Interpolation requires at least two sample points in each dimension.");
      return  Nan<A0>();
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( run_assign_, tag::cpu_
                            , (A0)(A1)(N1)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1,nt2::tag::binearest_,N1,nt2::container::domain>))
                            )
  {
    typedef typename boost::proto::result_of::child_c<A1&,0>::value_type  child0;
    typedef typename boost::proto::result_of::child_c<A1&,1>::value_type  child1;
    typedef typename boost::proto::result_of::child_c<A1&,2>::value_type  child2;
    typedef typename boost::proto::result_of::child_c<A1&,3>::value_type  child3;
    typedef typename boost::proto::result_of::child_c<A1&,4>::value_type  child4;
    typedef typename child0::value_type                                   x_type;
    typedef typename child2::value_type                               value_type;
    typedef typename meta::as_integer<x_type>::type                   index_type;
    typedef table<value_type>                                             vtab_t;
    typedef table<x_type>                                                 xtab_t;
    typedef table<index_type>                                             itab_t;
    typedef A0&                                                      result_type;

    result_type operator()(A0& zi, A1& inputs) const
    {
       const child0 & x_  =  boost::proto::child_c<0>(inputs);
       const child1 & y_  =  boost::proto::child_c<1>(inputs);
       const child2 & z   =  boost::proto::child_c<2>(inputs);
       const child3 & xi_ =  boost::proto::child_c<3>(inputs);
       const child4 & yi_ =  boost::proto::child_c<4>(inputs);
//        const child0 & x  =  boost::proto::child_c<0>(inputs);
//        const child1 & y  =  boost::proto::child_c<1>(inputs);
//        const child2 & z  =  boost::proto::child_c<2>(inputs);
       if ((numel(x_) <=  1) || (numel(y_) <=  1))
       {
         BOOST_ASSERT_MSG(false,
                          "Interpolation requires at least two sample points in each dimension.");
       }
       else
       {
         xtab_t x, y, xii, yii;
         details::check2(z, x_, y_, xi_, yi_, x, y, xii, yii);
//          BOOST_ASSERT_MSG(issorted(x, 'a')&&issorted(y, 'a'), "for 'binearest' interpolation x and y values must be sorted in ascending order");
//          BOOST_ASSERT_MSG((numel(x) == width(z) && numel(y) == height(z))
//                         , "The grid vectors do not define a grid of points that match the given values.");
         auto xi =  rowvect(xii);
         auto yi =  rowvect(yii);
         bool extrap = false;
         value_type extrapval = Nan<value_type>();
         choices(inputs, extrap, extrapval, N1());
         table<index_type> indx, indy;
         details::bsearch (indx, x, xi);
         details::bsearch (indy, y, yi);
         auto ii = selinc((xi - rowvect(x(indx)) >= rowvect(x(inc(indx))) - xi), indx);
         auto jj = selinc((yi - rowvect(y(indy)) >= rowvect(y(inc(indy))) - yi), indy);
         auto indz = sub2ind (size(z), jj, ii);
         zi = z(indz);
         if (!extrap)
         {
           details::extrapol2(zi, x, y, xi, yi, extrapval);
         }
         zi = reshape(zi, xii.extent());
       }
       return zi;
    }
  private :
    static void choices(const A1&, bool &,  value_type&, boost::mpl::long_<5> const &)
    { }
    static void choices(const A1& inputs, bool & extrap,  value_type& extrapval, boost::mpl::long_<6> const &)
    {
        typedef typename boost::proto::result_of::child_c<A1&,3>::type             child3;
        typedef typename meta::scalar_of<child3>::type                    cref_param_type;
        typedef typename meta::strip<cref_param_type>::type                    param_type;
        get(inputs, extrap, extrapval, param_type());
      }
    static void get(const A1& inputs, bool & extrap,  value_type&,  const bool &)
      {
        extrap =  boost::proto::child_c<3>(inputs);
      }
    static void get(const A1& inputs, bool &,  value_type& extrapval,  const value_type &)
      {
        extrapval =  boost::proto::child_c<3>(inputs);
      }
  };
} }


#endif
