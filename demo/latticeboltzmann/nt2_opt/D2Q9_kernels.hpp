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

#include <nt2/linalg/details/blas/mm.hpp>

using namespace nt2;

template< typename T>
inline void relaxation( nt2::table<T> & m
                      , nt2::table<T> const s_
                      )
  {
    T la  = T(1.);
    T rho = T(1.);
    T dummy_ = T(1.)/(la*la*rho);

    m(_,_,4) = m(_,_,4)*(T(1.)-s_(1))
             + s_(1)*(-T(2.)*m(_,_,1)
                     + T(3.)*( dummy_*m(_,_,2)*m(_,_,2)
                             + dummy_*m(_,_,3)*m(_,_,3)
                             )
                     );

    m(_,_,5) = m(_,_,5)*( T(1.)-s_(2))
             + s_(2)*( m(_,_,1)
                     + T(1.5)*( dummy_*m(_,_,2)*m(_,_,2)
                              + dummy_*m(_,_,3)*m(_,_,3)
                              )
                     );

    m(_,_,6) = m(_,_,6)*(T(1.)-s_(3))
             - s_(3)*m(_,_,2)/la;

    m(_,_,7) = m(_,_,7)*(T(1.)-s_(4))
             - s_(4)*m(_,_,3)/la;

    m(_,_,8) = m(_,_,8)*(T(1.)-s_(5))
             + s_(5)*( dummy_*m(_,_,2)*m(_,_,2)
                     - dummy_*m(_,_,3)*m(_,_,3)
                     );

    m(_,_,9) = m(_,_,9)*(T(1.)-s_(6))
             + s_(6)*dummy_*m(_,_,2)*m(_,_,3);
  }

template< typename T>
inline void get_f( nt2::table<T> const & f
                 , nt2::table<T> & fcopy
                 ,int nx
                 ,int ny
                 )
{
   // fcopy(_,_,1) = f(_,_,1);
   // fcopy(_(2,nx),_,2)    = f(_(1,nx-1),_,2);
   // fcopy(_,_(2,ny),3)    = f(_,_(1,ny-1),3);
   // fcopy(_(1,nx-1),_, 4) = f(_(2,nx),_,4);
   // fcopy(_,_(1,ny-1), 5 ) = f(_,_(2,ny), 5 );
   // fcopy(_(2,nx),_(2,ny), 6 ) = f(_(1,nx-1),_(1,ny-1), 6 );
   // fcopy(_(1,nx-1),_(2,ny), 7 ) = f( _(2,nx), _(1,ny-1), 7 );
   // fcopy(_(1,nx-1), _(1,ny-1), 8 ) = f( _(2,nx),_(2,ny), 8 );
   // fcopy(_(2,nx),_(1,ny-1), 9 ) = f(_(1,nx-1),_(2,ny), 9 );

   for(int j=1; j<=ny; j++)
   for(int i=1; i<=nx; i++)
   {
     fcopy(i,j,1) = f(i,j,1);
     fcopy(i,j,2) = (i>1) ? f(i-1,j,2) : T(0.);
     fcopy(i,j,3) = (j>1) ? f(i,j-1,3) : T(0.);
     fcopy(i,j,4) = (i<nx) ? f(i+1,j,4) : T(0.);
     fcopy(i,j,5) = (j<ny)? f(i,j+1,5) : T(0.);
     fcopy(i,j,6) = (i>1 && j>1) ? f(i-1,j-1,6) : T(0.);
     fcopy(i,j,7) = (i<nx && j>1) ? f(i+1,j-1,7) : T(0.);
     fcopy(i,j,8) = (i<nx && j<ny) ? f(i+1,j+1,8): T(0.);
     fcopy(i,j,9) = (i>1 && j<ny) ? f(i-1,j+1,9) : T(0.);
   }
}

