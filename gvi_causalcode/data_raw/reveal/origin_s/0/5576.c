static gint dissect_rtmpt_body_command ( tvbuff_t * tvb , gint offset , proto_tree * rtmpt_tree , gboolean amf3 ) {
 gboolean amf3_encoding = FALSE ;
 if ( amf3 ) {
 offset ++ ;
 }
 while ( tvb_reported_length_remaining ( tvb , offset ) > 0 ) {
 if ( amf3_encoding ) offset = dissect_amf3_value_type ( tvb , offset , rtmpt_tree , NULL ) ;
 else offset = dissect_amf0_value_type ( tvb , offset , rtmpt_tree , & amf3_encoding , NULL ) ;
 }
 return offset ;
 }