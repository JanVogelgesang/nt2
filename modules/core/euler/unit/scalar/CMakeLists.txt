##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
  betaln.cpp
  erfinv.cpp
  erfcinv.cpp
  spence.cpp
  stirling.cpp
  dawson.cpp
  digamma.cpp
  signgam.cpp
  gammaln.cpp
  gamma.cpp
  gammainc.cpp
  dgammainc.cpp
  gammaincinv.cpp
  beta.cpp
  expni.cpp
  erf.cpp
  erfc.cpp
  erfcx.cpp
# List of scalar test files for toolbox euler
   )

nt2_module_add_tests(core.euler.scalar.unit ${SOURCES})
