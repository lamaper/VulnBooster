static void reconstruct_and_encode_image ( RoqContext * enc , RoqTempdata * tempData , int w , int h , int numBlocks ) {
 int i , j , k ;
 int x , y ;
 int subX , subY ;
 int dist = 0 ;
 roq_qcell * qcell ;
 CelEvaluation * eval ;
 CodingSpool spool ;
 spool . typeSpool = 0 ;
 spool . typeSpoolLength = 0 ;
 spool . args = spool . argumentSpool ;
 spool . pout = & enc -> out_buf ;
 if ( tempData -> used_option [ RoQ_ID_CCC ] % 2 ) tempData -> mainChunkSize += 8 ;
 bytestream_put_le16 ( & enc -> out_buf , RoQ_QUAD_VQ ) ;
 bytestream_put_le32 ( & enc -> out_buf , tempData -> mainChunkSize / 8 ) ;
 bytestream_put_byte ( & enc -> out_buf , 0x0 ) ;
 bytestream_put_byte ( & enc -> out_buf , 0x0 ) ;
 for ( i = 0 ;
 i < numBlocks ;
 i ++ ) {
 eval = tempData -> cel_evals + i ;
 x = eval -> sourceX ;
 y = eval -> sourceY ;
 dist += eval -> eval_dist [ eval -> best_coding ] ;
 switch ( eval -> best_coding ) {
 case RoQ_ID_MOT : write_typecode ( & spool , RoQ_ID_MOT ) ;
 break ;
 case RoQ_ID_FCC : bytestream_put_byte ( & spool . args , motion_arg ( eval -> motion ) ) ;
 write_typecode ( & spool , RoQ_ID_FCC ) ;
 ff_apply_motion_8x8 ( enc , x , y , eval -> motion . d [ 0 ] , eval -> motion . d [ 1 ] ) ;
 break ;
 case RoQ_ID_SLD : bytestream_put_byte ( & spool . args , tempData -> i2f4 [ eval -> cbEntry ] ) ;
 write_typecode ( & spool , RoQ_ID_SLD ) ;
 qcell = enc -> cb4x4 + eval -> cbEntry ;
 ff_apply_vector_4x4 ( enc , x , y , enc -> cb2x2 + qcell -> idx [ 0 ] ) ;
 ff_apply_vector_4x4 ( enc , x + 4 , y , enc -> cb2x2 + qcell -> idx [ 1 ] ) ;
 ff_apply_vector_4x4 ( enc , x , y + 4 , enc -> cb2x2 + qcell -> idx [ 2 ] ) ;
 ff_apply_vector_4x4 ( enc , x + 4 , y + 4 , enc -> cb2x2 + qcell -> idx [ 3 ] ) ;
 break ;
 case RoQ_ID_CCC : write_typecode ( & spool , RoQ_ID_CCC ) ;
 for ( j = 0 ;
 j < 4 ;
 j ++ ) {
 subX = x + 4 * ( j & 1 ) ;
 subY = y + 2 * ( j & 2 ) ;
 switch ( eval -> subCels [ j ] . best_coding ) {
 case RoQ_ID_MOT : break ;
 case RoQ_ID_FCC : bytestream_put_byte ( & spool . args , motion_arg ( eval -> subCels [ j ] . motion ) ) ;
 ff_apply_motion_4x4 ( enc , subX , subY , eval -> subCels [ j ] . motion . d [ 0 ] , eval -> subCels [ j ] . motion . d [ 1 ] ) ;
 break ;
 case RoQ_ID_SLD : bytestream_put_byte ( & spool . args , tempData -> i2f4 [ eval -> subCels [ j ] . cbEntry ] ) ;
 qcell = enc -> cb4x4 + eval -> subCels [ j ] . cbEntry ;
 ff_apply_vector_2x2 ( enc , subX , subY , enc -> cb2x2 + qcell -> idx [ 0 ] ) ;
 ff_apply_vector_2x2 ( enc , subX + 2 , subY , enc -> cb2x2 + qcell -> idx [ 1 ] ) ;
 ff_apply_vector_2x2 ( enc , subX , subY + 2 , enc -> cb2x2 + qcell -> idx [ 2 ] ) ;
 ff_apply_vector_2x2 ( enc , subX + 2 , subY + 2 , enc -> cb2x2 + qcell -> idx [ 3 ] ) ;
 break ;
 case RoQ_ID_CCC : for ( k = 0 ;
 k < 4 ;
 k ++ ) {
 int cb_idx = eval -> subCels [ j ] . subCels [ k ] ;
 bytestream_put_byte ( & spool . args , tempData -> i2f2 [ cb_idx ] ) ;
 ff_apply_vector_2x2 ( enc , subX + 2 * ( k & 1 ) , subY + ( k & 2 ) , enc -> cb2x2 + cb_idx ) ;
 }
 break ;
 }
 write_typecode ( & spool , eval -> subCels [ j ] . best_coding ) ;
 }
 break ;
 }
 }
 while ( spool . typeSpoolLength ) write_typecode ( & spool , 0x0 ) ;

 enc -> frame_to_enc -> data [ 0 ] , enc -> frame_to_enc -> data [ 1 ] , enc -> frame_to_enc -> data [ 2 ] }
 ;
 uint8_t * cdata [ 3 ] = {
 enc -> current_frame -> data [ 0 ] , enc -> current_frame -> data [ 1 ] , enc -> current_frame -> data [ 2 ] }
 ;
 av_log ( enc -> avctx , AV_LOG_ERROR , "Expected distortion: %i Actual: %i\n" , dist , block_sse ( fdata , cdata , 0 , 0 , 0 , 0 , enc -> frame_to_enc -> linesize , enc -> current_frame -> linesize , enc -> width ) ) ;
