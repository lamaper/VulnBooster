static void set_stream_dimensions ( struct stream_state * stream , unsigned int w , unsigned int h ) {
 if ( ! stream -> config . cfg . g_w ) {
 if ( ! stream -> config . cfg . g_h ) stream -> config . cfg . g_w = w ;
 else stream -> config . cfg . g_w = w * stream -> config . cfg . g_h / h ;
 }
 if ( ! stream -> config . cfg . g_h ) {
 stream -> config . cfg . g_h = h * stream -> config . cfg . g_w / w ;
 }
 }