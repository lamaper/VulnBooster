double vp9_vaq_inv_q_ratio ( int energy ) {
 ENERGY_IN_BOUNDS ( energy ) ;
 vp9_clear_system_state ( ) ;
 return Q_RATIO ( - energy ) ;
 }