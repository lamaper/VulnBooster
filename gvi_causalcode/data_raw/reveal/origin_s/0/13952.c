static void append_struct_signature ( proto_item * item , guint8 * signature , gint signature_max_length , const guint8 type_stop ) {
 int depth = 0 ;
 guint8 type_start ;
 gint signature_length = 0 ;
 proto_item_append_text ( item , "%c" , ' ' ) ;
 type_start = * signature ;
 do {
 if ( type_start == * signature ) {
 depth ++ ;
 }
 if ( type_stop == * signature ) {
 depth -- ;
 }
 proto_item_append_text ( item , "%c" , * signature ++ ) ;
 }
 while ( depth > 0 && ++ signature_length < signature_max_length ) ;
 if ( signature_length >= signature_max_length ) {
 proto_item_append_text ( item , "... Invalid signature!" ) ;
 }
 }