static int dissect_dns_query ( tvbuff_t * tvb , int offset , int dns_data_offset , column_info * cinfo , proto_tree * dns_tree , gboolean is_mdns ) {
 int len ;
 const guchar * name ;
 gchar * name_out ;
 int name_len ;
 int type ;
 int dns_class ;
 int qu ;
 const char * type_name ;
 int data_start ;
 guint16 labels ;
 proto_tree * q_tree ;
 proto_item * tq ;
 data_start = offset ;
 len = get_dns_name_type_class ( tvb , offset , dns_data_offset , & name , & name_len , & type , & dns_class ) ;
 if ( is_mdns ) {
 qu = dns_class & C_QU ;
 dns_class &= ~ C_QU ;
 }
 else {
 qu = 0 ;
 }
 type_name = val_to_str_ext ( type , & dns_types_vals_ext , "Unknown (%d)" ) ;
 name_out = format_text ( name , strlen ( name ) ) ;
 if ( cinfo != NULL ) {
 col_append_fstr ( cinfo , COL_INFO , "%s %s" , type_name , name_out ) ;
 if ( is_mdns ) {
 col_append_fstr ( cinfo , COL_INFO , ", \"%s\" question" , qu ? "QU" : "QM" ) ;
 }
 }
 if ( dns_tree != NULL ) {
 q_tree = proto_tree_add_subtree_format ( dns_tree , tvb , offset , len , ett_dns_qd , & tq , "%s: type %s, class %s" , name_out , type_name , val_to_str_const ( dns_class , dns_classes , "Unknown" ) ) ;
 if ( is_mdns ) {
 proto_item_append_text ( tq , ", \"%s\" question" , qu ? "QU" : "QM" ) ;
 }
 proto_tree_add_string ( q_tree , hf_dns_qry_name , tvb , offset , name_len , name ) ;
 tq = proto_tree_add_uint ( q_tree , hf_dns_qry_name_len , tvb , offset , name_len , name_len > 1 ? ( guint32 ) strlen ( name ) : 0 ) ;
 PROTO_ITEM_SET_GENERATED ( tq ) ;
 labels = qname_labels_count ( name , name_len ) ;
 tq = proto_tree_add_uint ( q_tree , hf_dns_count_labels , tvb , offset , name_len , labels ) ;
 PROTO_ITEM_SET_GENERATED ( tq ) ;
 offset += name_len ;
 proto_tree_add_item ( q_tree , hf_dns_qry_type , tvb , offset , 2 , ENC_BIG_ENDIAN ) ;
 offset += 2 ;
 if ( is_mdns ) {
 proto_tree_add_uint ( q_tree , hf_dns_qry_class_mdns , tvb , offset , 2 , dns_class ) ;
 proto_tree_add_boolean ( q_tree , hf_dns_qry_qu , tvb , offset , 2 , qu ) ;
 }
 else {
 proto_tree_add_uint ( q_tree , hf_dns_qry_class , tvb , offset , 2 , dns_class ) ;
 }
 offset += 2 ;
 }
 if ( data_start + len != offset ) {
 }
 return len ;
 }