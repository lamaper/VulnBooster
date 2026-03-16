static void init_encode_frame_mb_context ( VP9_COMP * cpi ) {
 MACROBLOCK * const x = & cpi -> mb ;
 VP9_COMMON * const cm = & cpi -> common ;
 MACROBLOCKD * const xd = & x -> e_mbd ;
 const int aligned_mi_cols = mi_cols_aligned_to_sb ( cm -> mi_cols ) ;
 vp9_setup_src_planes ( x , cpi -> Source , 0 , 0 ) ;
 vp9_setup_block_planes ( & x -> e_mbd , cm -> subsampling_x , cm -> subsampling_y ) ;
 vpx_memset ( xd -> above_context [ 0 ] , 0 , sizeof ( * xd -> above_context [ 0 ] ) * * aligned_mi_cols * MAX_MB_PLANE ) ;
 vpx_memset ( xd -> above_seg_context , 0 , sizeof ( * xd -> above_seg_context ) * aligned_mi_cols ) ;
 }