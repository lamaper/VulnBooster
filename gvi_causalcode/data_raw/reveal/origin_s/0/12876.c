void dissect_unid ( tvbuff_t * tvb , packet_info * pinfo , int offset , proto_item * pi , const char * ssn_name , int hf_ssn_timestamp , int hf_ssn_date , int hf_ssn_time , int hf_macid , gint ett , gint ett_ssn ) {
 proto_tree * tree , * ssn_tree ;
 tree = proto_item_add_subtree ( pi , ett ) ;
 ssn_tree = proto_tree_add_subtree ( tree , tvb , offset , 6 , ett_ssn , NULL , ssn_name ) ;
 dissect_cipsafety_ssn ( ssn_tree , tvb , pinfo , offset , hf_ssn_timestamp , hf_ssn_date , hf_ssn_time ) ;
 proto_tree_add_item ( tree , hf_macid , tvb , offset + 6 , 4 , ENC_LITTLE_ENDIAN ) ;
 }