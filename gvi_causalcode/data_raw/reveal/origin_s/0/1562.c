TEST_F ( ScoredHistoryMatchTest , ScoringScheme ) {
 base : : Time now = base : : Time : : NowFromSystemTime ( ) ;
 std : : string url_string ( "http://fedcba/" ) ;
 const GURL url ( url_string ) ;
 history : : URLRow row ( MakeURLRow ( url_string . c_str ( ) , "" , 8 , 3 , 1 ) ) ;
 RowWordStarts word_starts ;
 PopulateWordStarts ( row , & word_starts ) ;
 WordStarts two_words_no_offsets ( 2 , 0u ) ;
 VisitInfoVector visits = CreateVisitInfoVector ( 8 , 3 , now ) ;
 ScoredHistoryMatch scored ( row , visits , ASCIIToUTF16 ( "fed http" ) , Make2Terms ( "fed" , "http" ) , two_words_no_offsets , word_starts , false , nullptr , now ) ;
 EXPECT_EQ ( 0 , scored . raw_score ) ;
 base : : AutoReset < bool > reset ( & ScoredHistoryMatch : : allow_scheme_matches_ , true ) ;
 ScoredHistoryMatch scored_with_scheme ( row , visits , ASCIIToUTF16 ( "fed http" ) , Make2Terms ( "fed" , "http" ) , two_words_no_offsets , word_starts , false , nullptr , now ) ;
 EXPECT_GT ( scored_with_scheme . raw_score , 0 ) ;
 }