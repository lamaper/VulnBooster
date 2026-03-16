static void ttafilter_init ( TTAFilter * c , int32_t shift ) {
 memset ( c , 0 , sizeof ( TTAFilter ) ) ;
 c -> shift = shift ;
 c -> round = shift_1 [ shift - 1 ] ;
 }