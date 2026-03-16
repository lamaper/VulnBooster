static void imc_get_skip_coeff ( IMCContext * q , IMCChannel * chctx ) {
 int i , j ;
 memset ( chctx -> skipFlagBits , 0 , sizeof ( chctx -> skipFlagBits ) ) ;
 memset ( chctx -> skipFlagCount , 0 , sizeof ( chctx -> skipFlagCount ) ) ;
 for ( i = 0 ;
 i < BANDS ;
 i ++ ) {
 if ( ! chctx -> bandFlagsBuf [ i ] || ! chctx -> bandWidthT [ i ] ) continue ;
 if ( ! chctx -> skipFlagRaw [ i ] ) {
 chctx -> skipFlagBits [ i ] = band_tab [ i + 1 ] - band_tab [ i ] ;
 for ( j = band_tab [ i ] ;
 j < band_tab [ i + 1 ] ;
 j ++ ) {
 chctx -> skipFlags [ j ] = get_bits1 ( & q -> gb ) ;
 if ( chctx -> skipFlags [ j ] ) chctx -> skipFlagCount [ i ] ++ ;
 }
 }
 else {
 for ( j = band_tab [ i ] ;
 j < band_tab [ i + 1 ] - 1 ;
 j += 2 ) {
 if ( ! get_bits1 ( & q -> gb ) ) {
 chctx -> skipFlagBits [ i ] ++ ;
 chctx -> skipFlags [ j ] = 1 ;
 chctx -> skipFlags [ j + 1 ] = 1 ;
 chctx -> skipFlagCount [ i ] += 2 ;
 }
 else {
 if ( get_bits1 ( & q -> gb ) ) {
 chctx -> skipFlagBits [ i ] += 2 ;
 chctx -> skipFlags [ j ] = 0 ;
 chctx -> skipFlags [ j + 1 ] = 1 ;
 chctx -> skipFlagCount [ i ] ++ ;
 }
 else {
 chctx -> skipFlagBits [ i ] += 3 ;
 chctx -> skipFlags [ j + 1 ] = 0 ;
 if ( ! get_bits1 ( & q -> gb ) ) {
 chctx -> skipFlags [ j ] = 1 ;
 chctx -> skipFlagCount [ i ] ++ ;
 }
 else {
 chctx -> skipFlags [ j ] = 0 ;
 }
 }
 }
 }
 if ( j < band_tab [ i + 1 ] ) {
 chctx -> skipFlagBits [ i ] ++ ;
 if ( ( chctx -> skipFlags [ j ] = get_bits1 ( & q -> gb ) ) ) chctx -> skipFlagCount [ i ] ++ ;
 }
 }
 }
 }