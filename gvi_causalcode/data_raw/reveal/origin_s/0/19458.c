void parseDataValue ( proto_tree * tree , tvbuff_t * tvb , packet_info * pinfo , gint * pOffset , const char * szFieldName ) {
 static const int * datavalue_mask [ ] = {
 & hf_opcua_datavalue_mask_valueflag , & hf_opcua_datavalue_mask_statuscodeflag , & hf_opcua_datavalue_mask_sourcetimestampflag , & hf_opcua_datavalue_mask_servertimestampflag , & hf_opcua_datavalue_mask_sourcepicoseconds , & hf_opcua_datavalue_mask_serverpicoseconds , NULL }
 ;
 proto_item * ti ;
 proto_tree * subtree = proto_tree_add_subtree_format ( tree , tvb , * pOffset , - 1 , ett_opcua_datavalue , & ti , "%s: DataValue" , szFieldName ) ;
 gint iOffset = * pOffset ;
 guint8 EncodingMask ;
 EncodingMask = tvb_get_guint8 ( tvb , iOffset ) ;
 proto_tree_add_bitmask ( subtree , tvb , iOffset , hf_opcua_datavalue_mask , ett_opcua_datavalue_encodingmask , datavalue_mask , ENC_LITTLE_ENDIAN ) ;
 iOffset ++ ;
 if ( EncodingMask & DATAVALUE_ENCODINGBYTE_VALUE ) {
 parseVariant ( subtree , tvb , pinfo , & iOffset , "Value" ) ;
 }
 if ( EncodingMask & DATAVALUE_ENCODINGBYTE_STATUSCODE ) {
 parseStatusCode ( subtree , tvb , pinfo , & iOffset , hf_opcua_StatusCode ) ;
 }
 if ( EncodingMask & DATAVALUE_ENCODINGBYTE_SOURCETIMESTAMP ) {
 parseDateTime ( subtree , tvb , pinfo , & iOffset , hf_opcua_SourceTimestamp ) ;
 }
 if ( EncodingMask & DATAVALUE_ENCODINGBYTE_SOURCEPICOSECONDS ) {
 parseUInt16 ( subtree , tvb , pinfo , & iOffset , hf_opcua_SourcePicoseconds ) ;
 }
 if ( EncodingMask & DATAVALUE_ENCODINGBYTE_SERVERTIMESTAMP ) {
 parseDateTime ( subtree , tvb , pinfo , & iOffset , hf_opcua_ServerTimestamp ) ;
 }
 if ( EncodingMask & DATAVALUE_ENCODINGBYTE_SERVERPICOSECONDS ) {
 parseUInt16 ( subtree , tvb , pinfo , & iOffset , hf_opcua_ServerPicoseconds ) ;
 }
 proto_item_set_end ( ti , tvb , iOffset ) ;
 * pOffset = iOffset ;
 }