static struct FrameData * fd_create ( void * buf , size_t size , vpx_codec_frame_flags_t flags ) {
 struct FrameData * const frame_data = ( struct FrameData * ) vpx_malloc ( sizeof ( * frame_data ) ) ;
 if ( frame_data == NULL ) {
 return NULL ;
 }
 frame_data -> buf = vpx_malloc ( size ) ;
 if ( frame_data -> buf == NULL ) {
 vpx_free ( frame_data ) ;
 return NULL ;
 }
 vpx_memcpy ( frame_data -> buf , buf , size ) ;
 frame_data -> size = size ;
 frame_data -> flags = flags ;
 return frame_data ;
 }