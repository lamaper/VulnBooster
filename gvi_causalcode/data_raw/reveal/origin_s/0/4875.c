static inline int tm2_read_header ( TM2Context * ctx , const uint8_t * buf ) {
 uint32_t magic = AV_RL32 ( buf ) ;
 switch ( magic ) {
 case TM2_OLD_HEADER_MAGIC : av_log_missing_feature ( ctx -> avctx , "TM2 old header" , 1 ) ;
 return 0 ;
 case TM2_NEW_HEADER_MAGIC : return 0 ;
 default : av_log ( ctx -> avctx , AV_LOG_ERROR , "Not a TM2 header: 0x%08X\n" , magic ) ;
 return AVERROR_INVALIDDATA ;
 }
 }