TEST_F ( MultiBufferTest , LRUTest ) {
 int64_t max_size = 17 ;
 int64_t current_size = 0 ;
 lru_ -> IncrementMaxSize ( max_size ) ;
 multibuffer_ . SetMaxWriters ( 1 ) ;
 size_t pos = 0 ;
 size_t end = 10000 ;
 multibuffer_ . SetFileSize ( 10000 ) ;
 media : : MultiBufferReader reader ( & multibuffer_ , pos , end , base : : Callback < void ( int64_t , int64_t ) > ( ) ) ;
 reader . SetPreload ( 10000 , 10000 ) ;
 EXPECT_EQ ( current_size , lru_ -> Size ( ) ) ;
 current_size += max_size ;
 while ( AdvanceAll ( ) ) ;
 EXPECT_EQ ( current_size , lru_ -> Size ( ) ) ;
 lru_ -> IncrementMaxSize ( - max_size ) ;
 lru_ -> Prune ( 3 ) ;
 current_size -= 3 ;
 EXPECT_EQ ( current_size , lru_ -> Size ( ) ) ;
 lru_ -> Prune ( 3 ) ;
 current_size -= 3 ;
 EXPECT_EQ ( current_size , lru_ -> Size ( ) ) ;
 lru_ -> Prune ( 1000 ) ;
 EXPECT_EQ ( 0 , lru_ -> Size ( ) ) ;
 }