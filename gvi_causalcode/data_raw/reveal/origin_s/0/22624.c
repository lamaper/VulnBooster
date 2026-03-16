static floatx80 cpu_set_fp80 ( uint64_t mant , uint16_t upper ) {
 CPU_LDoubleU temp ;
 temp . l . upper = upper ;
 temp . l . lower = mant ;
 return temp . d ;
 }