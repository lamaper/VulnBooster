static gchar * rtmpt_get_amf_param ( tvbuff_t * tvb , gint offset , gint param , const gchar * prop ) {
 guint32 remain = tvb_reported_length_remaining ( tvb , offset ) ;
 guint32 itemlen ;
 guint32 iStringLength ;
 while ( remain > 0 && param > 0 ) {
 itemlen = rtmpt_get_amf_length ( tvb , offset ) ;
 offset += itemlen ;
 remain -= itemlen ;
 param -- ;
 }
 if ( remain > 0 && param == 0 ) {
 guint8 iObjType = tvb_get_guint8 ( tvb , offset ) ;
 if ( ! prop && iObjType == AMF0_STRING && remain >= 3 ) {
 iStringLength = tvb_get_ntohs ( tvb , offset + 1 ) ;
 if ( remain >= iStringLength + 3 ) {
 return tvb_get_string_enc ( wmem_packet_scope ( ) , tvb , offset + 3 , iStringLength , ENC_ASCII ) ;
 }
 }
 if ( prop && iObjType == AMF0_OBJECT ) {
 offset ++ ;
 remain -- ;
 while ( remain > 2 ) {
 guint32 iPropLength = tvb_get_ntohs ( tvb , offset ) ;
 if ( remain < 2 + iPropLength + 3 ) break ;
 if ( tvb_strneql ( tvb , offset + 2 , prop , strlen ( prop ) ) == 0 ) {
 if ( tvb_get_guint8 ( tvb , offset + 2 + iPropLength ) != AMF0_STRING ) break ;
 iStringLength = tvb_get_ntohs ( tvb , offset + 2 + iPropLength + 1 ) ;
 if ( remain < 2 + iPropLength + 3 + iStringLength ) break ;
 return tvb_get_string_enc ( wmem_packet_scope ( ) , tvb , offset + 2 + iPropLength + 3 , iStringLength , ENC_ASCII ) ;
 }
 itemlen = rtmpt_get_amf_length ( tvb , offset + 2 + iPropLength ) ;
 offset += 2 + iPropLength + itemlen ;
 remain -= 2 + iPropLength + itemlen ;
 }
 }
 }
 return NULL ;
 }