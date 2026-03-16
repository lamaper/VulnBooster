void vp9_build_inter_predictors_sby ( MACROBLOCKD * xd , int mi_row , int mi_col , BLOCK_SIZE bsize ) {
 build_inter_predictors_for_planes ( xd , bsize , mi_row , mi_col , 0 , 0 ) ;
 }