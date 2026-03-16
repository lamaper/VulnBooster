int vp9_set_active_map ( VP9_COMP * cpi , unsigned char * map , int rows , int cols ) {
 if ( rows == cpi -> common . mb_rows && cols == cpi -> common . mb_cols ) {
 const int mi_rows = cpi -> common . mi_rows ;
 const int mi_cols = cpi -> common . mi_cols ;
 if ( map ) {
 int r , c ;
 for ( r = 0 ;
 r < mi_rows ;
 r ++ ) {
 for ( c = 0 ;
 c < mi_cols ;
 c ++ ) {
 cpi -> segmentation_map [ r * mi_cols + c ] = ! map [ ( r >> 1 ) * cols + ( c >> 1 ) ] ;
 }
 }
 vp9_enable_segfeature ( & cpi -> common . seg , 1 , SEG_LVL_SKIP ) ;
 vp9_enable_segmentation ( & cpi -> common . seg ) ;
 }
 else {
 vp9_disable_segmentation ( & cpi -> common . seg ) ;
 }
 return 0 ;
 }
 else {
 return - 1 ;
 }
 }