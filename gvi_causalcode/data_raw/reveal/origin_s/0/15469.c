int vp8_set_active_map ( VP8_COMP * cpi , unsigned char * map , unsigned int rows , unsigned int cols ) {
 if ( rows == cpi -> common . mb_rows && cols == cpi -> common . mb_cols ) {
 if ( map ) {
 vpx_memcpy ( cpi -> active_map , map , rows * cols ) ;
 cpi -> active_map_enabled = 1 ;
 }
 else cpi -> active_map_enabled = 0 ;
 return 0 ;
 }
 else {
 return - 1 ;
 }
 }