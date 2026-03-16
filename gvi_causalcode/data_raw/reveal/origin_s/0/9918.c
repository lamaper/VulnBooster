TEST ( BuildTime , TimeLooksValid ) {
 char build_time [ ] = "00:00:00" ;
 EXPECT_EQ ( 8u , strlen ( build_time ) ) ;
 EXPECT_EQ ( ':' , build_time [ 2 ] ) ;
 EXPECT_EQ ( ':' , build_time [ 5 ] ) ;
 }