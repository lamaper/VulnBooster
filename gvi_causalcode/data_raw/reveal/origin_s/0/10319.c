int upx_inflatelzma ( const char * src , uint32_t ssize , char * dst , uint32_t * dsize , uint32_t upx0 , uint32_t upx1 , uint32_t ep ) {
 struct CLI_LZMA l ;
 uint32_t magic [ ] = {
 0xb16 , 0xb1e , 0 }
 ;
 unsigned char fake_lzmahdr [ 5 ] ;
 memset ( & l , 0 , sizeof ( l ) ) ;
 cli_writeint32 ( fake_lzmahdr + 1 , * dsize ) ;
 * fake_lzmahdr = 3 + 9 * ( 5 * 2 + 0 ) ;
 l . next_in = fake_lzmahdr ;
 l . avail_in = 5 ;
 if ( cli_LzmaInit ( & l , * dsize ) != LZMA_RESULT_OK ) return 0 ;
 l . avail_in = ssize ;
 l . avail_out = * dsize ;
 l . next_in = ( unsigned char * ) src + 2 ;
 l . next_out = ( unsigned char * ) dst ;
 if ( cli_LzmaDecode ( & l ) == LZMA_RESULT_DATA_ERROR ) {
 cli_LzmaShutdown ( & l ) ;
 return - 1 ;
 }
 cli_LzmaShutdown ( & l ) ;
 return pefromupx ( src , ssize , dst , dsize , ep , upx0 , upx1 , magic , * dsize ) ;
 }