static void libopus_flush ( AVCodecContext * avc ) {
 struct libopus_context * opus = avc -> priv_data ;
 opus_multistream_decoder_ctl ( opus -> dec , OPUS_RESET_STATE ) ;
 }