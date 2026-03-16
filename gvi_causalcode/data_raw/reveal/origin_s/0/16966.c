static void dissect_zcl_part_wrhandshakeparam ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , guint * offset ) {
 proto_tree_add_item ( tree , hf_zbee_zcl_part_partitioned_cluster_id , tvb , * offset , 2 , ENC_LITTLE_ENDIAN ) ;
 * offset += 2 ;
 dissect_zcl_write_attr ( tvb , pinfo , tree , offset , ZBEE_ZCL_CID_PARTITION ) ;
 }