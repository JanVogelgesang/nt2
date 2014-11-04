//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#include <nt2/table.hpp>

#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/reshape.hpp>

#include <nt2/sdk/meta/as.hpp>

#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/unit/details/prng.hpp>
#include <nt2/sdk/bench/metric/absolute_time.hpp>
#include <nt2/sdk/bench/metric/speedup.hpp>
#include <nt2/sdk/bench/setup/fixed.hpp>
#include <nt2/sdk/bench/protocol/until.hpp>
#include <nt2/sdk/bench/stats/median.hpp>

#include <iostream>

#include "D2Q9_kernels.hpp"

using namespace nt2;
using namespace nt2::bench;

template<typename T> struct latticeboltzmann_nt2_opt
{

  void operator()()
  {
    int max_steps = 10;

    nt2::table<T> * fout = &fcopy;
    nt2::table<T> * fin  = &f;


    for(int step = 0; step<max_steps; step++)
    {
        onetime_step<T>
        (*fin, *fout, m, bc, alpha, s, nx, ny);

        std::swap(fout,fin);
     }

   }

  friend std::ostream& operator<<(std::ostream& os, latticeboltzmann_nt2_opt<T> const& p)
  {
    return os << "(" << p.size()<< ")";
  }

  int size() const { return nx*ny; }

  latticeboltzmann_nt2_opt(int size_)
  :  nx(size_),ny(size_/2)
  , Longueur(2.), Largeur(1.)
  , xmin(0.0), xmax(Longueur), ymin(-0.5*Largeur), ymax(0.5*Largeur)
  , dx(Longueur/nx)
  , vit_schema(1)
  , dt(dx/vit_schema)
  , L_obs(0.25), l_obs(0.05)
  , posx_obs(0.25), posy_obs(0.5)
  , Re(100.0)
  , max_velocity(0.05)
  , rhoo(1.)
  , mu(rhoo*max_velocity*L_obs/Re)
  , zeta(3.*mu)
  , dummy(3.0/(vit_schema*vit_schema*rhoo*dt))
  , s3(1.0/(0.5+zeta*dummy))
  , s4(s3)
  , s5(s4)
  , s6(s4)
  , s7(1.0/(0.5+mu*dummy))
  , s8(s7)
  , s     (nt2::cons(s3,s4,s5,s6,s7,s8))
  , bc    (nt2::of_size(nx, ny))
  , m     (nt2::of_size(nx, ny, 9))
  , f     (nt2::of_size(nx, ny, 9))
  , fcopy (nt2::of_size(nx, ny, 9))
  , rhs   (nt2::of_size(nx, ny, 9))
  , alpha (nt2::of_size(nx, ny))
  , s1x(1 + (posx_obs - l_obs/2)/dx), s2x(1 + (posx_obs + l_obs/2)/dx)
  , s1y(1 + (posy_obs - L_obs/2)/dx), s2y(1 + (posy_obs + L_obs/2)/dx)
  {
    bc    = nt2::zeros(nt2::of_size(nx, ny), nt2::meta::as_<int>());
    alpha = nt2::zeros(nt2::of_size(nx, ny), nt2::meta::as_<int>());;
    m     = nt2::zeros(nt2::of_size(nx, ny, 9), nt2::meta::as_<T>());
    f     = nt2::zeros(nt2::of_size(nx, ny, 9), nt2::meta::as_<T>());
    fcopy = nt2::zeros(nt2::of_size(nx, ny, 9), nt2::meta::as_<T>());
    rhs   = nt2::zeros(nt2::of_size(nx, ny, 9), nt2::meta::as_<T>());

    // Set boundary conditions outside the domain and on the rectangular obstacle
    bc(1,_)   = 1;
    bc(nx,_)  = 3;
    bc(_, 1)  = 1;
    bc(_, ny) = 1;

    m(_,_,1) = rhoo;
    m(_,_,2) = rhoo*max_velocity;

    relaxation( m
              , nt2::table< T,nt2::of_size_<6> >
                (nt2::ones(6,nt2::meta::as_<T>()))
              );
    m2f(m,f,nx,ny);

    bc(_(s1x,s2x-1),_(s1y,s2y-1)) = 1;

    // Set in binary format which velocity is involved on the boundary
    // Example 01001: we have the velocity 1 and 4 on the boundary

    // on the rectangular obstacle
    // moment 1
    alpha(s1x-1, _(s1y,s2y-1)) += 1<<0;
    // moment 2
    alpha(_(s1x,s2x-1), s1y-1) += 1<<1;
    // moment 3
    alpha(s2x, _(s1y,s2y-1))   += 1<<2;
    // moment 4
    alpha(_(s1x,s2x-1),s2y)    += 1<<3;
    // // moment 5
    alpha(_(s1x-1,s2x-2),s1y-1) += 1<<4;
    alpha(s1x-1, _(s1y,s2y-2))  += 1<<4;
    // moment 6
    alpha(_(s1x+1,s2x),s1y-1) += 1<<5;
    alpha(s2x,_(s1y,s2y-2))   += 1<<5;
    // moment 7
    alpha(s2x,_(s1y+1,s2y))   += 1<<6;
    alpha(_(s1x+1,s2x-1),s2y) += 1<<6;
    // moment 8
    alpha(s1x-1,_(s1y+1,s2y)) += 1<<7;
    alpha(_(s1x,s2x-2),s2y)   += 1<<7;

    // outside the domain
    alpha(2,_) = 1<<5 | 1<<2 | 1<<6;
    alpha(nx-1,_) += 1<<4 | 1<<0 | 1<<7;
    alpha(_,2) += 1<<3;
    alpha(_,ny-1) += 1<<1;
    alpha(_(3,nx-2),2) += 1<<6 | 1<<7;
    alpha(_(3,nx-2),ny-1) += 1<<5 | 1<<4;

    // Set rhs on the boundary
    // right border
    f(nx,_,4)          += -f(nx-1,_,2);
    f(nx,_(1,nx-1),7)  += -f(nx-1,_(2,ny),9);
    f(nx,_(2,ny),8)    += -f(nx-1,_(1,ny-1),6);
    // left border
    f(1,_,2)           += -f(2,_,4);
    f(1,_(2,ny),9)     += -f(2,_(1,ny-1),7);
    f(1,_(1,ny-1),6)   += -f(2,_(2,ny),8);
    // top border
    f(_,ny,5)          += -f(_,ny-1,4);
    f(_(2,nx-1),ny,8)  += -f(_(1,nx-2),ny-1,6);
    f(_(2,nx-1),ny,9)  += -f(_(3,nx),ny-1,7);
    // bottom border
    f(_,1,3)           += -f(_,2,5);
    f(_(2,nx-1),1,6)   += -f(_(3,nx),2,8);
    f(_(2,nx-1),1,7)   += -f(_(1,nx-2),2,9);
    // rectangular obstacle
    f(_(s1x,s2x-1),_(s1y,s2y-1),_) = T(0);
  }

  private:

  // Domain, space and time step
  int nx, ny;

  T Longueur, Largeur
   ,xmin, xmax, ymin, ymax
   ,dx = Longueur/nx
   ,vit_schema
   ,dt;

  // Obstacle
  T L_obs, l_obs
   ,posx_obs, posy_obs;

// Physical parameters
  T Re
   ,max_velocity
   ,rhoo
   ,mu
   ,zeta
   ,dummy
   ,s3
   ,s4
   ,s5
   ,s6
   ,s7
   ,s8;

   nt2::table<T,nt2::of_size_<6> > s;

// Set boundary conditions outside the domain and on the rectangular obstacle
   nt2::table<int> bc;

   nt2::table<T>  m
                 ,f,fcopy
                 ,rhs;

   nt2::table<int> alpha;

   int s1x, s2x
      ,s1y, s2y;
};

NT2_REGISTER_BENCHMARK_TPL( latticeboltzmann_nt2_opt, (float) )
{
  run_until_with< latticeboltzmann_nt2_opt<T> > ( 3., 1
                                  , fixed(1024)
                                  , absolute_time<stats::median_>()
                                  );
}
