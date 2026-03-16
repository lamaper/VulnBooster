static int dissect_h245_NonStandardIdentifier ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {

 nsiOID = "" ;
 h221NonStandard = 0 ;
 offset = dissect_per_choice ( tvb , offset , actx , tree , hf_index , ett_h245_NonStandardIdentifier , NonStandardIdentifier_choice , & value ) ;
 switch ( value ) {
 case 0 : nsp_handle = dissector_get_string_handle ( nsp_object_dissector_table , nsiOID ) ;
 break ;
 case 1 : nsp_handle = dissector_get_uint_handle ( nsp_h221_dissector_table , h221NonStandard ) ;
 break ;
 default : nsp_handle = NULL ;
 }
 return offset ;
 }