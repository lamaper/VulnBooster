void proto_tree_prime_hfid ( proto_tree * tree _U_ , const gint hfid ) {
 header_field_info * hfinfo ;
 PROTO_REGISTRAR_GET_NTH ( hfid , hfinfo ) ;
 hfinfo -> ref_type = HF_REF_TYPE_DIRECT ;
 if ( hfinfo -> parent != - 1 ) {
 header_field_info * parent_hfinfo ;
 PROTO_REGISTRAR_GET_NTH ( hfinfo -> parent , parent_hfinfo ) ;
 if ( parent_hfinfo -> ref_type != HF_REF_TYPE_DIRECT ) parent_hfinfo -> ref_type = HF_REF_TYPE_INDIRECT ;
 }
 }