void vp9_entropy_mode_init ( ) {
 vp9_tokens_from_tree ( intra_mode_encodings , vp9_intra_mode_tree ) ;
 vp9_tokens_from_tree ( switchable_interp_encodings , vp9_switchable_interp_tree ) ;
 vp9_tokens_from_tree ( partition_encodings , vp9_partition_tree ) ;
 vp9_tokens_from_tree ( inter_mode_encodings , vp9_inter_mode_tree ) ;
 }