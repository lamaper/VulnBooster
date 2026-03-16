static int dissect_answer_records ( tvbuff_t * tvb , int cur_off , int dns_data_offset , int count , column_info * cinfo , proto_tree * dns_tree , const char * name , packet_info * pinfo , gboolean is_mdns ) {
 int start_off , add_off ;
 proto_tree * qatree = NULL ;
 proto_item * ti = NULL ;
 start_off = cur_off ;
 if ( dns_tree ) {
 qatree = proto_tree_add_subtree ( dns_tree , tvb , start_off , - 1 , ett_dns_ans , & ti , name ) ;
 }
 while ( count -- > 0 ) {
 add_off = dissect_dns_answer ( tvb , cur_off , dns_data_offset , cinfo , qatree , pinfo , is_mdns ) ;
 cur_off += add_off ;
 }
 if ( ti ) {
 proto_item_set_len ( ti , cur_off - start_off ) ;
 }
 return cur_off - start_off ;
 }