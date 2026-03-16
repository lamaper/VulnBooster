static void RemapHintMask ( HintMask * hm , int mapping [ 96 ] , int max ) {
 HintMask rpl ;
 int i , mb ;
 if ( hm == NULL ) return ;
 if ( max > 96 ) max = 96 ;
 mb = ( max + 7 ) >> 3 ;
 memset ( & rpl , 0 , mb ) ;
 for ( i = 0 ;
 i < max ;
 ++ i ) if ( ( * hm ) [ i >> 3 ] & ( 0x80 >> ( i & 0x7 ) ) ) rpl [ mapping [ i ] >> 3 ] |= ( 0x80 >> ( mapping [ i ] & 0x7 ) ) ;
 memcpy ( hm , & rpl , mb ) ;
 }