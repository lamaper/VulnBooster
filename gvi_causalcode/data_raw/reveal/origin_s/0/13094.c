static void set_default_kf_interval ( struct stream_state * stream , struct VpxEncoderConfig * global ) {
 if ( ! stream -> config . have_kf_max_dist ) {
 double framerate = ( double ) global -> framerate . num / global -> framerate . den ;
 if ( framerate > 0.0 ) stream -> config . cfg . kf_max_dist = ( unsigned int ) ( 5.0 * framerate ) ;
 }
 }