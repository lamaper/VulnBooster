static unsigned int sse_thresh ( BLOCK_SIZE bs , int increase_denoising ) {
 return widths [ bs ] * heights [ bs ] * ( increase_denoising ? 60 : 40 ) ;
 }