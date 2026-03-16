static int dissect_h245_T_standardOid ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {

 gef_ctx_t * gefx ;
 offset = dissect_per_object_identifier_str ( tvb , offset , actx , tree , hf_index , & standard_oid_str ) ;
 gefx = gef_ctx_get ( actx -> private_data ) ;
 if ( gefx ) gefx -> id = standard_oid_str ;
 if ( strcmp ( standard_oid_str , "0.0.8.235.0.3.76" ) == 0 ) {
 if ( upcoming_channel ) upcoming_channel -> srtp_flag = TRUE ;
 }
 if ( ! h245_lc_dissector && strcmp ( standard_oid_str , "0.0.8.245.1.1.1" ) == 0 ) h245_lc_dissector = amr_handle ;
 return offset ;
 }