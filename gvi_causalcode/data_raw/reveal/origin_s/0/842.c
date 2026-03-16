double vp9_vaq_rdmult_ratio ( int energy ) {
 ENERGY_IN_BOUNDS ( energy ) ;
 vp9_clear_system_state ( ) ;
 return RDMULT_RATIO ( energy ) ;
 }