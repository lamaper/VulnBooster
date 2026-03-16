guint32 getExtensionObjectType ( tvbuff_t * tvb , gint * pOffset ) {
 gint iOffset = * pOffset ;
 guint8 EncodingMask ;
 guint32 Numeric = 0 ;
 EncodingMask = tvb_get_guint8 ( tvb , iOffset ) ;
 iOffset ++ ;
 switch ( EncodingMask ) {
 case 0x00 : Numeric = tvb_get_guint8 ( tvb , iOffset ) ;
 break ;
 case 0x01 : iOffset += 1 ;
 Numeric = tvb_get_letohs ( tvb , iOffset ) ;
 break ;
 case 0x02 : iOffset += 2 ;
 Numeric = tvb_get_letohl ( tvb , iOffset ) ;
 break ;
 case 0x03 : case 0x04 : case 0x05 : case 0x06 : break ;
 }
 ;
 return Numeric ;
 }