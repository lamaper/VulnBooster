static void cpu_get_fp80 ( uint64_t * pmant , uint16_t * pexp , floatx80 f ) {
 CPU_LDoubleU temp ;
 temp . d = f ;
 * pmant = temp . l . lower ;
 * pexp = temp . l . upper ;
 }