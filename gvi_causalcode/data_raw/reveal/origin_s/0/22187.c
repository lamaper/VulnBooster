void vp9_entropy_mv_init ( ) {
 vp9_tokens_from_tree ( mv_joint_encodings , vp9_mv_joint_tree ) ;
 vp9_tokens_from_tree ( mv_class_encodings , vp9_mv_class_tree ) ;
 vp9_tokens_from_tree ( mv_class0_encodings , vp9_mv_class0_tree ) ;
 vp9_tokens_from_tree ( mv_fp_encodings , vp9_mv_fp_tree ) ;
 }