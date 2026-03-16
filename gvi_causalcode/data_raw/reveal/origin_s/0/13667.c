static void dissect_fhandle_data ( tvbuff_t * tvb , int offset , packet_info * pinfo _U_ , proto_tree * tree , guint32 * hash ) {
 guint32 fhhash ;
 guint32 i ;
 if ( ! tvb_bytes_exist ( tvb , offset , PVFS2_FH_LENGTH ) ) goto type_ready ;
 for ( fhhash = 0 , i = 0 ;
 i < ( PVFS2_FH_LENGTH - 3 ) ;
 i += 4 ) {
 guint32 val ;
 val = tvb_get_ntohl ( tvb , offset + i ) ;
 fhhash ^= val ;
 fhhash += val ;
 }
 proto_tree_add_uint ( tree , hf_pvfs_fh_hash , tvb , offset , PVFS2_FH_LENGTH , fhhash ) ;
 if ( hash ) * hash = fhhash ;
 type_ready : dissect_fhandle_data_unknown ( tvb , offset , tree ) ;
 }