unsigned int vp9_vaq_segment_id ( int energy ) {
 ENERGY_IN_BOUNDS ( energy ) ;
 return SEGMENT_ID ( energy ) ;
 }