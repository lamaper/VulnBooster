static void setup_compound_reference_mode ( VP9_COMMON * cm ) {
 if ( cm -> ref_frame_sign_bias [ LAST_FRAME ] == cm -> ref_frame_sign_bias [ GOLDEN_FRAME ] ) {
 cm -> comp_fixed_ref = ALTREF_FRAME ;
 cm -> comp_var_ref [ 0 ] = LAST_FRAME ;
 cm -> comp_var_ref [ 1 ] = GOLDEN_FRAME ;
 }
 else if ( cm -> ref_frame_sign_bias [ LAST_FRAME ] == cm -> ref_frame_sign_bias [ ALTREF_FRAME ] ) {
 cm -> comp_fixed_ref = GOLDEN_FRAME ;
 cm -> comp_var_ref [ 0 ] = LAST_FRAME ;
 cm -> comp_var_ref [ 1 ] = ALTREF_FRAME ;
 }
 else {
 cm -> comp_fixed_ref = LAST_FRAME ;
 cm -> comp_var_ref [ 0 ] = GOLDEN_FRAME ;
 cm -> comp_var_ref [ 1 ] = ALTREF_FRAME ;
 }
 }