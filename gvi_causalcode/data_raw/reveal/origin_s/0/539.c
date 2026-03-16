static int tm2_read_tree ( TM2Context * ctx , uint32_t prefix , int length , TM2Huff * huff ) {
 int ret ;
 if ( length > huff -> max_bits ) {
 av_log ( ctx -> avctx , AV_LOG_ERROR , "Tree exceeded its given depth (%i)\n" , huff -> max_bits ) ;
 return AVERROR_INVALIDDATA ;
 }
 if ( ! get_bits1 ( & ctx -> gb ) ) {
 if ( length == 0 ) {
 length = 1 ;
 }
 if ( huff -> num >= huff -> max_num ) {
 av_log ( ctx -> avctx , AV_LOG_DEBUG , "Too many literals\n" ) ;
 return AVERROR_INVALIDDATA ;
 }
 huff -> nums [ huff -> num ] = get_bits_long ( & ctx -> gb , huff -> val_bits ) ;
 huff -> bits [ huff -> num ] = prefix ;
 huff -> lens [ huff -> num ] = length ;
 huff -> num ++ ;
 return 0 ;
 }
 else {
 if ( ( ret = tm2_read_tree ( ctx , prefix << 1 , length + 1 , huff ) ) < 0 ) return ret ;
 if ( ( ret = tm2_read_tree ( ctx , ( prefix << 1 ) | 1 , length + 1 , huff ) ) < 0 ) return ret ;
 }
 return 0 ;
 }