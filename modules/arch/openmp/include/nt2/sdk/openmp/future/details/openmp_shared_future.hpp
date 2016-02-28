//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_OPENMP_FUTURE_DETAILS_OPENMP_SHARED_FUTURE_HPP_INCLUDED
#define NT2_SDK_OPENMP_FUTURE_DETAILS_OPENMP_SHARED_FUTURE_HPP_INCLUDED

#if defined(_OPENMP) && _OPENMP >= 201307 /* OpenMP 4.0 */

#include <omp.h>

#include <future>
#include <memory>
#include <type_traits>
#include <utility>
#include <nt2/sdk/openmp/future/details/openmp_future.hpp>
#include <nt2/sdk/openmp/future/details/openmp_task_wrapper.hpp>

namespace nt2
{
  namespace tag
  {
    template<class T> struct openmp_;
  }

  namespace details
  {
    template<typename result_type>
    struct openmp_shared_future
    {
      openmp_shared_future()
      : ready_(new int(0))
      , raw_future_()
      {}

      openmp_shared_future( std::shared_future<result_type> && other)
      : std::shared_future<result_type>(
        std::forward< std::shared_future<result_type> >(other)
        )
      , ready_( new int(0) )
      , raw_future_(
        std::forward< std::shared_future<result_type> >(other)
        )
      {}

      openmp_shared_future( details::openmp_future<result_type> && other)
      : ready_( other.ready_ )
      , raw_future_( other.share_raw() )
      {}

      openmp_shared_future( details::openmp_future<result_type> & other)
      : ready_( other.ready_ )
      , raw_future_( other.share_raw() )
      {}

      openmp_shared_future( openmp_shared_future && other) = default;
      openmp_shared_future & operator = ( openmp_shared_future && other ) = default;
      openmp_shared_future( openmp_shared_future const & other) = default;
      openmp_shared_future & operator = ( openmp_shared_future const & other ) = default;

      int is_ready() const
      {
        return *ready_;
      }

      inline void wait()
      {
        #pragma omp taskwait
      }

      result_type get()
      {
        if(!is_ready())
        {
          wait();
        }

        return raw_future_.get();
      }

      template<typename F>
      openmp_future<typename std::result_of<F(openmp_shared_future)>::type>
      then(F && f)
      {
        typedef typename std::result_of<F(openmp_shared_future)>::type
        then_result_type;

        typedef typename details::openmp_future< then_result_type >
        then_future_type;

        int * prev( ready_.get() );
// Remove warning because the variable is used in the omp pragma
        boost::ignore_unused(prev);

        details::openmp_task_wrapper<F,then_result_type,openmp_shared_future>
        packaged_task(std::forward<F>(f),openmp_shared_future(*this));

        then_future_type then_future( packaged_task.get_future() );

        int * next( then_future.ready_.get() );

        #pragma omp task \
        firstprivate(packaged_task,prev,next) \
        depend(in: prev[0:1]) \
        depend(out: next[0:1])
        {
          packaged_task();
          *next = 1;
        }

        return then_future;
      }

      std::shared_ptr<int> ready_;

    private:
      std::shared_future<result_type> raw_future_;
    };
  }
}

#endif
#endif
