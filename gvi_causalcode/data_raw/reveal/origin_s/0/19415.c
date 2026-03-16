static guint32 rtmpt_get_amf_txid ( tvbuff_t * tvb , gint offset ) {
 guint32 remain = tvb_reported_length_remaining ( tvb , offset ) ;
 if ( remain > 0 ) {
 guint32 itemlen = rtmpt_get_amf_length ( tvb , offset ) ;
 if ( remain < itemlen ) return 0 ;
 offset += itemlen ;
 remain -= itemlen ;
 }
 if ( remain >= 9 ) {
 guint8 iObjType = tvb_get_guint8 ( tvb , offset ) ;
 if ( iObjType == AMF0_NUMBER ) {
 return ( guint32 ) tvb_get_ntohieee_double ( tvb , offset + 1 ) ;
 }
 }
 return 0 ;
 }