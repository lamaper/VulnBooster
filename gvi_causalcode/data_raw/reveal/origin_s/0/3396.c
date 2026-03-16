void parseNodeId ( proto_tree * tree , tvbuff_t * tvb , packet_info * pinfo , gint * pOffset , const char * szFieldName ) {
 proto_item * ti ;
 proto_tree * subtree = proto_tree_add_subtree_format ( tree , tvb , * pOffset , - 1 , ett_opcua_nodeid , & ti , "%s: NodeId" , szFieldName ) ;
 gint iOffset = * pOffset ;
 guint8 EncodingMask ;
 EncodingMask = tvb_get_guint8 ( tvb , iOffset ) ;
 proto_tree_add_item ( subtree , hf_opcua_nodeid_encodingmask , tvb , iOffset , 1 , ENC_LITTLE_ENDIAN ) ;
 iOffset ++ ;
 switch ( EncodingMask ) {
 case 0x00 : proto_tree_add_item ( subtree , hf_opcua_nodeid_numeric , tvb , iOffset , 1 , ENC_LITTLE_ENDIAN ) ;
 iOffset += 1 ;
 break ;
 case 0x01 : proto_tree_add_item ( subtree , hf_opcua_nodeid_nsindex , tvb , iOffset , 1 , ENC_LITTLE_ENDIAN ) ;
 iOffset += 1 ;
 proto_tree_add_item ( subtree , hf_opcua_nodeid_numeric , tvb , iOffset , 2 , ENC_LITTLE_ENDIAN ) ;
 iOffset += 2 ;
 break ;
 case 0x02 : proto_tree_add_item ( subtree , hf_opcua_nodeid_nsindex , tvb , iOffset , 2 , ENC_LITTLE_ENDIAN ) ;
 iOffset += 2 ;
 proto_tree_add_item ( subtree , hf_opcua_nodeid_numeric , tvb , iOffset , 4 , ENC_LITTLE_ENDIAN ) ;
 iOffset += 4 ;
 break ;
 case 0x03 : proto_tree_add_item ( subtree , hf_opcua_nodeid_nsindex , tvb , iOffset , 2 , ENC_LITTLE_ENDIAN ) ;
 iOffset += 2 ;
 parseString ( subtree , tvb , pinfo , & iOffset , hf_opcua_nodeid_string ) ;
 break ;
 case 0x04 : proto_tree_add_item ( subtree , hf_opcua_nodeid_nsindex , tvb , iOffset , 2 , ENC_LITTLE_ENDIAN ) ;
 iOffset += 2 ;
 parseGuid ( subtree , tvb , pinfo , & iOffset , hf_opcua_nodeid_guid ) ;
 break ;
 case 0x05 : proto_tree_add_item ( subtree , hf_opcua_nodeid_nsindex , tvb , iOffset , 2 , ENC_LITTLE_ENDIAN ) ;
 iOffset += 2 ;
 parseByteString ( subtree , tvb , pinfo , & iOffset , hf_opcua_nodeid_bytestring ) ;
 break ;
 }
 ;
 proto_item_set_end ( ti , tvb , iOffset ) ;
 * pOffset = iOffset ;
 }