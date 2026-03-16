void vp9_predict_intra_block ( const MACROBLOCKD * xd , int block_idx , int bwl_in , TX_SIZE tx_size , PREDICTION_MODE mode , const uint8_t * ref , int ref_stride , uint8_t * dst , int dst_stride , int aoff , int loff , int plane ) {
 const int bwl = bwl_in - tx_size ;
 const int wmask = ( 1 << bwl ) - 1 ;
 const int have_top = ( block_idx >> bwl ) || xd -> up_available ;
 const int have_left = ( block_idx & wmask ) || xd -> left_available ;
 const int have_right = ( ( block_idx & wmask ) != wmask ) ;
 const int x = aoff * 4 ;
 const int y = loff * 4 ;
 assert ( bwl >= 0 ) ;
 build_intra_predictors ( xd , ref , ref_stride , dst , dst_stride , mode , tx_size , have_top , have_left , have_right , x , y , plane ) ;
 }