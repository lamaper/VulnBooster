TEST_F ( ScoredHistoryMatchTest , ScoringTLD ) {
 base : : Time now = base : : Time : : NowFromSystemTime ( ) ;
 std : : string url_string ( "http://fedcba.com/" ) ;
 const GURL url ( url_string ) ;
 history : : URLRow row ( MakeURLRow ( url_string . c_str ( ) , "" , 8 , 3 , 1 ) ) ;
 RowWordStarts word_starts ;
 PopulateWordStarts ( row , & word_starts ) ;
 WordStarts two_words_no_offsets ( 2 , 0u ) ;
 VisitInfoVector visits = CreateVisitInfoVector ( 8 , 3 , now ) ;
 ScoredHistoryMatch scored ( row , visits , std : : string ( ) , ASCIIToUTF16 ( "fed com" ) , Make2Terms ( "fed" , "com" ) , two_words_no_offsets , word_starts , false , nullptr , now ) ;
 EXPECT_EQ ( 0 , scored . raw_score ) ;
 base : : AutoReset < bool > reset ( & ScoredHistoryMatch : : allow_tld_matches_ , true ) ;
 ScoredHistoryMatch scored_with_tld ( row , visits , std : : string ( ) , ASCIIToUTF16 ( "fed com" ) , Make2Terms ( "fed" , "com" ) , two_words_no_offsets , word_starts , false , nullptr , now ) ;
 EXPECT_GT ( scored_with_tld . raw_score , 0 ) ;
 }