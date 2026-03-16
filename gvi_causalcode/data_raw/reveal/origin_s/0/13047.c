TEST_F ( HistoryQuickProviderTest , EncodingLimitMatch ) {
 std : : vector < std : : string > expected_urls ;
 std : : string url ( "http://cda.com/Dogs%20Cats%20Gorillas%20Sea%20Slugs%20and%20Mice" ) ;
 RunTest ( ASCIIToUTF16 ( "ice" ) , false , expected_urls , false , ASCIIToUTF16 ( "cda.com/Dogs Cats Gorillas Sea Slugs and Mice" ) , base : : string16 ( ) ) ;
 expected_urls . push_back ( url ) ;
 RunTest ( ASCIIToUTF16 ( "Mice" ) , false , expected_urls , false , ASCIIToUTF16 ( "cda.com/Dogs Cats Gorillas Sea Slugs and Mice" ) , base : : string16 ( ) ) ;
 ACMatchClassifications content ( ac_matches_ [ 0 ] . contents_class ) ;
 const size_t max_offset = url . length ( ) - ( ( 6 * 2 ) + 7 ) ;
 for ( ACMatchClassifications : : const_iterator citer = content . begin ( ) ;
 citer != content . end ( ) ;
 ++ citer ) EXPECT_LT ( citer -> offset , max_offset ) ;
 ACMatchClassifications description ( ac_matches_ [ 0 ] . description_class ) ;
 std : : string page_title ( "Dogs & Cats & Mice & Other Animals" ) ;
 for ( ACMatchClassifications : : const_iterator diter = description . begin ( ) ;
 diter != description . end ( ) ;
 ++ diter ) EXPECT_LT ( diter -> offset , page_title . length ( ) ) ;
 }