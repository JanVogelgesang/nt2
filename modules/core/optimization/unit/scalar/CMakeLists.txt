##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
  brent.cpp
  hjmin.cpp
  levenberg.cpp
  neldermead.cpp
rosenbrock.cpp
# List of scalar test files for toolbox optimize
   )

nt2_module_add_tests(core.optimization.scalar.unit ${SOURCES})
