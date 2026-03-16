proto_item * parseXmlElement ( proto_tree * tree , tvbuff_t * tvb , packet_info * pinfo , gint * pOffset , int hfIndex ) {
 return parseByteString ( tree , tvb , pinfo , pOffset , hfIndex ) ;
 }