static const char * get_sep_type ( guint32 interface_id , guint32 adapter_id , guint32 chandle , guint32 direction , guint32 seid , guint32 frame_number ) {
 wmem_tree_key_t key [ 6 ] ;
 wmem_tree_t * subtree ;
 sep_entry_t * sep ;
 key [ 0 ] . length = 1 ;
 key [ 0 ] . key = & interface_id ;
 key [ 1 ] . length = 1 ;
 key [ 1 ] . key = & adapter_id ;
 key [ 2 ] . length = 1 ;
 key [ 2 ] . key = & chandle ;
 key [ 3 ] . length = 1 ;
 key [ 3 ] . key = & direction ;
 key [ 4 ] . length = 1 ;
 key [ 4 ] . key = & seid ;
 key [ 5 ] . length = 0 ;
 key [ 5 ] . key = NULL ;
 subtree = ( wmem_tree_t * ) wmem_tree_lookup32_array ( sep_list , key ) ;
 sep = ( subtree ) ? ( sep_entry_t * ) wmem_tree_lookup32_le ( subtree , frame_number ) : NULL ;
 if ( sep ) {
 return val_to_str_const ( sep -> type , sep_type_vals , "unknown" ) ;
 }
 return "unknown" ;
 }