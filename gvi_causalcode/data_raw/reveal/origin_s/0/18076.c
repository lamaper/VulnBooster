static gint64 get_varint64 ( tvbuff_t * tvb , gint offset , gint bytes_left , gint * len ) {
 guint8 b ;
 gint64 result = 0 ;
 * len = 0 ;
 while ( ( * len ) < bytes_left ) {
 b = tvb_get_guint8 ( tvb , offset + ( * len ) ) ;
 result |= ( ( gint64 ) b & 0x7f ) << ( ( * len ) * 7 ) ;
 ( * len ) ++ ;
 if ( ( b & 0x80 ) == 0 ) {
 break ;
 }
 }
 return result ;
 }