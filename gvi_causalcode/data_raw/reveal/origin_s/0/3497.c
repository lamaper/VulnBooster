TEST_F ( ScoredHistoryMatchTest , ScoringBookmarks ) {
 base : : Time now = base : : Time : : NowFromSystemTime ( ) ;
 std : : string url_string ( "http://fedcba" ) ;
 const GURL url ( url_string ) ;
 history : : URLRow row ( MakeURLRow ( url_string . c_str ( ) , "abcd bcd" , 8 , 3 , 1 ) ) ;
 RowWordStarts word_starts ;
 PopulateWordStarts ( row , & word_starts ) ;
 WordStarts one_word_no_offset ( 1 , 0u ) ;
 VisitInfoVector visits = CreateVisitInfoVector ( 8 , 3 , now ) ;
 ScoredHistoryMatch scored ( row , visits , ASCIIToUTF16 ( "abc" ) , Make1Term ( "abc" ) , one_word_no_offset , word_starts , false , nullptr , now ) ;
 base : : AutoReset < int > reset ( & ScoredHistoryMatch : : bookmark_value_ , 5 ) ;
 ScoredHistoryMatch scored_with_bookmark ( row , visits , ASCIIToUTF16 ( "abc" ) , Make1Term ( "abc" ) , one_word_no_offset , word_starts , true , nullptr , now ) ;
 EXPECT_GT ( scored_with_bookmark . raw_score , scored . raw_score ) ;
 }