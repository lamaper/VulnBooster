static int ogg_read_seek ( AVFormatContext * s , int stream_index , int64_t timestamp , int flags ) {
 struct ogg * ogg = s -> priv_data ;
 struct ogg_stream * os = ogg -> streams + stream_index ;
 int ret ;
 av_assert0 ( stream_index < ogg -> nstreams ) ;
 ogg_reset ( s ) ;
 if ( s -> streams [ stream_index ] -> codec -> codec_type == AVMEDIA_TYPE_VIDEO && ! ( flags & AVSEEK_FLAG_ANY ) ) os -> keyframe_seek = 1 ;
 ret = ff_seek_frame_binary ( s , stream_index , timestamp , flags ) ;
 ogg_reset ( s ) ;
 os = ogg -> streams + stream_index ;
 if ( ret < 0 ) os -> keyframe_seek = 0 ;
 return ret ;
 }