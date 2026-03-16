static void srtp_calc_aead_iv_srtcp ( srtp_stream_ctx_t * stream , v128_t * iv , uint32_t seq_num , srtcp_hdr_t * hdr ) {
 v128_t in ;
 v128_t salt ;
 memset ( & in , 0 , sizeof ( v128_t ) ) ;
 memset ( & salt , 0 , sizeof ( v128_t ) ) ;
 in . v16 [ 0 ] = 0 ;
 memcpy ( & in . v16 [ 1 ] , & hdr -> ssrc , 4 ) ;
 in . v16 [ 3 ] = 0 ;
 in . v32 [ 2 ] = 0x7FFFFFFF & htonl ( seq_num ) ;
 debug_print ( mod_srtp , "Pre-salted RTCP IV = %s\n" , v128_hex_string ( & in ) ) ;
 memcpy ( salt . v8 , stream -> c_salt , 12 ) ;
 debug_print ( mod_srtp , "RTCP SALT = %s\n" , v128_hex_string ( & salt ) ) ;
 v128_xor ( iv , & in , & salt ) ;
 }