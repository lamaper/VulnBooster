int get_ber_length ( tvbuff_t * tvb , int offset , guint32 * length , gboolean * ind ) {
 return try_get_ber_length ( tvb , offset , length , ind , 1 ) ;
 }