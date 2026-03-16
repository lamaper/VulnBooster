static int dissect_pvfs_string ( tvbuff_t * tvb , proto_tree * tree , int hfindex , int offset , const char * * string_buffer_ret ) {
 return dissect_pvfs_opaque_data ( tvb , offset , tree , NULL , hfindex , FALSE , 0 , TRUE , string_buffer_ret ) ;
 }