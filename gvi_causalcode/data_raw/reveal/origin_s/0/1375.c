void vp9_decode_frame ( VP9Decoder * pbi , const uint8_t * data , const uint8_t * data_end , const uint8_t * * p_data_end ) {
 VP9_COMMON * const cm = & pbi -> common ;
 MACROBLOCKD * const xd = & pbi -> mb ;
 struct vp9_read_bit_buffer rb = {
 NULL , NULL , 0 , NULL , 0 }
 ;
 uint8_t clear_data [ MAX_VP9_HEADER_SIZE ] ;
 const size_t first_partition_size = read_uncompressed_header ( pbi , init_read_bit_buffer ( pbi , & rb , data , data_end , clear_data ) ) ;
 const int tile_rows = 1 << cm -> log2_tile_rows ;
 const int tile_cols = 1 << cm -> log2_tile_cols ;
 YV12_BUFFER_CONFIG * const new_fb = get_frame_new_buffer ( cm ) ;
 xd -> cur_buf = new_fb ;
 if ( ! first_partition_size ) {
 * p_data_end = data + 1 ;
 return ;
 }
 data += vp9_rb_bytes_read ( & rb ) ;
 if ( ! read_is_valid ( data , first_partition_size , data_end ) ) vpx_internal_error ( & cm -> error , VPX_CODEC_CORRUPT_FRAME , "Truncated packet or corrupt header length" ) ;
 init_macroblockd ( cm , & pbi -> mb ) ;
 if ( cm -> coding_use_prev_mi ) set_prev_mi ( cm ) ;
 else cm -> prev_mi = NULL ;
 setup_plane_dequants ( cm , xd , cm -> base_qindex ) ;
 vp9_setup_block_planes ( xd , cm -> subsampling_x , cm -> subsampling_y ) ;
 cm -> fc = cm -> frame_contexts [ cm -> frame_context_idx ] ;
 vp9_zero ( cm -> counts ) ;
 vp9_zero ( xd -> dqcoeff ) ;
 xd -> corrupted = 0 ;
 new_fb -> corrupted = read_compressed_header ( pbi , data , first_partition_size ) ;
 if ( pbi -> max_threads > 1 && tile_rows == 1 && tile_cols > 1 && cm -> frame_parallel_decoding_mode ) {
 * p_data_end = decode_tiles_mt ( pbi , data + first_partition_size , data_end ) ;
 vp9_loop_filter_frame_mt ( new_fb , pbi , cm , cm -> lf . filter_level , 0 ) ;
 }
 else {
 * p_data_end = decode_tiles ( pbi , data + first_partition_size , data_end ) ;
 }
 new_fb -> corrupted |= xd -> corrupted ;
 if ( ! new_fb -> corrupted ) {
 if ( ! cm -> error_resilient_mode && ! cm -> frame_parallel_decoding_mode ) {
 vp9_adapt_coef_probs ( cm ) ;
 if ( ! frame_is_intra_only ( cm ) ) {
 vp9_adapt_mode_probs ( cm ) ;
 vp9_adapt_mv_probs ( cm , cm -> allow_high_precision_mv ) ;
 }
 }
 else {
 debug_check_frame_counts ( cm ) ;
 }
 }
 else {
 vpx_internal_error ( & cm -> error , VPX_CODEC_CORRUPT_FRAME , "Decode failed. Frame data is corrupted." ) ;
 }
 if ( cm -> refresh_frame_context ) cm -> frame_contexts [ cm -> frame_context_idx ] = cm -> fc ;
 }