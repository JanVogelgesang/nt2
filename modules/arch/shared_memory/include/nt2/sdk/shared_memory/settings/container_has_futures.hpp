//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_SHARED_MEMORY_SETTINGS_CONTAINER_HAS_FUTURES_HPP_INCLUDED
#define NT2_SDK_SHARED_MEMORY_SETTINGS_CONTAINER_HAS_FUTURES_HPP_INCLUDED

#include <nt2/sdk/shared_memory/future.hpp>
#include <boost/swap.hpp>
#include <vector>
#include <set>
#include <cstdio>


namespace nt2 { namespace details {

  template <typename Arch>
  struct container_has_futures
  {
    typedef typename nt2::make_future<Arch,int >::type future;
    typedef typename std::set<
      container_has_futures *
    >::iterator call_it;

    inline bool empty()
    {
      return futures_.empty();
    }

    inline future & tile(std::size_t m, std::size_t n)
    {
      return futures_[m + n*NTiles_.first];
    }

    inline future const & tile(std::size_t m, std::size_t n) const
    {
      return futures_[m + n*NTiles_.first];
    }

    template<typename Iterator>
    inline Iterator leftup(Iterator raw, std::size_t m, std::size_t n)
    {
      return raw +  size_.first * grain_.second * n + grain_.first * m ;
    }

    inline void synchronize()
    {
      if (!calling_cards_.empty())
      {
        for(call_it n=calling_cards_.begin();
            n!=calling_cards_.end();
            ++n)
        {
            (*n)->synchronize();
        }
        calling_cards_.clear();
      }

      if (!futures_.empty())
      {
        for(std::size_t n=0;n<futures_.size();++n)
        {
            futures_[n].get();
        }
        futures_.clear();
      }
    }

    ~container_has_futures()
    {
      //synchronize();
    }

    //===========================================
    // vector of Futures
    //===========================================
    std::vector<future> futures_;
    std::set< container_has_futures *> calling_cards_;
    std::pair<std::size_t,std::size_t> grain_;
    std::pair<std::size_t,std::size_t> NTiles_;
    std::pair<std::size_t,std::size_t> size_;

  };

} }

#endif
