static int dissect_h245_T_forwardLogicalChannelParameters ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {

 h245_lc_dissector = NULL ;
 offset = dissect_per_sequence ( tvb , offset , actx , tree , hf_index , ett_h245_T_forwardLogicalChannelParameters , T_forwardLogicalChannelParameters_sequence ) ;
 if ( h223_lc_params_temp && h245_lc_dissector ) h223_lc_params_temp -> subdissector = h245_lc_dissector ;
 else if ( h223_lc_params_temp ) h223_lc_params_temp -> subdissector = data_handle ;
 if ( upcoming_channel && codec_type ) {
 g_strlcpy ( upcoming_channel -> data_type_str , codec_type , sizeof ( upcoming_channel -> data_type_str ) ) ;
 }
 upcoming_channel = NULL ;
 return offset ;
 }