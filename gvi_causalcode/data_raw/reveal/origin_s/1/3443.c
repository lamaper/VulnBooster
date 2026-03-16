static int dissect_h225_DialedDigits ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {

 guint len = 0 ;
 h225_packet_info * h225_pi ;
 offset = dissect_per_restricted_character_string ( tvb , offset , actx , tree , hf_index , 1 , 128 , FALSE , "0123456789#*," , 13 , & value_tvb ) ;
 h225_pi = ( h225_packet_info * ) p_get_proto_data ( wmem_packet_scope ( ) , actx -> pinfo , proto_h225 , 0 ) ;
 if ( h225_pi && h225_pi -> is_destinationInfo == TRUE ) {
 if ( value_tvb ) {
 len = tvb_reported_length ( value_tvb ) ;
 if ( len > sizeof h225_pi -> dialedDigits - 1 ) len = sizeof h225_pi -> dialedDigits - 1 ;
 tvb_memcpy ( value_tvb , ( guint8 * ) h225_pi -> dialedDigits , 0 , len ) ;
 }
 h225_pi -> dialedDigits [ len ] = '\0' ;
 h225_pi -> is_destinationInfo = FALSE ;
 }
 return offset ;
 }