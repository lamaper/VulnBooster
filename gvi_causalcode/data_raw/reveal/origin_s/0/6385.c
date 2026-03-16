TEST_F ( ScoredHistoryMatchTest , GetTopicalityScoreTrailingSlash ) {
 const float hostname = GetTopicalityScoreOfTermAgainstURLAndTitle ( ASCIIToUTF16 ( "def" ) , ASCIIToUTF16 ( "http://abc.def.com/" ) , ASCIIToUTF16 ( "Non-Matching Title" ) ) ;
 const float hostname_no_slash = GetTopicalityScoreOfTermAgainstURLAndTitle ( ASCIIToUTF16 ( "def" ) , ASCIIToUTF16 ( "http://abc.def.com" ) , ASCIIToUTF16 ( "Non-Matching Title" ) ) ;
 EXPECT_EQ ( hostname_no_slash , hostname ) ;
 }