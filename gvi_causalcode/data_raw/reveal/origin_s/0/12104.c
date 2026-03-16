static inline const guint8 * get_uint_string_value ( wmem_allocator_t * scope , proto_tree * tree , tvbuff_t * tvb , gint start , gint length , gint * ret_length , const guint encoding ) {
 guint32 n ;
 const guint8 * value ;
 n = get_uint_value ( tree , tvb , start , length , encoding & ~ ENC_CHARENCODING_MASK ) ;
 value = tvb_get_string_enc ( scope , tvb , start + length , n , encoding ) ;
 length += n ;
 * ret_length = length ;
 return value ;
 }