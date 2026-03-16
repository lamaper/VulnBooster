static int matroska_merge_packets ( AVPacket * out , AVPacket * in ) {
 int old_size = out -> size ;
 int ret = av_grow_packet ( out , in -> size ) ;
 if ( ret < 0 ) return ret ;
 memcpy ( out -> data + old_size , in -> data , in -> size ) ;
 av_free_packet ( in ) ;
 av_free ( in ) ;
 return 0 ;
 }