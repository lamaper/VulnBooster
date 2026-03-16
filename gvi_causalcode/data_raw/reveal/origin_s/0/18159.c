static gint32 get_int_value ( proto_tree * tree , tvbuff_t * tvb , gint offset , gint length , const guint encoding ) {
 gint32 value ;
 gboolean length_error ;
 switch ( length ) {
 case 1 : value = ( gint8 ) tvb_get_guint8 ( tvb , offset ) ;
 break ;
 case 2 : value = ( gint16 ) ( encoding ? tvb_get_letohs ( tvb , offset ) : tvb_get_ntohs ( tvb , offset ) ) ;
 break ;
 case 3 : value = encoding ? tvb_get_letoh24 ( tvb , offset ) : tvb_get_ntoh24 ( tvb , offset ) ;
 if ( value & 0x00800000 ) {
 value |= 0xFF000000 ;
 }
 break ;
 case 4 : value = encoding ? tvb_get_letohl ( tvb , offset ) : tvb_get_ntohl ( tvb , offset ) ;
 break ;
 default : if ( length < 1 ) {
 length_error = TRUE ;
 value = 0 ;
 }
 else {
 length_error = FALSE ;
 value = encoding ? tvb_get_letohl ( tvb , offset ) : tvb_get_ntohl ( tvb , offset ) ;
 }
 report_type_length_mismatch ( tree , "a signed integer" , length , length_error ) ;
 break ;
 }
 return value ;
 }