static void get_hfi_length ( header_field_info * hfinfo , tvbuff_t * tvb , const gint start , gint * length , gint * item_length ) {
 gint length_remaining ;
 DISSECTOR_ASSERT ( tvb != NULL || * length == 0 ) ;
 if ( * length == - 1 ) {
 switch ( hfinfo -> type ) {
 case FT_PROTOCOL : case FT_NONE : case FT_BYTES : case FT_STRING : case FT_STRINGZPAD : * length = tvb_captured_length ( tvb ) ? tvb_ensure_captured_length_remaining ( tvb , start ) : 0 ;
 DISSECTOR_ASSERT ( * length >= 0 ) ;
 break ;
 case FT_STRINGZ : break ;
 default : THROW ( ReportedBoundsError ) ;
 DISSECTOR_ASSERT_NOT_REACHED ( ) ;
 }
 * item_length = * length ;
 }
 else {
 * item_length = * length ;
 if ( hfinfo -> type == FT_PROTOCOL || hfinfo -> type == FT_NONE ) {
 if ( tvb ) {
 length_remaining = tvb_captured_length_remaining ( tvb , start ) ;
 if ( * item_length < 0 || ( * item_length > 0 && ( length_remaining < * item_length ) ) ) * item_length = length_remaining ;
 }
 }
 if ( * item_length < 0 ) {
 THROW ( ReportedBoundsError ) ;
 }
 }
 }