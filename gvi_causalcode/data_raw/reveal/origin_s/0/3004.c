TEST_F ( AutocompleteResultTest , Swap ) {
 AutocompleteResult r1 ;
 AutocompleteResult r2 ;
 r1 . Swap ( & r2 ) ;
 EXPECT_EQ ( r1 . end ( ) , r1 . default_match ( ) ) ;
 EXPECT_EQ ( r2 . end ( ) , r2 . default_match ( ) ) ;
 ACMatches matches ;
 AutocompleteMatch match ;
 match . relevance = 1 ;
 match . allowed_to_be_default_match = true ;
 AutocompleteInput input ( base : : ASCIIToUTF16 ( "a" ) , base : : string16 : : npos , std : : string ( ) , GURL ( ) , OmniboxEventProto : : INVALID_SPEC , false , false , false , true , false , TestSchemeClassifier ( ) ) ;
 matches . push_back ( match ) ;
 r1 . AppendMatches ( input , matches ) ;
 r1 . SortAndCull ( input , template_url_service_ . get ( ) ) ;
 EXPECT_EQ ( r1 . begin ( ) , r1 . default_match ( ) ) ;
 EXPECT_EQ ( "http://a/" , r1 . alternate_nav_url ( ) . spec ( ) ) ;
 r1 . Swap ( & r2 ) ;
 EXPECT_TRUE ( r1 . empty ( ) ) ;
 EXPECT_EQ ( r1 . end ( ) , r1 . default_match ( ) ) ;
 EXPECT_TRUE ( r1 . alternate_nav_url ( ) . is_empty ( ) ) ;
 ASSERT_FALSE ( r2 . empty ( ) ) ;
 EXPECT_EQ ( r2 . begin ( ) , r2 . default_match ( ) ) ;
 EXPECT_EQ ( "http://a/" , r2 . alternate_nav_url ( ) . spec ( ) ) ;
 }