static guint16 compute_key_id ( tvbuff_t * tvb , int offset , int size , guint8 algo ) {
 guint32 ac ;
 guint8 c1 , c2 ;
 DISSECTOR_ASSERT ( size >= 4 ) ;
 switch ( algo ) {
 case DNS_ALGO_RSAMD5 : return ( guint16 ) ( tvb_get_guint8 ( tvb , offset + size - 3 ) << 8 ) + tvb_get_guint8 ( tvb , offset + size - 2 ) ;
 default : for ( ac = 0 ;
 size > 1 ;
 size -= 2 , offset += 2 ) {
 c1 = tvb_get_guint8 ( tvb , offset ) ;
 c2 = tvb_get_guint8 ( tvb , offset + 1 ) ;
 ac += ( c1 << 8 ) + c2 ;
 }
 if ( size > 0 ) {
 c1 = tvb_get_guint8 ( tvb , offset ) ;
 ac += c1 << 8 ;
 }
 ac += ( ac >> 16 ) & 0xffff ;
 return ( guint16 ) ( ac & 0xffff ) ;
 }
 }