template<typename T>
inline void f2m_m2f( nt2::table<T> & in
                   , nt2::table<T> & out
                   , int nx
                   , int ny
                   , nt2::table<T> & inv
                   )
{
   in.resize(nt2::of_size(nx*ny,9));
   out.resize(nt2::of_size(nx*ny,9));

   out = nt2::mtimes(in,inv);

   in.resize(nt2::of_size(nx,ny,9));
   out.resize(nt2::of_size(nx,ny,9));
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

  T q = T(.5);

  fcopy(_,_,invalpha(k))
    //bounce back conditions
  = nt2::if_else( (alpha >> (k-2)&1)
        ,nt2::if_else( (bc == 1)
             ,nt2::if_else(q*nt2::ones(nt2::of_size(nx,ny), nt2::meta::as_<T>()) < T(.5)
                  ,(T(1.) - T(2.)*q)*fcopy(_,_,k) + T(2.)*q*f(_,_,k) + fcopy(_,_,invalpha(k))
                  ,(T(1.) - T(.5)/q)*f(_,_,invalpha(k)) +T(.5)/q*f(_,_,k) + fcopy(_,_,invalpha(k))
                  )
    //anti bounce back conditions
             , nt2::if_else( (bc == 2)
                   ,nt2::if_else(q*nt2::ones(nt2::of_size(nx,ny), nt2::meta::as_<T>())< T(.5)
                        ,-(T(1.) - T(2.)*q)*fcopy(_,_,k) - T(2.)*q*f(_,_,k) + fcopy(_,_,invalpha(k))
                        ,-(T(1.) - T(.5)/q)*f(_,_,invalpha(k)) -T(.5)/q*f(_,_,k) + fcopy(_,_,invalpha(k))
                        )
    //Neumann conditions
                   ,nt2::if_else( (bc == 3)
                        , f(_,_,invalpha(k))
                        , fcopy(_,_,invalpha(k))
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

/********************************************************************************************/
template< typename T>
inline void relaxation_scalar(std::vector<T> & m, std::vector<T> const & s)
{
      T la = T(1.);
      T rhoo = T(1.);
      T dummy = T(1.)/(la*la*rhoo);
      m[3] = m[3]*(T(1.)-s[0]) + s[0]*(-T(2.)*m[0] + T(3.)*(dummy*m[1]*m[1]+dummy*m[2]*m[2]));
      m[4] = m[4]*(T(1.)-s[1]) + s[1]*(m[0] + T(1.5)*(dummy*m[1]*m[1]+dummy*m[2]*m[2]));
      m[5] = m[5]*(T(1.)-s[2]) - s[2]*m[1]/la;
      m[6] = m[6]*(T(1.)-s[3]) - s[3]*m[2]/la;
      m[7] = m[7]*(T(1.)-s[4]) + s[4]*(dummy*m[1]*m[1]-dummy*m[2]*m[2]);
      m[8] = m[8]*(T(1.)-s[5]) + s[5]*dummy*m[1]*m[2];
}

template< typename T>
void get_f_scalar( std::vector<T> const & f
          , std::vector<T> & f_loc
          , int nx
          , int ny
          , int i
          , int j
          )
{
    int dec = nx*ny;
    int ind = 0;

    f_loc[0] = f[i + j*nx + ind];
    ind += dec;

    f_loc[1] = (i>0) ? f[(i-1) + j*nx + ind] : T(0);
    ind += dec;

    f_loc[2] = (j>0) ? f[i + (j-1)*nx + ind] : T(0);
    ind += dec;

    f_loc[3] = (i<nx-1) ? f[(i+1) + j*nx + ind] : T(0);
    ind += dec;

    f_loc[4] = (j<ny-1) ? f[i + (j+1)*nx + ind] : T(0);
    ind += dec;

    f_loc[5] = ((i>0) && (j>0)) ? f[(i-1) + (j-1)*nx + ind] : T(0);
    ind += dec;

    f_loc[6] = ((i<nx-1) && (j>0)) ? f[(i+1) + (j-1)*nx + ind] : T(0);
    ind += dec;

    f_loc[7] = ((i<nx-1) && (j<ny-1)) ? f[(i+1) + (j+1)*nx + ind] : T(0);
    ind += dec;

    f_loc[8] = ((i>0) && (j<ny-1)) ? f[(i-1) + (j+1)*nx + ind] : T(0);
}

template<typename T>
inline void f2m_m2f_scalar(std::vector<T> const & in
                          ,std::vector<T> & out
                          ,std::vector<T> & inv)
{
  T one  = T(1.);
  T zero = T(0.);

  int inc    = 1;
  int nine   = 9;

// Row Major Matrix-Matrix multiplication with Column Major Blas
  nt2::details::
  gemm( "T", "N"
    , &nine, &inc, &nine
    , &one
    , & inv[0], &nine
    , & in[0], &nine
    , &zero
    , &out[0], &nine
    );
}

template< typename T>
inline void set_f_scalar( std::vector<T> & f
          , std::vector<T> const & f_loc
          , int nx
          , int ny
          , int i
          , int j
          )
{
  int dec = nx*ny;
  int ind = i +j*nx;

  for(int k=0;k<9;k++){
      f[ind] = f_loc[k];
      ind += dec;
  }
}

template< typename T>
inline void bouzidi_scalar( std::vector<T> const & f
            , std::vector<T> & f_loc
            , T rhs
            , int alpha
            , int type
            , int nx
            , int ny
            , int i
            , int j
            )
{
    int dec = nx*ny;
    std::vector<int> invalpha={0, 3, 4, 1, 2, 7, 8, 5, 6};
    T f1, f2, q;

    rhs = f_loc[invalpha[alpha]];
    q = T(.5);

    f1 = f[i + j*nx + alpha*dec];
    f2 = f[i + j*nx + invalpha[alpha]*dec];

    //bounce back conditions
    if (type == 1)
    {
        if (q<=T(.5))
            f_loc[invalpha[alpha]] = (T(1.) - T(2.)*q)*f_loc[alpha] + T(2.)*q*f1 + rhs;
        else
            f_loc[invalpha[alpha]] = (T(1.) - T(.5)/q)*f2 +T(.5)/q*f1 + rhs;
    }
    //anti bounce back conditions
    else if (type == 2)
    {
        if (q<T(.5))
            f_loc[invalpha[alpha]] = -(T(1.) - T(2.)*q)*f_loc[alpha] - T(2.)*q*f1 + rhs;
        else
            f_loc[invalpha[alpha]] = -(T(1.) - T(.5)/q)*f2 -T(.5)/q*f1 + rhs;
    }
    //Neumann conditions
    else if (type == 3)
    {
        f_loc[invalpha[alpha]] = f2;
    }
}


template< typename T>
inline void apply_bc_scalar( std::vector<T> const & f
             , std::vector<T> & f_loc
             , int bc
             , std::vector<int> const & alphaTab
             , int nx
             , int ny
             , int i
             , int j
             )
{
    int alpha = alphaTab[i+j*nx];

    for(int k=0;k<8;k++){
        if (alpha>>k&1){
            bouzidi_scalar(f, f_loc, T(0.), k+1, bc, nx, ny, i, j);
        }
    }
}

#endif
