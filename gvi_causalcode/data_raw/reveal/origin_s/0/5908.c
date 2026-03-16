TEST_F ( HistoryQuickProviderTest , ContentsClass ) {
 std : : vector < std : : string > expected_urls ;
 expected_urls . push_back ( "http://ja.wikipedia.org/wiki/%E7%AC%AC%E4%BA%8C%E6%AC%A1%E4%B8%96%E7" "%95%8C%E5%A4%A7%E6%88%A6#.E3.83.B4.E3.82.A7.E3.83.AB.E3.82.B5.E3.82." "A4.E3.83.A6.E4.BD.93.E5.88.B6" ) ;
 RunTest ( base : : UTF8ToUTF16 ( "第二 e3" ) , false , expected_urls , false , base : : UTF8ToUTF16 ( "ja.wikipedia.org/wiki/第二次世界大戦#.E3.83.B4.E3." "82.A7.E3.83.AB.E3.82.B5.E3.82.A4.E3.83.A6.E4.BD." "93.E5.88.B6" ) , base : : string16 ( ) ) ;


 size_t expected_offsets [ ] = {
 0 , 22 , 24 , 31 , 33 , 40 , 42 , 49 , 51 , 58 , 60 , 67 , 69 , 76 , 78 }
 ;
 EXPECT_LE ( contents_class . size ( ) , arraysize ( expected_offsets ) ) ;
 EXPECT_GE ( contents_class . size ( ) , 5u ) ;
 for ( size_t i = 0 ;
 i < contents_class . size ( ) ;
 ++ i ) EXPECT_EQ ( expected_offsets [ i ] , contents_class [ i ] . offset ) ;
 }