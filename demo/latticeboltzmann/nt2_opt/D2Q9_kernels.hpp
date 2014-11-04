//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#ifndef D2Q9_KERNELS_HPP_INCLUDED
#define D2Q9_KERNELS_HPP_INCLUDED

#include <cmath>
#include <iostream>

#include <nt2/table.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/cons.hpp>

using namespace nt2;

template< typename T>
inline void relaxation( nt2::table<T> & m
                      , nt2::table<T,nt2::of_size_<6> > const s_
                      )
  {
    T la = T(1.);
    T rho = T(1.);
    T dummy_ = T(1.)/(la*la*rho);
    nt2::table<T> qx2 = dummy_*m(_,_,2)*m(_,_,2);
    nt2::table<T> qy2 = dummy_*m(_,_,3)*m(_,_,3);
    nt2::table<T> q2  = qx2 + qy2;
    nt2::table<T> qxy = dummy_*m(_,_,2)*m(_,_,3);

    m(_,_,4) = m(_,_,4)*(T(1.)-s_(1)) + s_(1)*(-T(2.)*m(_,_,1) + T(3.)*q2);
    m(_,_,5) = m(_,_,5)*(T(1.)-s_(2)) + s_(2)*(m(_,_,1) + T(1.5)*q2);
    m(_,_,6) = m(_,_,6)*(T(1.)-s_(3)) - s_(3)*m(_,_,2)/la;
    m(_,_,7) = m(_,_,7)*(T(1.)-s_(4)) - s_(4)*m(_,_,3)/la;
    m(_,_,8) = m(_,_,8)*(T(1.)-s_(5)) + s_(5)*(qx2-qy2);
    m(_,_,9) = m(_,_,9)*(T(1.)-s_(6)) + s_(6)*qxy;
  }

template< typename T>
inline void get_f( nt2::table<T> const & f
                 , nt2::table<T> & fcopy
                 ,int nx
                 ,int ny
                 )
{
    fcopy(_,_,1) = f(_,_,1);

    fcopy(_(2,nx),_,2)    = f(_(1,nx-1),_,2);
    // fcopy(1,_,2)  = T(0);

    fcopy(_,_(2,ny),3)    = f(_,_(1,ny-1),3);
    // fcopy(_,1,3)  = T(0);

    fcopy(_(1,nx-1),_, 4) = f(_(2,nx),_,4);
    // fcopy(nx,_,4) = T(0);

    fcopy(_,_(1,ny-1), 5 ) = f(_,_(2,ny), 5 );
    // fcopy(_,ny,4) = T(0);

    fcopy(_(2,nx),_(1,ny-1), 6 ) = f(_(1,nx-1),_(2,ny), 6 );
    // fcopy(1,_,6) = T(0); fcopy(_,ny,6) = T(0);


    fcopy( _(1,nx-1),_(2,ny), 7 ) = f( _(2,nx), _(1,ny-1), 7 );
    // fcopy(nx,_,7) = T(0); fcopy(_,1,7) = T(0);

    fcopy( _(1,nx-1), _(1,ny-1), 8 ) = f( _(2,nx),_(2,ny), 8 );
    // fcopy(nx,_,8) = T(0); fcopy(_,ny,8) = T(0);

    fcopy(_(2,nx),_(1,ny-1), 9 ) = f(_(1,nx-1),_(2,ny), 9 );
    // fcopy(1,_,9) = T(0); fcopy(_,ny,9) = T(0);
}

template<typename T>
inline void f2m( nt2::table<T> & fcopy
               , nt2::table<T> & m
               , int nx
               , int ny
               )
{
   T la = T(1.);

   nt2::table<T> invF (   nt2::cons<T>( nt2::of_size(9 ,9),
      1,  1,  1,  1,  1,  1,  1,  1,  1,
      0, la,  0,-la,  0, la,-la,-la, la,
      0,  0, la,  0,-la, la, la,-la,-la,
     -4, -1, -1, -1, -1,  2,  2,  2,  2,
      4, -2, -2, -2, -2,  1,  1,  1,  1,
      0, -2,  0,  2,  0,  1, -1, -1,  1,
      0,  0, -2,  0,  2,  1,  1, -1, -1,
      0,  1, -1,  1, -1,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  1, -1,  1, -1
      )
    );

   fcopy.resize(nt2::of_size(nx*ny,9));
   m.resize(nt2::of_size(nx*ny,9));

   m = nt2::mtimes(fcopy,invF);

   fcopy.resize(nt2::of_size(nx,ny,9));
   m.resize(nt2::of_size(nx,ny,9));
}

