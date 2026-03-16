int ffv1_allocate_initial_states ( FFV1Context * f ) {
 int i ;
 for ( i = 0 ;
 i < f -> quant_table_count ;
 i ++ ) {
 f -> initial_states [ i ] = av_malloc ( f -> context_count [ i ] * sizeof ( * f -> initial_states [ i ] ) ) ;
 if ( ! f -> initial_states [ i ] ) return AVERROR ( ENOMEM ) ;
 memset ( f -> initial_states [ i ] , 128 , f -> context_count [ i ] * sizeof ( * f -> initial_states [ i ] ) ) ;
 }
 return 0 ;
 }