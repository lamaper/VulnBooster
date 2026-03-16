static void alloc_mode_context ( VP9_COMMON * cm , int num_4x4_blk , PICK_MODE_CONTEXT * ctx ) {
 const int num_blk = ( num_4x4_blk < 4 ? 4 : num_4x4_blk ) ;
 const int num_pix = num_blk << 4 ;
 int i , k ;
 ctx -> num_4x4_blk = num_blk ;
 CHECK_MEM_ERROR ( cm , ctx -> zcoeff_blk , vpx_calloc ( num_4x4_blk , sizeof ( uint8_t ) ) ) ;
 for ( i = 0 ;
 i < MAX_MB_PLANE ;
 ++ i ) {
 for ( k = 0 ;
 k < 3 ;
 ++ k ) {
 CHECK_MEM_ERROR ( cm , ctx -> coeff [ i ] [ k ] , vpx_memalign ( 16 , num_pix * sizeof ( * ctx -> coeff [ i ] [ k ] ) ) ) ;
 CHECK_MEM_ERROR ( cm , ctx -> qcoeff [ i ] [ k ] , vpx_memalign ( 16 , num_pix * sizeof ( * ctx -> qcoeff [ i ] [ k ] ) ) ) ;
 CHECK_MEM_ERROR ( cm , ctx -> dqcoeff [ i ] [ k ] , vpx_memalign ( 16 , num_pix * sizeof ( * ctx -> dqcoeff [ i ] [ k ] ) ) ) ;
 CHECK_MEM_ERROR ( cm , ctx -> eobs [ i ] [ k ] , vpx_memalign ( 16 , num_pix * sizeof ( * ctx -> eobs [ i ] [ k ] ) ) ) ;
 ctx -> coeff_pbuf [ i ] [ k ] = ctx -> coeff [ i ] [ k ] ;
 ctx -> qcoeff_pbuf [ i ] [ k ] = ctx -> qcoeff [ i ] [ k ] ;
 ctx -> dqcoeff_pbuf [ i ] [ k ] = ctx -> dqcoeff [ i ] [ k ] ;
 ctx -> eobs_pbuf [ i ] [ k ] = ctx -> eobs [ i ] [ k ] ;
 }
 }
 }