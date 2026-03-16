static int seqvideo_decode_frame ( AVCodecContext * avctx , void * data , int * got_frame , AVPacket * avpkt ) {
 const uint8_t * buf = avpkt -> data ;
 int buf_size = avpkt -> size ;
 int ret ;
 SeqVideoContext * seq = avctx -> priv_data ;
 if ( ( ret = ff_reget_buffer ( avctx , & seq -> frame ) ) < 0 ) {
 av_log ( seq -> avctx , AV_LOG_ERROR , "tiertexseqvideo: reget_buffer() failed\n" ) ;
 return ret ;
 }
 if ( seqvideo_decode ( seq , buf , buf_size ) ) return AVERROR_INVALIDDATA ;
 if ( ( ret = av_frame_ref ( data , & seq -> frame ) ) < 0 ) return ret ;
 * got_frame = 1 ;
 return buf_size ;
 }