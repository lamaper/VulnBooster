static REFERENCE_MODE read_frame_reference_mode ( const VP9_COMMON * cm , vp9_reader * r ) {
 if ( is_compound_reference_allowed ( cm ) ) {
 return vp9_read_bit ( r ) ? ( vp9_read_bit ( r ) ? REFERENCE_MODE_SELECT : COMPOUND_REFERENCE ) : SINGLE_REFERENCE ;
 }
 else {
 return SINGLE_REFERENCE ;
 }
 }