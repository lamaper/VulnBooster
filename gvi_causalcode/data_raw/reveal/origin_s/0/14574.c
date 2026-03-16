static int absdiff_thresh ( BLOCK_SIZE bs , int increase_denoising ) {
 ( void ) bs ;
 return 3 + ( increase_denoising ? 1 : 0 ) ;
 }