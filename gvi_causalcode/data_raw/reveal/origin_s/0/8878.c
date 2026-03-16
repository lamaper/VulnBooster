TEST ( URLFixerTest , SegmentURL ) {
 std : : string result ;
 url : : Parsed parts ;
 for ( size_t i = 0 ;
 i < arraysize ( segment_cases ) ;
 ++ i ) {
 SegmentCase value = segment_cases [ i ] ;
 result = url_formatter : : SegmentURL ( value . input , & parts ) ;
 EXPECT_EQ ( value . result , result ) ;
 EXPECT_EQ ( value . scheme , parts . scheme ) ;
 EXPECT_EQ ( value . username , parts . username ) ;
 EXPECT_EQ ( value . password , parts . password ) ;
 EXPECT_EQ ( value . host , parts . host ) ;
 EXPECT_EQ ( value . port , parts . port ) ;
 EXPECT_EQ ( value . path , parts . path ) ;
 EXPECT_EQ ( value . query , parts . query ) ;
 EXPECT_EQ ( value . ref , parts . ref ) ;
 }
 }