static void start_put ( struct transfer_request * request ) {
 char * hex = oid_to_hex ( & request -> obj -> oid ) ;
 struct active_request_slot * slot ;
 struct strbuf buf = STRBUF_INIT ;
 enum object_type type ;
 char hdr [ 50 ] ;
 void * unpacked ;
 unsigned long len ;
 int hdrlen ;
 ssize_t size ;
 git_zstream stream ;
 unpacked = read_sha1_file ( request -> obj -> oid . hash , & type , & len ) ;
 hdrlen = xsnprintf ( hdr , sizeof ( hdr ) , "%s %lu" , typename ( type ) , len ) + 1 ;
 git_deflate_init ( & stream , zlib_compression_level ) ;
 size = git_deflate_bound ( & stream , len + hdrlen ) ;
 strbuf_init ( & request -> buffer . buf , size ) ;
 request -> buffer . posn = 0 ;
 stream . next_out = ( unsigned char * ) request -> buffer . buf . buf ;
 stream . avail_out = size ;
 stream . next_in = ( void * ) hdr ;
 stream . avail_in = hdrlen ;
 while ( git_deflate ( & stream , 0 ) == Z_OK ) ;
 stream . next_in = unpacked ;
 stream . avail_in = len ;
 while ( git_deflate ( & stream , Z_FINISH ) == Z_OK ) ;
 git_deflate_end ( & stream ) ;
 free ( unpacked ) ;
 request -> buffer . buf . len = stream . total_out ;
 strbuf_addstr ( & buf , "Destination: " ) ;
 append_remote_object_url ( & buf , repo -> url , hex , 0 ) ;
 request -> dest = strbuf_detach ( & buf , NULL ) ;
 append_remote_object_url ( & buf , repo -> url , hex , 0 ) ;
 strbuf_add ( & buf , request -> lock -> tmpfile_suffix , 41 ) ;
 request -> url = strbuf_detach ( & buf , NULL ) ;
 slot = get_active_slot ( ) ;
 slot -> callback_func = process_response ;
 slot -> callback_data = request ;
 curl_setup_http ( slot -> curl , request -> url , DAV_PUT , & request -> buffer , fwrite_null ) ;
 if ( start_active_slot ( slot ) ) {
 request -> slot = slot ;
 request -> state = RUN_PUT ;
 }
 else {
 request -> state = ABORTED ;
 free ( request -> url ) ;
 request -> url = NULL ;
 }
 }