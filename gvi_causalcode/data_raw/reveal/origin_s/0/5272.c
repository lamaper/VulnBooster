void BrotliStateInitWithCustomAllocators ( BrotliState * s , brotli_alloc_func alloc_func , brotli_free_func free_func , void * opaque ) {
 if ( ! alloc_func ) {
 s -> alloc_func = DefaultAllocFunc ;
 s -> free_func = DefaultFreeFunc ;
 s -> memory_manager_opaque = 0 ;
 }
 else {
 s -> alloc_func = alloc_func ;
 s -> free_func = free_func ;
 s -> memory_manager_opaque = opaque ;
 }
 BrotliInitBitReader ( & s -> br ) ;
 s -> state = BROTLI_STATE_UNINITED ;
 s -> substate_metablock_header = BROTLI_STATE_METABLOCK_HEADER_NONE ;
 s -> substate_tree_group = BROTLI_STATE_TREE_GROUP_NONE ;
 s -> substate_context_map = BROTLI_STATE_CONTEXT_MAP_NONE ;
 s -> substate_uncompressed = BROTLI_STATE_UNCOMPRESSED_NONE ;
 s -> substate_huffman = BROTLI_STATE_HUFFMAN_NONE ;
 s -> substate_decode_uint8 = BROTLI_STATE_DECODE_UINT8_NONE ;
 s -> substate_read_block_length = BROTLI_STATE_READ_BLOCK_LENGTH_NONE ;
 s -> buffer_length = 0 ;
 s -> loop_counter = 0 ;
 s -> pos = 0 ;
 s -> rb_roundtrips = 0 ;
 s -> partial_pos_out = 0 ;
 s -> block_type_trees = NULL ;
 s -> block_len_trees = NULL ;
 s -> ringbuffer = NULL ;
 s -> context_map = NULL ;
 s -> context_modes = NULL ;
 s -> dist_context_map = NULL ;
 s -> context_map_slice = NULL ;
 s -> dist_context_map_slice = NULL ;
 s -> sub_loop_counter = 0 ;
 s -> literal_hgroup . codes = NULL ;
 s -> literal_hgroup . htrees = NULL ;
 s -> insert_copy_hgroup . codes = NULL ;
 s -> insert_copy_hgroup . htrees = NULL ;
 s -> distance_hgroup . codes = NULL ;
 s -> distance_hgroup . htrees = NULL ;
 s -> custom_dict = NULL ;
 s -> custom_dict_size = 0 ;
 s -> is_last_metablock = 0 ;
 s -> window_bits = 0 ;
 s -> max_distance = 0 ;
 s -> dist_rb [ 0 ] = 16 ;
 s -> dist_rb [ 1 ] = 15 ;
 s -> dist_rb [ 2 ] = 11 ;
 s -> dist_rb [ 3 ] = 4 ;
 s -> dist_rb_idx = 0 ;
 s -> block_type_trees = NULL ;
 s -> block_len_trees = NULL ;
 s -> symbol_lists = & s -> symbols_lists_array [ BROTLI_HUFFMAN_MAX_CODE_LENGTH + 1 ] ;
 s -> mtf_upper_bound = 255 ;
 }