static void truespeech_synth ( TSContext * dec , int16_t * out , int quart ) {
 int i , k ;
 int t [ 8 ] ;
 int16_t * ptr0 , * ptr1 ;
 ptr0 = dec -> tmp1 ;
 ptr1 = dec -> filters + quart * 8 ;
 for ( i = 0 ;
 i < 60 ;
 i ++ ) {
 int sum = 0 ;
 for ( k = 0 ;
 k < 8 ;
 k ++ ) sum += ptr0 [ k ] * ptr1 [ k ] ;
 sum = ( sum + ( out [ i ] << 12 ) + 0x800 ) >> 12 ;
 out [ i ] = av_clip ( sum , - 0x7FFE , 0x7FFE ) ;
 for ( k = 7 ;
 k > 0 ;
 k -- ) ptr0 [ k ] = ptr0 [ k - 1 ] ;
 ptr0 [ 0 ] = out [ i ] ;
 }
 for ( i = 0 ;
 i < 8 ;
 i ++ ) t [ i ] = ( ts_decay_35_64 [ i ] * ptr1 [ i ] ) >> 15 ;
 ptr0 = dec -> tmp2 ;
 for ( i = 0 ;
 i < 60 ;
 i ++ ) {
 int sum = 0 ;
 for ( k = 0 ;
 k < 8 ;
 k ++ ) sum += ptr0 [ k ] * t [ k ] ;
 for ( k = 7 ;
 k > 0 ;
 k -- ) ptr0 [ k ] = ptr0 [ k - 1 ] ;
 ptr0 [ 0 ] = out [ i ] ;
 out [ i ] = ( ( out [ i ] << 12 ) - sum ) >> 12 ;
 }
 for ( i = 0 ;
 i < 8 ;
 i ++ ) t [ i ] = ( ts_decay_3_4 [ i ] * ptr1 [ i ] ) >> 15 ;
 ptr0 = dec -> tmp3 ;
 for ( i = 0 ;
 i < 60 ;
 i ++ ) {
 int sum = out [ i ] << 12 ;
 for ( k = 0 ;
 k < 8 ;
 k ++ ) sum += ptr0 [ k ] * t [ k ] ;
 for ( k = 7 ;
 k > 0 ;
 k -- ) ptr0 [ k ] = ptr0 [ k - 1 ] ;
 ptr0 [ 0 ] = av_clip ( ( sum + 0x800 ) >> 12 , - 0x7FFE , 0x7FFE ) ;
 sum = ( ( ptr0 [ 1 ] * ( dec -> filtval - ( dec -> filtval >> 2 ) ) ) >> 4 ) + sum ;
 sum = sum - ( sum >> 3 ) ;
 out [ i ] = av_clip ( ( sum + 0x800 ) >> 12 , - 0x7FFE , 0x7FFE ) ;
 }
 }