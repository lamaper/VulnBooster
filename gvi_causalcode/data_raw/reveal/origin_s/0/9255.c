static guint32 get_uint32 ( tvbuff_t * tvb , gint32 offset , gint encoding ) {
 return ( ENC_BIG_ENDIAN == encoding ) ? tvb_get_ntohl ( tvb , offset ) : tvb_get_letohl ( tvb , offset ) ;
 }