static void i_free_all ( gs_memory_t * mem , uint free_mask , client_name_t cname ) {
 gs_ref_memory_t * imem = ( gs_ref_memory_t * ) mem ;
 struct free_data fd ;
 fd . imem = imem ;
 fd . allocator = NULL ;
 if ( free_mask & FREE_ALL_DATA && imem -> root != NULL ) {
 clump_splay_app ( imem -> root , imem , free_all_not_allocator , & fd ) ;
 imem -> root = fd . allocator ;
 if ( fd . allocator ) fd . allocator -> parent = fd . allocator -> left = fd . allocator -> right = NULL ;
 }
 if ( free_mask & FREE_ALL_ALLOCATOR ) {
 clump_splay_app ( imem -> root , imem , free_all_allocator , & fd ) ;
 }
 }