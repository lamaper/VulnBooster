TEST_F ( MultiBufferTest , ReadAllAdvanceFirst_NeverDefer ) {
 multibuffer_ . SetMaxWriters ( 1 ) ;
 size_t pos = 0 ;
 size_t end = 10000 ;
 multibuffer_ . SetFileSize ( 10000 ) ;
 multibuffer_ . SetMaxBlocksAfterDefer ( - 10000 ) ;
 multibuffer_ . SetRangeSupported ( true ) ;
 media : : MultiBufferReader reader ( & multibuffer_ , pos , end , base : : Callback < void ( int64_t , int64_t ) > ( ) ) ;
 reader . SetMaxBuffer ( 2000 , 5000 ) ;
 reader . SetPreload ( 1000 , 1000 ) ;
 while ( pos < end ) {
 unsigned char buffer [ 27 ] ;
 buffer [ 17 ] = 17 ;
 size_t to_read = std : : min < size_t > ( end - pos , 17 ) ;
 while ( AdvanceAll ( ) ) ;
 int64_t bytes = reader . TryRead ( buffer , to_read ) ;
 EXPECT_GT ( bytes , 0 ) ;
 EXPECT_EQ ( buffer [ 17 ] , 17 ) ;
 for ( int64_t i = 0 ;
 i < bytes ;
 i ++ ) {
 uint8_t expected = static_cast < uint8_t > ( ( pos * 15485863 ) >> 16 ) ;
 EXPECT_EQ ( expected , buffer [ i ] ) << " pos = " << pos ;
 pos ++ ;
 }
 }
 EXPECT_GT ( multibuffer_ . writers_created ( ) , 1 ) ;
 }