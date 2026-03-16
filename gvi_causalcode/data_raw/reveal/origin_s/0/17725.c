static void gather_data_for_cel ( CelEvaluation * cel , RoqContext * enc , RoqTempdata * tempData ) {
 uint8_t mb8 [ 8 * 8 * 3 ] ;
 int index = cel -> sourceY * enc -> width / 64 + cel -> sourceX / 8 ;
 int i , j , best_dist , divide_bit_use ;
 int bitsUsed [ 4 ] = {
 2 , 10 , 10 , 0 }
 ;
 if ( enc -> framesSinceKeyframe >= 1 ) {
 cel -> motion = enc -> this_motion8 [ index ] ;
 cel -> eval_dist [ RoQ_ID_FCC ] = eval_motion_dist ( enc , cel -> sourceX , cel -> sourceY , enc -> this_motion8 [ index ] , 8 ) ;
 }
 else cel -> eval_dist [ RoQ_ID_FCC ] = INT_MAX ;
 if ( enc -> framesSinceKeyframe >= 2 ) cel -> eval_dist [ RoQ_ID_MOT ] = block_sse ( enc -> frame_to_enc -> data , enc -> current_frame -> data , cel -> sourceX , cel -> sourceY , cel -> sourceX , cel -> sourceY , enc -> frame_to_enc -> linesize , enc -> current_frame -> linesize , 8 ) ;
 else cel -> eval_dist [ RoQ_ID_MOT ] = INT_MAX ;
 get_frame_mb ( enc -> frame_to_enc , cel -> sourceX , cel -> sourceY , mb8 , 8 ) ;
 cel -> eval_dist [ RoQ_ID_SLD ] = index_mb ( mb8 , tempData -> codebooks . unpacked_cb4_enlarged , tempData -> codebooks . numCB4 , & cel -> cbEntry , 8 ) ;
 gather_data_for_subcel ( cel -> subCels + 0 , cel -> sourceX + 0 , cel -> sourceY + 0 , enc , tempData ) ;
 gather_data_for_subcel ( cel -> subCels + 1 , cel -> sourceX + 4 , cel -> sourceY + 0 , enc , tempData ) ;
 gather_data_for_subcel ( cel -> subCels + 2 , cel -> sourceX + 0 , cel -> sourceY + 4 , enc , tempData ) ;
 gather_data_for_subcel ( cel -> subCels + 3 , cel -> sourceX + 4 , cel -> sourceY + 4 , enc , tempData ) ;
 cel -> eval_dist [ RoQ_ID_CCC ] = 0 ;
 divide_bit_use = 0 ;
 for ( i = 0 ;
 i < 4 ;
 i ++ ) {
 cel -> eval_dist [ RoQ_ID_CCC ] += cel -> subCels [ i ] . eval_dist [ cel -> subCels [ i ] . best_coding ] ;
 divide_bit_use += cel -> subCels [ i ] . best_bit_use ;
 }
 best_dist = INT_MAX ;
 bitsUsed [ 3 ] = 2 + divide_bit_use ;
 for ( i = 0 ;
 i < 4 ;
 i ++ ) if ( ROQ_LAMBDA_SCALE * cel -> eval_dist [ i ] + enc -> lambda * bitsUsed [ i ] < best_dist ) {
 cel -> best_coding = i ;
 best_dist = ROQ_LAMBDA_SCALE * cel -> eval_dist [ i ] + enc -> lambda * bitsUsed [ i ] ;
 }
 tempData -> used_option [ cel -> best_coding ] ++ ;
 tempData -> mainChunkSize += bitsUsed [ cel -> best_coding ] ;
 if ( cel -> best_coding == RoQ_ID_SLD ) tempData -> codebooks . usedCB4 [ cel -> cbEntry ] ++ ;
 if ( cel -> best_coding == RoQ_ID_CCC ) for ( i = 0 ;
 i < 4 ;
 i ++ ) {
 if ( cel -> subCels [ i ] . best_coding == RoQ_ID_SLD ) tempData -> codebooks . usedCB4 [ cel -> subCels [ i ] . cbEntry ] ++ ;
 else if ( cel -> subCels [ i ] . best_coding == RoQ_ID_CCC ) for ( j = 0 ;
 j < 4 ;
 j ++ ) tempData -> codebooks . usedCB2 [ cel -> subCels [ i ] . subCels [ j ] ] ++ ;
 }
 }