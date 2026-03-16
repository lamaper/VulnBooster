static uint32_t gic_dist_readw ( void * opaque , hwaddr offset ) {
 uint32_t val ;
 val = gic_dist_readb ( opaque , offset ) ;
 val |= gic_dist_readb ( opaque , offset + 1 ) << 8 ;
 return val ;
 }