static int s_aos_available ( stream * s , gs_offset_t * pl ) {
 * pl = ( ( aos_state_t * ) s -> state ) -> file_sz - stell ( s ) ;
 return 0 ;
 }