static const unsigned char * seq_unpack_rle_block ( const unsigned char * src , const unsigned char * src_end , unsigned char * dst , int dst_size ) {
 int i , len , sz ;
 GetBitContext gb ;
 int code_table [ 64 ] ;
 init_get_bits ( & gb , src , ( src_end - src ) * 8 ) ;
 for ( i = 0 , sz = 0 ;
 i < 64 && sz < dst_size ;
 i ++ ) {
 if ( get_bits_left ( & gb ) < 4 ) return NULL ;
 code_table [ i ] = get_sbits ( & gb , 4 ) ;
 sz += FFABS ( code_table [ i ] ) ;
 }
 src += ( get_bits_count ( & gb ) + 7 ) / 8 ;
 for ( i = 0 ;
 i < 64 && dst_size > 0 ;
 i ++ ) {
 len = code_table [ i ] ;
 if ( len < 0 ) {
 len = - len ;
 if ( src_end - src < 1 ) return NULL ;
 memset ( dst , * src ++ , FFMIN ( len , dst_size ) ) ;
 }
 else {
 if ( src_end - src < len ) return NULL ;
 memcpy ( dst , src , FFMIN ( len , dst_size ) ) ;
 src += len ;
 }
 dst += len ;
 dst_size -= len ;
 }
 return src ;
 }