static int64_t timebase_units_to_ticks ( const vpx_rational_t * timebase , int64_t n ) {
 return n * TICKS_PER_SEC * timebase -> num / timebase -> den ;
 }