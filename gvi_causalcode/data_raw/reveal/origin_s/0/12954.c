static void gic_dist_writew ( void * opaque , hwaddr offset , uint32_t value ) {
 gic_dist_writeb ( opaque , offset , value & 0xff ) ;
 gic_dist_writeb ( opaque , offset + 1 , value >> 8 ) ;
 }