[ ## this file was manually modified by jt
    {
     'functor' : {
         'arity' : '2',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'T',
            },
         'simd_types' : [],
         'special' : ['cephes'],
         'type_defs' : [],
         'types' : ['real_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 01/03/2011',
             'included' : ['#include <nt2/include/functions/beta.hpp>'],
             'notes' : [],
             'stamp' : 'modified by jt the 01/03/2011',
            },
         'ranges' : {
             'default' : [['T(0)', 'T(100)'], ['T(0)', 'T(100)']],
            },
         'specific_values' : {
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['nt2::cephes::beta(a0,a1)'],
                },
             'property_value' : {
                 'default' : ['nt2::beta(a0,a1)'],
                },
             'simd' : {
                },
             'ulp_thresh' : {
                 'default' : ['1000'],
                },
            },
        },
    },
]
