static gint rtmpt_get_amf_length ( tvbuff_t * tvb , gint offset ) {
 guint8 iObjType ;
 gint remain = tvb_reported_length_remaining ( tvb , offset ) ;
 guint32 depth = 0 ;
 gint itemlen = 0 ;
 gint rv = 0 ;
 while ( rv == 0 || depth > 0 ) {
 if ( depth > 0 ) {
 if ( remain - rv < 2 ) return remain ;
 itemlen = tvb_get_ntohs ( tvb , offset + rv ) + 2 ;
 if ( remain - rv < itemlen + 1 ) return remain ;
 rv += itemlen ;
 }
 if ( remain - rv < 1 ) return remain ;
 iObjType = tvb_get_guint8 ( tvb , offset + rv ) ;
 if ( depth > 0 && itemlen == 2 && iObjType == AMF0_END_OF_OBJECT ) {
 rv ++ ;
 depth -- ;
 continue ;
 }
 switch ( iObjType ) {
 case AMF0_NUMBER : itemlen = 9 ;
 break ;
 case AMF0_BOOLEAN : itemlen = 2 ;
 break ;
 case AMF0_STRING : if ( remain - rv < 3 ) return remain ;
 itemlen = tvb_get_ntohs ( tvb , offset + rv + 1 ) + 3 ;
 break ;
 case AMF0_NULL : case AMF0_UNDEFINED : case AMF0_UNSUPPORTED : itemlen = 1 ;
 break ;
 case AMF0_DATE : itemlen = 11 ;
 break ;
 case AMF0_LONG_STRING : case AMF0_XML : if ( remain - rv < 5 ) return remain ;
 itemlen = tvb_get_ntohl ( tvb , offset + rv + 1 ) + 5 ;
 break ;
 case AMF0_INT64 : itemlen = 9 ;
 break ;
 case AMF0_OBJECT : itemlen = 1 ;
 depth ++ ;
 break ;
 case AMF0_ECMA_ARRAY : itemlen = 5 ;
 depth ++ ;
 break ;
 default : return remain ;
 }
 if ( remain - rv < itemlen ) return remain ;
 rv += itemlen ;
 }
 return rv ;
 }