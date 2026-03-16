void parseNodeClassMask ( proto_tree * tree , tvbuff_t * tvb , packet_info * pinfo _U_ , gint * pOffset ) {
 static const int * nodeclass_mask [ ] = {
 & hf_opcua_nodeClassMask_object , & hf_opcua_nodeClassMask_variable , & hf_opcua_nodeClassMask_method , & hf_opcua_nodeClassMask_objecttype , & hf_opcua_nodeClassMask_variabletype , & hf_opcua_nodeClassMask_referencetype , & hf_opcua_nodeClassMask_datatype , & hf_opcua_nodeClassMask_view , NULL }
 ;
 guint8 NodeClassMask = tvb_get_guint8 ( tvb , * pOffset ) ;
 if ( NodeClassMask == NODECLASSMASK_ALL ) {
 proto_tree_add_item ( tree , hf_opcua_nodeClassMask_all , tvb , * pOffset , 4 , ENC_LITTLE_ENDIAN ) ;
 }
 else {
 proto_tree_add_bitmask ( tree , tvb , * pOffset , hf_opcua_nodeClassMask , ett_opcua_nodeClassMask , nodeclass_mask , ENC_LITTLE_ENDIAN ) ;
 }
 * pOffset += 4 ;
 }