TEST_F ( MultiBufferTest , ReadAll ) {
 multibuffer_ . SetMaxWriters ( 1 ) ;
 size_t pos = 0 ;
 size_t end = 10000 ;
 multibuffer_ . SetFileSize ( 10000 ) ;
 multibuffer_ . SetMustReadWholeFile ( true ) ;
 media : : MultiBufferReader reader ( & multibuffer_ , pos , end , base : : Callback < void ( int64_t , int64_t ) > ( ) ) ;
 reader . SetMaxBuffer ( 2000 , 5000 ) ;
 reader . SetPreload ( 1000 , 1000 ) ;
 while ( pos < end ) {
 unsigned char buffer [ 27 ] ;
 buffer [ 17 ] = 17 ;
 size_t to_read = std : : min < size_t > ( end - pos , 17 ) ;
 int64_t bytes_read = reader . TryRead ( buffer , to_read ) ;
 if ( bytes_read ) {
 EXPECT_EQ ( buffer [ 17 ] , 17 ) ;
 for ( int64_t i = 0 ;
 i < bytes_read ;
 i ++ ) {
 uint8_t expected = static_cast < uint8_t > ( ( pos * 15485863 ) >> 16 ) ;
 EXPECT_EQ ( expected , buffer [ i ] ) << " pos = " << pos ;
 pos ++ ;
 }
 }
 else {
 Advance ( ) ;
 }
 }
 }