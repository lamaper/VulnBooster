static void qcms_modular_transform_release ( struct qcms_modular_transform * transform ) {
 struct qcms_modular_transform * next_transform ;
 while ( transform != NULL ) {
 next_transform = transform -> next_transform ;
 if ( transform -> input_clut_table_r + transform -> input_clut_table_length == transform -> input_clut_table_g && transform -> input_clut_table_g + transform -> input_clut_table_length == transform -> input_clut_table_b ) {
 if ( transform -> input_clut_table_r ) free ( transform -> input_clut_table_r ) ;
 }
 else {
 if ( transform -> input_clut_table_r ) free ( transform -> input_clut_table_r ) ;
 if ( transform -> input_clut_table_g ) free ( transform -> input_clut_table_g ) ;
 if ( transform -> input_clut_table_b ) free ( transform -> input_clut_table_b ) ;
 }
 if ( transform -> r_clut + 1 == transform -> g_clut && transform -> g_clut + 1 == transform -> b_clut ) {
 if ( transform -> r_clut ) free ( transform -> r_clut ) ;
 }
 else {
 if ( transform -> r_clut ) free ( transform -> r_clut ) ;
 if ( transform -> g_clut ) free ( transform -> g_clut ) ;
 if ( transform -> b_clut ) free ( transform -> b_clut ) ;
 }
 if ( transform -> output_clut_table_r + transform -> output_clut_table_length == transform -> output_clut_table_g && transform -> output_clut_table_g + transform -> output_clut_table_length == transform -> output_clut_table_b ) {
 if ( transform -> output_clut_table_r ) free ( transform -> output_clut_table_r ) ;
 }
 else {
 if ( transform -> output_clut_table_r ) free ( transform -> output_clut_table_r ) ;
 if ( transform -> output_clut_table_g ) free ( transform -> output_clut_table_g ) ;
 if ( transform -> output_clut_table_b ) free ( transform -> output_clut_table_b ) ;
 }
 if ( transform -> output_gamma_lut_r ) free ( transform -> output_gamma_lut_r ) ;
 if ( transform -> output_gamma_lut_g ) free ( transform -> output_gamma_lut_g ) ;
 if ( transform -> output_gamma_lut_b ) free ( transform -> output_gamma_lut_b ) ;
 free ( transform ) ;
 transform = next_transform ;
 }
 }