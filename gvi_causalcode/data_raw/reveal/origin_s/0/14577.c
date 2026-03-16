static int dissect_nlm_shareres ( tvbuff_t * tvb , int offset , packet_info * pinfo _U_ , proto_tree * tree , int version _U_ ) {
 guint32 nlm_stat ;
 offset = dissect_rpc_data ( tvb , tree , hf_nlm_cookie , offset ) ;
 nlm_stat = tvb_get_ntohl ( tvb , offset ) ;
 if ( nlm_stat ) {
 col_append_fstr ( pinfo -> cinfo , COL_INFO , " %s" , val_to_str ( nlm_stat , names_nlm_stats , "Unknown Status (%u)" ) ) ;
 }
 offset = dissect_rpc_uint32 ( tvb , tree , hf_nlm_stat , offset ) ;
 offset = dissect_rpc_uint32 ( tvb , tree , hf_nlm_sequence , offset ) ;
 return offset ;
 }