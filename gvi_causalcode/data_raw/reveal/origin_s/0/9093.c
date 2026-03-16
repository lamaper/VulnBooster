static void vc1_smooth_overlap_filter_iblk ( VC1Context * v ) {
 MpegEncContext * s = & v -> s ;
 int mb_pos ;
 if ( v -> condover == CONDOVER_NONE ) return ;
 mb_pos = s -> mb_x + s -> mb_y * s -> mb_stride ;
 if ( v -> condover == CONDOVER_ALL || v -> pq >= 9 || v -> over_flags_plane [ mb_pos ] ) {
 if ( s -> mb_x && ( v -> condover == CONDOVER_ALL || v -> pq >= 9 || v -> over_flags_plane [ mb_pos - 1 ] ) ) {
 v -> vc1dsp . vc1_h_s_overlap ( v -> block [ v -> left_blk_idx ] [ 1 ] , v -> block [ v -> cur_blk_idx ] [ 0 ] ) ;
 v -> vc1dsp . vc1_h_s_overlap ( v -> block [ v -> left_blk_idx ] [ 3 ] , v -> block [ v -> cur_blk_idx ] [ 2 ] ) ;
 if ( ! ( s -> flags & CODEC_FLAG_GRAY ) ) {
 v -> vc1dsp . vc1_h_s_overlap ( v -> block [ v -> left_blk_idx ] [ 4 ] , v -> block [ v -> cur_blk_idx ] [ 4 ] ) ;
 v -> vc1dsp . vc1_h_s_overlap ( v -> block [ v -> left_blk_idx ] [ 5 ] , v -> block [ v -> cur_blk_idx ] [ 5 ] ) ;
 }
 }
 v -> vc1dsp . vc1_h_s_overlap ( v -> block [ v -> cur_blk_idx ] [ 0 ] , v -> block [ v -> cur_blk_idx ] [ 1 ] ) ;
 v -> vc1dsp . vc1_h_s_overlap ( v -> block [ v -> cur_blk_idx ] [ 2 ] , v -> block [ v -> cur_blk_idx ] [ 3 ] ) ;
 if ( s -> mb_x == s -> mb_width - 1 ) {
 if ( ! s -> first_slice_line && ( v -> condover == CONDOVER_ALL || v -> pq >= 9 || v -> over_flags_plane [ mb_pos - s -> mb_stride ] ) ) {
 v -> vc1dsp . vc1_v_s_overlap ( v -> block [ v -> top_blk_idx ] [ 2 ] , v -> block [ v -> cur_blk_idx ] [ 0 ] ) ;
 v -> vc1dsp . vc1_v_s_overlap ( v -> block [ v -> top_blk_idx ] [ 3 ] , v -> block [ v -> cur_blk_idx ] [ 1 ] ) ;
 if ( ! ( s -> flags & CODEC_FLAG_GRAY ) ) {
 v -> vc1dsp . vc1_v_s_overlap ( v -> block [ v -> top_blk_idx ] [ 4 ] , v -> block [ v -> cur_blk_idx ] [ 4 ] ) ;
 v -> vc1dsp . vc1_v_s_overlap ( v -> block [ v -> top_blk_idx ] [ 5 ] , v -> block [ v -> cur_blk_idx ] [ 5 ] ) ;
 }
 }
 v -> vc1dsp . vc1_v_s_overlap ( v -> block [ v -> cur_blk_idx ] [ 0 ] , v -> block [ v -> cur_blk_idx ] [ 2 ] ) ;
 v -> vc1dsp . vc1_v_s_overlap ( v -> block [ v -> cur_blk_idx ] [ 1 ] , v -> block [ v -> cur_blk_idx ] [ 3 ] ) ;
 }
 }
 if ( s -> mb_x && ( v -> condover == CONDOVER_ALL || v -> over_flags_plane [ mb_pos - 1 ] ) ) {
 if ( ! s -> first_slice_line && ( v -> condover == CONDOVER_ALL || v -> pq >= 9 || v -> over_flags_plane [ mb_pos - s -> mb_stride - 1 ] ) ) {
 v -> vc1dsp . vc1_v_s_overlap ( v -> block [ v -> topleft_blk_idx ] [ 2 ] , v -> block [ v -> left_blk_idx ] [ 0 ] ) ;
 v -> vc1dsp . vc1_v_s_overlap ( v -> block [ v -> topleft_blk_idx ] [ 3 ] , v -> block [ v -> left_blk_idx ] [ 1 ] ) ;
 if ( ! ( s -> flags & CODEC_FLAG_GRAY ) ) {
 v -> vc1dsp . vc1_v_s_overlap ( v -> block [ v -> topleft_blk_idx ] [ 4 ] , v -> block [ v -> left_blk_idx ] [ 4 ] ) ;
 v -> vc1dsp . vc1_v_s_overlap ( v -> block [ v -> topleft_blk_idx ] [ 5 ] , v -> block [ v -> left_blk_idx ] [ 5 ] ) ;
 }
 }
 v -> vc1dsp . vc1_v_s_overlap ( v -> block [ v -> left_blk_idx ] [ 0 ] , v -> block [ v -> left_blk_idx ] [ 2 ] ) ;
 v -> vc1dsp . vc1_v_s_overlap ( v -> block [ v -> left_blk_idx ] [ 1 ] , v -> block [ v -> left_blk_idx ] [ 3 ] ) ;
 }
 }