static int dissect_h245_T_unsigned32Min ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {

 guint8 * buf ;
 tvbuff_t * value_tvb ;
 gef_ctx_t * gefx ;
 offset = dissect_per_constrained_integer ( tvb , offset , actx , tree , hf_index , 0U , 4294967295U , & value , FALSE ) ;
 gefx = gef_ctx_get ( actx -> private_data ) ;
 if ( gefx ) {
 buf = ( guint8 * ) wmem_new ( actx -> pinfo -> pool , guint32 ) ;
 phton32 ( buf , value ) ;
 value_tvb = tvb_new_child_real_data ( tvb , buf , sizeof ( guint32 ) , sizeof ( guint32 ) ) ;
 add_new_data_source ( actx -> pinfo , value_tvb , "unsigned32Min" ) ;
 dissector_try_string ( gef_content_dissector_table , gefx -> key , value_tvb , actx -> pinfo , tree , actx ) ;
 }
 return offset ;
 }