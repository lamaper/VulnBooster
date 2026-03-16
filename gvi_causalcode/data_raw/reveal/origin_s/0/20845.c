TEST ( BuildTime , DateLooksValid ) {
 char build_date [ ] = BUILD_DATE ;
 EXPECT_EQ ( 11u , strlen ( build_date ) ) ;
 EXPECT_EQ ( ' ' , build_date [ 3 ] ) ;
 EXPECT_EQ ( ' ' , build_date [ 6 ] ) ;
 }