proto_item * parseStatusCode ( proto_tree * tree , tvbuff_t * tvb , packet_info * pinfo _U_ , gint * pOffset , int hfIndex ) {
 proto_item * item = NULL ;
 guint32 uStatusCode = 0 ;
 const gchar * szStatusCode = NULL ;
 item = proto_tree_add_item ( tree , hfIndex , tvb , * pOffset , 4 , ENC_LITTLE_ENDIAN ) ;
 uStatusCode = tvb_get_letohl ( tvb , * pOffset ) ;
 szStatusCode = val_to_str_const ( uStatusCode & 0xFFFF0000 , g_statusCodes , "Unknown Status Code" ) ;
 proto_item_append_text ( item , " [%s]" , szStatusCode ) ;
 if ( uStatusCode & 0x0000FFFF ) {
 gint iOffset = * pOffset ;
 proto_tree * flags_tree ;
 proto_item * ti_inner ;
 flags_tree = proto_item_add_subtree ( item , ett_opcua_statuscode ) ;
 proto_tree_add_item ( flags_tree , hf_opcua_status_StructureChanged , tvb , iOffset , 2 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( flags_tree , hf_opcua_status_SemanticsChanged , tvb , iOffset , 2 , ENC_LITTLE_ENDIAN ) ;
 ti_inner = proto_tree_add_item ( flags_tree , hf_opcua_status_InfoType , tvb , iOffset , 2 , ENC_LITTLE_ENDIAN ) ;
 switch ( uStatusCode & 0x00000C00 ) {
 case STATUSCODE_INFOTYPE_DATAVALUE : {
 proto_tree * tree_inner ;
 tree_inner = proto_item_add_subtree ( ti_inner , ett_opcua_statuscode_info ) ;
 proto_tree_add_item ( tree_inner , hf_opcua_status_Limit , tvb , iOffset , 2 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( tree_inner , hf_opcua_status_InfoBit_Limit_Overflow , tvb , iOffset , 2 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( tree_inner , hf_opcua_status_InfoBit_Historian_MultiValue , tvb , iOffset , 2 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( tree_inner , hf_opcua_status_InfoBit_Historian_ExtraData , tvb , iOffset , 2 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( tree_inner , hf_opcua_status_InfoBit_Historian_Partial , tvb , iOffset , 2 , ENC_LITTLE_ENDIAN ) ;
 proto_tree_add_item ( tree_inner , hf_opcua_status_Historian , tvb , iOffset , 2 , ENC_LITTLE_ENDIAN ) ;
 }
 default : break ;
 }
 }
 * pOffset += 4 ;
 return item ;
 }