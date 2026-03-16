static int dissect_query_records ( tvbuff_t * tvb , int cur_off , int dns_data_offset , int count , column_info * cinfo , proto_tree * dns_tree , gboolean isupdate , gboolean is_mdns ) {
 int start_off , add_off ;
 proto_tree * qatree ;
 proto_item * ti ;
 const char * s = ( isupdate ? "Zone" : "Queries" ) ;
 start_off = cur_off ;
 qatree = proto_tree_add_subtree ( dns_tree , tvb , start_off , - 1 , ett_dns_qry , & ti , s ) ;
 while ( count -- > 0 ) {
 add_off = dissect_dns_query ( tvb , cur_off , dns_data_offset , cinfo , qatree , is_mdns ) ;
 cur_off += add_off ;
 }
 if ( ti ) {
 proto_item_set_len ( ti , cur_off - start_off ) ;
 }
 return cur_off - start_off ;
 }