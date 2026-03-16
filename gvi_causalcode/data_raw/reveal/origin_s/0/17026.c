TEST_F ( HistoryQuickProviderTest , PreventBeatingURLWhatYouTypedMatch ) {
 std : : vector < std : : string > expected_urls ;
 expected_urls . clear ( ) ;
 expected_urls . push_back ( "http://popularsitewithroot.com/" ) ;
 RunTest ( ASCIIToUTF16 ( "popularsitewithroot.com" ) , false , expected_urls , true , ASCIIToUTF16 ( "popularsitewithroot.com" ) , base : : string16 ( ) ) ;
 EXPECT_LT ( ac_matches_ [ 0 ] . relevance , HistoryURLProvider : : kScoreForBestInlineableResult ) ;
 RunTest ( ASCIIToUTF16 ( "popularsitewithroot.c" ) , false , expected_urls , true , ASCIIToUTF16 ( "popularsitewithroot.com" ) , ASCIIToUTF16 ( "om" ) ) ;
 EXPECT_GE ( ac_matches_ [ 0 ] . relevance , HistoryURLProvider : : kScoreForWhatYouTypedResult ) ;
 expected_urls . clear ( ) ;
 expected_urls . push_back ( "http://popularsitewithpathonly.com/moo" ) ;
 RunTest ( ASCIIToUTF16 ( "popularsitewithpathonly.com" ) , false , expected_urls , true , ASCIIToUTF16 ( "popularsitewithpathonly.com/moo" ) , ASCIIToUTF16 ( "/moo" ) ) ;
 EXPECT_LT ( ac_matches_ [ 0 ] . relevance , HistoryURLProvider : : kScoreForUnvisitedIntranetResult ) ;
 RunTest ( ASCIIToUTF16 ( "popularsitewithpathonly.com/" ) , false , expected_urls , true , ASCIIToUTF16 ( "popularsitewithpathonly.com/moo" ) , ASCIIToUTF16 ( "moo" ) ) ;
 EXPECT_LT ( ac_matches_ [ 0 ] . relevance , HistoryURLProvider : : kScoreForUnvisitedIntranetResult ) ;
 RunTest ( ASCIIToUTF16 ( "popularsitewithpathonly.co" ) , false , expected_urls , true , ASCIIToUTF16 ( "popularsitewithpathonly.com/moo" ) , ASCIIToUTF16 ( "m/moo" ) ) ;
 EXPECT_GE ( ac_matches_ [ 0 ] . relevance , HistoryURLProvider : : kScoreForWhatYouTypedResult ) ;
 RunTest ( ASCIIToUTF16 ( "popularsitewithpathonly.com/mo" ) , false , expected_urls , true , ASCIIToUTF16 ( "popularsitewithpathonly.com/moo" ) , ASCIIToUTF16 ( "o" ) ) ;
 EXPECT_GE ( ac_matches_ [ 0 ] . relevance , HistoryURLProvider : : kScoreForWhatYouTypedResult ) ;
 RunTest ( ASCIIToUTF16 ( "popularsitewithpathonly.com/moo" ) , false , expected_urls , true , ASCIIToUTF16 ( "popularsitewithpathonly.com/moo" ) , base : : string16 ( ) ) ;
 EXPECT_LT ( ac_matches_ [ 0 ] . relevance , HistoryURLProvider : : kScoreForBestInlineableResult ) ;
 }