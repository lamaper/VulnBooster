static void ps2_common_post_load ( PS2State * s ) {
 PS2Queue * q = & s -> queue ;
 uint8_t i , size ;
 uint8_t tmp_data [ PS2_QUEUE_SIZE ] ;
 size = ( q -> count < 0 || q -> count > PS2_QUEUE_SIZE ) ? 0 : q -> count ;
 for ( i = 0 ;
 i < size ;
 i ++ ) {
 if ( q -> rptr < 0 || q -> rptr >= sizeof ( q -> data ) ) {
 q -> rptr = 0 ;
 }
 tmp_data [ i ] = q -> data [ q -> rptr ++ ] ;
 }
 memcpy ( q -> data , tmp_data , size ) ;
 q -> rptr = 0 ;
 q -> wptr = size ;
 q -> count = size ;
 s -> update_irq ( s -> update_arg , q -> count != 0 ) ;
 }