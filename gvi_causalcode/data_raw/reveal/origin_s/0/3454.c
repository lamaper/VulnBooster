void armv7m_nvic_set_pending ( void * opaque , int irq ) {
 nvic_state * s = ( nvic_state * ) opaque ;
 if ( irq >= 16 ) irq += 16 ;
 gic_set_pending_private ( & s -> gic , 0 , irq ) ;
 }