GPtrArray * proto_all_finfos ( proto_tree * tree ) {
 ffdata_t ffdata ;
 ffdata . array = g_ptr_array_new ( ) ;
 ffdata . id = 0 ;
 proto_tree_traverse_pre_order ( tree , every_finfo , & ffdata ) ;
 return ffdata . array ;
 }