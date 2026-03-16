TEST_F ( MultiBufferTest , RandomTest_RangeSupported ) {
 size_t file_size = 1000000 ;
 multibuffer_ . SetFileSize ( file_size ) ;
 multibuffer_ . SetMaxBlocksAfterDefer ( 10 ) ;
 std : : vector < ReadHelper * > read_helpers ;
 multibuffer_ . SetRangeSupported ( true ) ;
 for ( size_t i = 0 ;
 i < 20 ;
 i ++ ) {
 read_helpers . push_back ( new ReadHelper ( file_size , 1000 , & multibuffer_ , & rnd_ ) ) ;
 }
 for ( int i = 0 ;
 i < 100 ;
 i ++ ) {
 for ( int j = 0 ;
 j < 100 ;
 j ++ ) {
 if ( rnd_ . Rand ( ) & 1 ) {
 if ( ! media : : writers . empty ( ) ) Advance ( ) ;
 }
 else {
 size_t j = rnd_ . Rand ( ) % read_helpers . size ( ) ;
 if ( rnd_ . Rand ( ) % 100 < 3 ) read_helpers [ j ] -> Seek ( ) ;
 read_helpers [ j ] -> StartRead ( ) ;
 }
 }
 multibuffer_ . CheckLRUState ( ) ;
 }
 multibuffer_ . CheckPresentState ( ) ;
 while ( ! read_helpers . empty ( ) ) {
 delete read_helpers . back ( ) ;
 read_helpers . pop_back ( ) ;
 }
 }