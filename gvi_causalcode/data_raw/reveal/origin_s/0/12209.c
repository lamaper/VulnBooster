static inline const guint8 * get_stringz_value ( wmem_allocator_t * scope , proto_tree * tree , tvbuff_t * tvb , gint start , gint length , gint * ret_length , const guint encoding ) {
 const guint8 * value ;
 if ( length < - 1 ) {
 report_type_length_mismatch ( tree , "a string" , length , TRUE ) ;
 }
 if ( length == - 1 ) {
 value = tvb_get_stringz_enc ( scope , tvb , start , & length , encoding ) ;
 }
 else if ( length == 0 ) {
 value = "[Empty]" ;
 }
 else {
 value = tvb_get_string_enc ( scope , tvb , start , length , encoding ) ;
 }
 * ret_length = length ;
 return value ;
 }