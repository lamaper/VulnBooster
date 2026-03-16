char * test_url_print ( TSMBuffer bufp , TSMLoc hdr_loc ) {
 TSIOBuffer output_buffer ;
 TSIOBufferReader reader ;
 int64_t total_avail ;
 TSIOBufferBlock block ;
 const char * block_start ;
 int64_t block_avail ;
 char * output_string ;
 int output_len ;
 output_buffer = TSIOBufferCreate ( ) ;
 if ( ! output_buffer ) {
 TSError ( "[InkAPITest] couldn't allocate IOBuffer" ) ;
 }
 reader = TSIOBufferReaderAlloc ( output_buffer ) ;
 TSUrlPrint ( bufp , hdr_loc , output_buffer ) ;
 total_avail = TSIOBufferReaderAvail ( reader ) ;
 output_string = ( char * ) TSmalloc ( total_avail + 1 ) ;
 output_len = 0 ;
 block = TSIOBufferReaderStart ( reader ) ;
 while ( block ) {
 block_start = TSIOBufferBlockReadStart ( block , reader , & block_avail ) ;
 if ( block_avail == 0 ) {
 break ;
 }
 memcpy ( output_string + output_len , block_start , block_avail ) ;
 output_len += block_avail ;
 TSIOBufferReaderConsume ( reader , block_avail ) ;
 block = TSIOBufferReaderStart ( reader ) ;
 }
 output_string [ output_len ] = '\0' ;
 output_len ++ ;
 TSIOBufferReaderFree ( reader ) ;
 TSIOBufferDestroy ( output_buffer ) ;
 return output_string ;
 }