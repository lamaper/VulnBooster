static int64_t ticks_to_timebase_units ( const vpx_rational_t * timebase , int64_t n ) {
 const int64_t round = TICKS_PER_SEC * timebase -> num / 2 - 1 ;
 return ( n * timebase -> den + round ) / timebase -> num / TICKS_PER_SEC ;
 }