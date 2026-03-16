static int tta_check_crc ( TTAContext * s , const uint8_t * buf , int buf_size ) {
 uint32_t crc , CRC ;
 CRC = AV_RL32 ( buf + buf_size ) ;
 crc = av_crc ( s -> crc_table , 0xFFFFFFFFU , buf , buf_size ) ;
 if ( CRC != ( crc ^ 0xFFFFFFFFU ) ) {
 av_log ( s -> avctx , AV_LOG_ERROR , "CRC error\n" ) ;
 return AVERROR_INVALIDDATA ;
 }
 return 0 ;
 }