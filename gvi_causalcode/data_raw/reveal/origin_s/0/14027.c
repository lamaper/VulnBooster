static guint32 get_message_header_endianness ( tvbuff_t * tvb , gint offset ) {
 guint8 endianness ;
 guint encoding ;
 endianness = tvb_get_guint8 ( tvb , offset + ENDIANNESS_OFFSET ) ;
 switch ( endianness ) {
 case 'l' : encoding = ENC_LITTLE_ENDIAN ;
 break ;
 case 'B' : encoding = ENC_BIG_ENDIAN ;
 break ;
 default : encoding = ENC_ALLJOYN_BAD_ENCODING ;
 break ;
 }
 return encoding ;
 }