static int dissect_mswsp ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , gboolean in , void * data ) {
 proto_tree * mswsp_tree = NULL ;
 proto_tree * hdr_tree ;
 proto_item * ti , * hti ;
 guint32 msg ;
 guint32 status ;
 if ( tvb_reported_length ( tvb ) < 16 ) {
 return 0 ;
 }
 col_append_str ( pinfo -> cinfo , COL_PROTOCOL , " WSP" ) ;
 col_set_str ( pinfo -> cinfo , COL_INFO , "WSP " ) ;
 col_append_str ( pinfo -> cinfo , COL_INFO , in ? "Request: " : "Response: " ) ;
 ti = proto_tree_add_item ( tree , proto_mswsp , tvb , 0 , - 1 , ENC_NA ) ;
 mswsp_tree = proto_item_add_subtree ( ti , ett_mswsp ) ;
 hti = proto_tree_add_item ( mswsp_tree , hf_mswsp_hdr , tvb , 0 , 16 , ENC_NA ) ;
 hdr_tree = proto_item_add_subtree ( hti , ett_mswsp_hdr ) ;
 proto_tree_add_item_ret_uint ( hdr_tree , hf_mswsp_hdr_msg , tvb , 0 , 4 , ENC_LITTLE_ENDIAN , & msg ) ;
 proto_item_append_text ( hti , " %s" , val_to_str ( msg , VALS ( msg_ids ) , "(Unknown: 0x%x)" ) ) ;
 proto_tree_add_item_ret_uint ( hdr_tree , hf_mswsp_hdr_status , tvb , 4 , 4 , ENC_LITTLE_ENDIAN , & status ) ;
 if ( ! in || status != 0 ) {
 proto_item_append_text ( hti , " %s" , val_to_str ( status , VALS ( dcom_hresult_vals ) , "(Unknown: 0x%x)" ) ) ;
 }
 proto_tree_add_checksum ( hdr_tree , tvb , 8 , hf_mswsp_hdr_checksum , - 1 , NULL , pinfo , 0 , ENC_LITTLE_ENDIAN , PROTO_CHECKSUM_NO_FLAGS ) ;
 proto_tree_add_item ( hdr_tree , hf_mswsp_hdr_reserved , tvb , 12 , 4 , ENC_LITTLE_ENDIAN ) ;
 switch ( msg ) {
 case 0xC8 : dissect_CPMConnect ( tvb , pinfo , tree , in , data ) ;
 break ;
 case 0xC9 : dissect_CPMDisconnect ( tvb , pinfo , tree , in , data ) ;
 break ;
 case 0xCA : dissect_CPMCreateQuery ( tvb , pinfo , tree , in , data ) ;
 break ;
 case 0xCB : dissect_CPMFreeCursor ( tvb , pinfo , tree , in , data ) ;
 break ;
 case 0xCC : dissect_CPMGetRows ( tvb , pinfo , tree , in , data ) ;
 break ;
 case 0xCD : dissect_CPMRatioFinished ( tvb , pinfo , tree , in , data ) ;
 break ;
 case 0xCE : dissect_CPMCompareBmk ( tvb , pinfo , tree , in , data ) ;
 break ;
 case 0xCF : dissect_CPMGetApproximatePosition ( tvb , pinfo , tree , in , data ) ;
 break ;
 case 0xD0 : dissect_CPMSetBindings ( tvb , pinfo , tree , in , data ) ;
 break ;
 case 0xD1 : dissect_CPMGetNotify ( tvb , pinfo , tree , in , data ) ;
 break ;
 case 0xD2 : dissect_CPMSendNotifyOut ( tvb , pinfo , tree , in , data ) ;
 break ;
 case 0xD7 : dissect_CPMGetQueryStatus ( tvb , pinfo , tree , in , data ) ;
 break ;
 case 0xD9 : dissect_CPMCiState ( tvb , pinfo , tree , in , data ) ;
 break ;
 case 0xE4 : dissect_CPMFetchValue ( tvb , pinfo , tree , in , data ) ;
 break ;
 case 0xE7 : dissect_CPMGetQueryStatusEx ( tvb , pinfo , tree , in , data ) ;
 break ;
 case 0xE8 : dissect_CPMRestartPosition ( tvb , pinfo , tree , in , data ) ;
 break ;
 case 0xEC : dissect_CPMSetCatState ( tvb , pinfo , tree , in , data ) ;
 break ;
 case 0xF1 : dissect_CPMGetRowsetNotify ( tvb , pinfo , tree , in , data ) ;
 break ;
 case 0xF2 : dissect_CPMFindIndices ( tvb , pinfo , tree , in , data ) ;
 break ;
 case 0xF3 : dissect_CPMSetScopePrioritization ( tvb , pinfo , tree , in , data ) ;
 break ;
 case 0xF4 : dissect_CPMGetScopeStatistics ( tvb , pinfo , tree , in , data ) ;
 break ;
 default : return 0 ;
 }
 return tvb_reported_length ( tvb ) ;
 }