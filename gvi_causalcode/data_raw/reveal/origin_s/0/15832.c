static vp9_variance_fn_t get_block_variance_fn ( BLOCK_SIZE bsize ) {
 switch ( bsize ) {
 case BLOCK_8X8 : return vp9_mse8x8 ;
 case BLOCK_16X8 : return vp9_mse16x8 ;
 case BLOCK_8X16 : return vp9_mse8x16 ;
 default : return vp9_mse16x16 ;
 }
 }