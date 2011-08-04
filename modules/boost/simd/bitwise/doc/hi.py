[ ## this file was manually modified by jt
    {
     'functor' : {
         'module' : 'boost',
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::dispatch::meta::downgrade<ir_t>::type',
            },
         'type_defs' : ['typedef typename boost::dispatch::meta::as_integer<T,unsigned>::type ir_t;'],
         'types' : ['real_', 'int64_', 'int32_', 'int16_'],
         'simd_types' : ['real_', 'sintgt_8_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 18/02/2011',
             'included' : ['#include<nt2/sdk/meta/downgrade.hpp>'],
             'no_ulp' : 'True',
             'notes' : [],
             'stamp' : 'modified by jt the 18/02/2011',
            },
         'ranges' : {
             'default' : [['boost::simd::Valmin<T>()/2', 'boost::simd::Valmax<T>()/2']],
             'sintgt_8_' :  [['boost::simd::Valmin<T>()/2', 'boost::simd::Valmax<T>()/2']],  
            },
         'specific_values' : {
             'default' : {
                 'boost::simd::One<T>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0.5',},
                 'boost::simd::Zero<T>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0.5',},
                },
             'real_' : {
                 'boost::simd::Nan<T>()' : {'result' : 'boost::simd::Mone<r_t>()','ulp_thresh' : '0.5',},
                 'boost::simd::Zero<T>()' : {'result' : 'boost::simd::Zero<r_t>()','ulp_thresh' : '0.5',},
                },
            },
         'verif_test' : {
             'property_call' : {
                },
             'property_value' : {
                },
             'simd' : {
                },
             'ulp_thresh' : {
                },
            },
        },
    },
]
