static int test_decompress_single_bit_error ( xd3_stream * stream , int expected_non_failures ) {
 int ret ;
 usize_t i ;
 uint8_t encoded [ 4 * sizeof ( test_text ) ] ;
 usize_t encoded_size ;
 int non_failures = 0 ;
 int cksum = ( stream -> flags & XD3_ADLER32 ) != 0 ;

 {
 char buf [ TESTBUFSIZE ] ;
 FILE * f ;
 snprintf_func ( buf , TESTBUFSIZE , "test_text" ) ;
 f = fopen ( buf , "w" ) ;
 fwrite ( test_text , 1 , sizeof ( test_text ) , f ) ;
 fclose ( f ) ;
 }

 char buf [ TESTBUFSIZE ] ;
 FILE * f ;
 snprintf_func ( buf , TESTBUFSIZE , "test_text.xz.%d" , non_failures ) ;
 f = fopen ( buf , "w" ) ;
 fwrite ( encoded , 1 , encoded_size , f ) ;
 fclose ( f ) ;
 }
 while ( 0 ) # endif stream -> sec_data . inefficient = 1 ;
 stream -> sec_inst . inefficient = 1 ;
 stream -> sec_addr . inefficient = 1 ;
 if ( ( ret = test_compress_text ( stream , encoded , & encoded_size ) ) ) {
 return ret ;
 }
 if ( ( ret = test_decompress_text ( stream , encoded , encoded_size , sizeof ( test_text ) / 4 ) ) ) {
 return ret ;
 }
 TEST_FAILURES ( ) ;
 for ( i = 0 ;
 i < encoded_size * 8 ;
 i += 1 ) {
 encoded [ i / 8 ] ^= 1 << ( i % 8 ) ;
 if ( ( ret = test_decompress_text ( stream , encoded , encoded_size , sizeof ( test_text ) ) ) == 0 ) {
 non_failures += 1 ;


 }
 else {
 }
 if ( cksum && ret == EIO ) {
 stream -> msg = "checksum mismatch" ;
 return XD3_INTERNAL ;
 }
 encoded [ i / 8 ] ^= 1 << ( i % 8 ) ;
 }
 if ( ( ret = test_decompress_text ( stream , encoded , encoded_size , 1 ) ) ) {
 return ret ;
 }
 if ( non_failures != expected_non_failures ) {
 XPR ( NT "non-failures %u;
 expected %u" , non_failures , expected_non_failures ) ;
 stream -> msg = "incorrect" ;
 return XD3_INTERNAL ;
 }
 DOT ( ) ;
 return 0 ;
 }