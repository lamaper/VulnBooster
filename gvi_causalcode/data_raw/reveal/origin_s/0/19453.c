static gboolean protocol_is_ardp ( tvbuff_t * tvb ) {
 guint8 flags , header_length ;
 gint length = tvb_captured_length ( tvb ) ;
 if ( length < ARDP_HEADER_LEN_OFFSET + 1 ) {
 return FALSE ;
 }
 header_length = 2 * tvb_get_guint8 ( tvb , ARDP_HEADER_LEN_OFFSET ) ;
 flags = tvb_get_guint8 ( tvb , 0 ) ;
 if ( ( flags & ARDP_SYN ) && header_length != ARDP_SYN_FIXED_HDR_LEN ) {
 return FALSE ;
 }
 if ( ! ( flags & ARDP_SYN ) && header_length < ARDP_FIXED_HDR_LEN ) {
 return FALSE ;
 }
 return TRUE ;
 }