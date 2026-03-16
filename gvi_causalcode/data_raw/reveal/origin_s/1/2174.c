TEST_F ( ScoredHistoryMatchTest , Inlining ) {
 base : : Time now = base : : Time : : NowFromSystemTime ( ) ;
 RowWordStarts word_starts ;
 WordStarts one_word_no_offset ( 1 , 0u ) ;
 VisitInfoVector visits ;
 {
 history : : URLRow row ( MakeURLRow ( "http://www.google.com" , "abcdef" , 3 , 30 , 1 ) ) ;
 PopulateWordStarts ( row , & word_starts ) ;
 ScoredHistoryMatch scored_a ( row , visits , std : : string ( ) , ASCIIToUTF16 ( "g" ) , Make1Term ( "g" ) , one_word_no_offset , word_starts , false , nullptr , now ) ;
 EXPECT_FALSE ( scored_a . match_in_scheme ) ;
 ScoredHistoryMatch scored_b ( row , visits , std : : string ( ) , ASCIIToUTF16 ( "w" ) , Make1Term ( "w" ) , one_word_no_offset , word_starts , false , nullptr , now ) ;
 EXPECT_FALSE ( scored_b . match_in_scheme ) ;
 ScoredHistoryMatch scored_c ( row , visits , std : : string ( ) , ASCIIToUTF16 ( "h" ) , Make1Term ( "h" ) , one_word_no_offset , word_starts , false , nullptr , now ) ;
 EXPECT_TRUE ( scored_c . match_in_scheme ) ;
 ScoredHistoryMatch scored_d ( row , visits , std : : string ( ) , ASCIIToUTF16 ( "o" ) , Make1Term ( "o" ) , one_word_no_offset , word_starts , false , nullptr , now ) ;
 EXPECT_FALSE ( scored_d . match_in_scheme ) ;
 }
 {
 history : : URLRow row ( MakeURLRow ( "http://teams.foo.com" , "abcdef" , 3 , 30 , 1 ) ) ;
 PopulateWordStarts ( row , & word_starts ) ;
 ScoredHistoryMatch scored_a ( row , visits , std : : string ( ) , ASCIIToUTF16 ( "t" ) , Make1Term ( "t" ) , one_word_no_offset , word_starts , false , nullptr , now ) ;
 EXPECT_FALSE ( scored_a . match_in_scheme ) ;
 ScoredHistoryMatch scored_b ( row , visits , std : : string ( ) , ASCIIToUTF16 ( "f" ) , Make1Term ( "f" ) , one_word_no_offset , word_starts , false , nullptr , now ) ;
 EXPECT_FALSE ( scored_b . match_in_scheme ) ;
 ScoredHistoryMatch scored_c ( row , visits , std : : string ( ) , ASCIIToUTF16 ( "o" ) , Make1Term ( "o" ) , one_word_no_offset , word_starts , false , nullptr , now ) ;
 EXPECT_FALSE ( scored_c . match_in_scheme ) ;
 }
 {
 history : : URLRow row ( MakeURLRow ( "https://www.testing.com" , "abcdef" , 3 , 30 , 1 ) ) ;
 PopulateWordStarts ( row , & word_starts ) ;
 ScoredHistoryMatch scored_a ( row , visits , std : : string ( ) , ASCIIToUTF16 ( "t" ) , Make1Term ( "t" ) , one_word_no_offset , word_starts , false , nullptr , now ) ;
 EXPECT_FALSE ( scored_a . match_in_scheme ) ;
 ScoredHistoryMatch scored_b ( row , visits , std : : string ( ) , ASCIIToUTF16 ( "h" ) , Make1Term ( "h" ) , one_word_no_offset , word_starts , false , nullptr , now ) ;
 EXPECT_TRUE ( scored_b . match_in_scheme ) ;
 ScoredHistoryMatch scored_c ( row , visits , std : : string ( ) , ASCIIToUTF16 ( "w" ) , Make1Term ( "w" ) , one_word_no_offset , word_starts , false , nullptr , now ) ;
 EXPECT_FALSE ( scored_c . match_in_scheme ) ;
 }
 {
 history : : URLRow row ( MakeURLRow ( "http://www.xn--1lq90ic7f1rc.cn/xnblah" , "abcd" , 3 , 30 , 1 ) ) ;
 PopulateWordStarts ( row , & word_starts ) ;
 ScoredHistoryMatch scored_a ( row , visits , "zh-CN" , ASCIIToUTF16 ( "x" ) , Make1Term ( "x" ) , one_word_no_offset , word_starts , false , nullptr , now ) ;
 EXPECT_FALSE ( scored_a . match_in_scheme ) ;
 ScoredHistoryMatch scored_b ( row , visits , "zh-CN" , ASCIIToUTF16 ( "xn" ) , Make1Term ( "xn" ) , one_word_no_offset , word_starts , false , nullptr , now ) ;
 EXPECT_FALSE ( scored_b . match_in_scheme ) ;
 ScoredHistoryMatch scored_c ( row , visits , "zh-CN" , ASCIIToUTF16 ( "w" ) , Make1Term ( "w" ) , one_word_no_offset , word_starts , false , nullptr , now ) ;
 EXPECT_FALSE ( scored_c . match_in_scheme ) ;
 }
 }