//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_SHARED_MEMORY_DETAILS_THEN_WORKER_HPP_INCLUDED
#define NT2_SDK_SHARED_MEMORY_DETAILS_THEN_WORKER_HPP_INCLUDED

#include <nt2/sdk/shared_memory/future.hpp>
#include <boost/move/move.hpp>

namespace nt2 { namespace details {

    template<class Worker>
    struct then_worker
    {
        typedef int result_type;
        typedef std::pair<std::size_t,std::size_t> Pair;

        then_worker(BOOST_FWD_REF(Worker) w,
                    Pair offset,
                    Pair chunk
                    )
        :w_(boost::forward<Worker>(w))
        ,offset_(offset),chunk_(chunk)
        {}

        template<typename T>
        int operator()(T) const
        {
            w_(offset_,chunk_);
            return 0;
        }

        mutable Worker w_;
        Pair offset_;
        Pair chunk_;

        private:
        then_worker& operator=(then_worker const&);
    };

} }

#endif
