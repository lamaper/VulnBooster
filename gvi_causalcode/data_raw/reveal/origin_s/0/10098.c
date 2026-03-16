int http_version_print ( int32_t version , char * buf , int bufsize , int * bufindex , int * dumpoffset ) {

 http_hdr_version_to_string ( version , tmpbuf ) ;
 TRY ( mime_mem_print ( tmpbuf , 8 , buf , bufsize , bufindex , dumpoffset ) ) ;
 return 1 ;
