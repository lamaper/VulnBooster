static int dissect_h225_FastStart_item ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {

 char codec_str [ 50 ] ;
 h225_packet_info * h225_pi ;
 codec_str [ 0 ] = '\0' ;
 offset = dissect_per_octet_string ( tvb , offset , actx , tree , hf_index , NO_BOUND , NO_BOUND , FALSE , & value_tvb ) ;
 if ( value_tvb && tvb_reported_length ( value_tvb ) ) {
 dissect_h245_FastStart_OLC ( value_tvb , actx -> pinfo , tree , codec_str ) ;
 }
 h225_pi = ( h225_packet_info * ) p_get_proto_data ( wmem_packet_scope ( ) , actx -> pinfo , proto_h225 , 0 ) ;
 if ( h225_pi != NULL ) {
 g_snprintf ( h225_pi -> frame_label , 50 , "%s %s" , h225_pi -> frame_label , codec_str ) ;
 h225_pi -> is_faststart = TRUE ;
 }
 contains_faststart = TRUE ;
 return offset ;
 }