template<typename T>
inline void m2f( nt2::table<T> & m
               , nt2::table<T> & fcopy
               , int nx
               , int ny
               )
{
    T la = T(1.);
    T a(1./9)
    , b(1./36.)
    , c(1./(6.*la))
    , d(1./12)
    , e(1./4.);

   nt2::table<T> invM (   nt2::cons<T>( nt2::of_size(9 ,9),
                          a,  0,  0, -4*b,  4*b,    0,    0,  0,  0,
                          a,  c,  0,   -b, -2*b, -2*d,    0,  e,  0,
                          a,  0,  c,   -b, -2*b,    0, -2*d, -e,  0,
                          a, -c,  0,   -b, -2*b,  2*d,    0,  e,  0,
                          a,  0, -c,   -b, -2*b,    0,  2*d, -e,  0,
                          a,  c,  c,  2*b,    b,    d,    d,  0,  e,
                          a, -c,  c,  2*b,    b,   -d,    d,  0, -e,
                          a, -c, -c,  2*b,    b,   -d,   -d,  0,  e,
                          a,  c, -c,  2*b,    b,    d,   -d,  0, -e
                          )
                       );

   m.resize(nt2::of_size(nx*ny,9));
   fcopy.resize(nt2::of_size(nx*ny,9));

   fcopy = nt2::mtimes(m,invM);

   m.resize(nt2::of_size(nx,ny,9));
   fcopy.resize(nt2::of_size(nx,ny,9));
}

template< typename T>
inline void bouzidi( nt2::table<T> const & f
            , nt2::table<T> & fcopy
            , int k
            , nt2::table<int> const & bc
            , nt2::table<int> const & alpha
            , int nx
            , int ny
            )
{
    nt2::table<int,nt2::of_size_<9> > invalpha
    (nt2::cons<int>(1, 4, 5, 2, 3, 8, 9, 6, 7));

    nt2::table<T> rhs = fcopy(_,_,invalpha(k));
    T q = T(.5);

    nt2::table<T> f1 = f(_,_,k);
    nt2::table<T> f2 = f(_,_,invalpha(k));

    fcopy(_,_,invalpha(k))
      //bounce back conditions
    = nt2::if_else( (alpha >> (k-2)&1)
          ,nt2::if_else( (bc == 1)
               ,nt2::if_else(q*nt2::ones(nt2::of_size(nx,ny), nt2::meta::as_<T>()) < T(.5)
                    ,(T(1.) - T(2.)*q)*fcopy(_,_,k) + T(2.)*q*f1 + rhs
                    ,(T(1.) - T(.5)/q)*f2 +T(.5)/q*f1 + rhs
                    )
      //anti bounce back conditions
               , nt2::if_else( (bc == 2)
                     ,nt2::if_else(q*nt2::ones(nt2::of_size(nx,ny), nt2::meta::as_<T>())< T(.5)
                          ,-(T(1.) - T(2.)*q)*fcopy(_,_,k) - T(2.)*q*f1 + rhs
                          ,-(T(1.) - T(.5)/q)*f2 -T(.5)/q*f1 + rhs
                          )
      //Neumann conditions
                     ,nt2::if_else( (bc == 3)
                          , f2
                          ,fcopy(_,_,invalpha(k))
                          )
                      )
                )
          ,fcopy(_,_,invalpha(k))
          );
}


template< typename T>
inline void apply_bc( nt2::table<T> const & f
                    , nt2::table<T> & fcopy
                    , nt2::table<int> const & bc
                    , nt2::table<int> const & alpha
                    , int nx
                    , int ny
                    )
{
    for(int k=2;k<=9;k++)
      bouzidi(f, fcopy, k, bc, alpha, nx, ny);
}

template< typename T>
inline void onetime_step( nt2::table<T> & f
                        , nt2::table<T> & fcopy
                        , nt2::table<T> & m
                        , nt2::table<int> & bc
                        , nt2::table<int> & alpha
                        , nt2::table< T, nt2::of_size_<6> > const & s
                        , int nx
                        , int ny
                        )
{
  get_f(f, fcopy,nx,ny);
  apply_bc(f, fcopy, bc, alpha, nx, ny);
  f2m(fcopy, m, nx, ny);
  relaxation(m,s);
  m2f(m, fcopy, nx, ny);
}

#endif
