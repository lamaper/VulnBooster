static int dissect_h225_FeatureDescriptor ( tvbuff_t * tvb _U_ , int offset _U_ , asn1_ctx_t * actx _U_ , proto_tree * tree _U_ , int hf_index _U_ ) {

 actx -> private_data = gef_ctx_alloc ( NULL , "FeatureDescriptor" ) ;
 offset = dissect_h225_GenericData ( tvb , offset , actx , tree , hf_index ) ;

 return offset ;
 }