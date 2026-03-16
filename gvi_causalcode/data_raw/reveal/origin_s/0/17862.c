TEST_F ( ShortcutsProviderTest , CalculateScore ) {
 ShortcutsDatabase : : Shortcut shortcut ( std : : string ( ) , ASCIIToUTF16 ( "test" ) , ShortcutsDatabase : : Shortcut : : MatchCore ( ASCIIToUTF16 ( "www.test.com" ) , GURL ( "http://www.test.com" ) , ASCIIToUTF16 ( "www.test.com" ) , "0,1,4,3,8,1" , ASCIIToUTF16 ( "A test" ) , "0,0,2,2" , ui : : PAGE_TRANSITION_TYPED , AutocompleteMatchType : : HISTORY_URL , base : : string16 ( ) ) , base : : Time : : Now ( ) , 1 ) ;
 const int max_relevance = ShortcutsProvider : : kShortcutsProviderDefaultMaxRelevance ;
 const int kMaxScore = CalculateScore ( "test" , shortcut , max_relevance ) ;
 int score_three_quarters = CalculateScore ( "tes" , shortcut , max_relevance ) ;
 EXPECT_LT ( score_three_quarters , kMaxScore ) ;
 int score_one_half = CalculateScore ( "te" , shortcut , max_relevance ) ;
 EXPECT_LT ( score_one_half , score_three_quarters ) ;
 int score_one_quarter = CalculateScore ( "t" , shortcut , max_relevance ) ;
 EXPECT_LT ( score_one_quarter , score_one_half ) ;
 shortcut . last_access_time = base : : Time : : Now ( ) - base : : TimeDelta : : FromDays ( 7 ) ;
 int score_week_old = CalculateScore ( "test" , shortcut , max_relevance ) ;
 EXPECT_LT ( score_week_old , kMaxScore ) ;
 shortcut . last_access_time = base : : Time : : Now ( ) - base : : TimeDelta : : FromDays ( 14 ) ;
 int score_two_weeks_old = CalculateScore ( "test" , shortcut , max_relevance ) ;
 EXPECT_LT ( score_two_weeks_old , score_week_old ) ;
 shortcut . number_of_hits = 2 ;
 shortcut . last_access_time = base : : Time : : Now ( ) - base : : TimeDelta : : FromDays ( 14 ) ;
 int score_popular_two_weeks_old = CalculateScore ( "test" , shortcut , max_relevance ) ;
 EXPECT_LT ( score_two_weeks_old , score_popular_two_weeks_old ) ;
 EXPECT_LT ( score_popular_two_weeks_old , kMaxScore ) ;
 shortcut . number_of_hits = 3 ;
 shortcut . last_access_time = base : : Time : : Now ( ) - base : : TimeDelta : : FromDays ( 14 ) ;
 int score_more_popular_two_weeks_old = CalculateScore ( "test" , shortcut , max_relevance ) ;
 EXPECT_LT ( score_two_weeks_old , score_more_popular_two_weeks_old ) ;
 EXPECT_LT ( score_popular_two_weeks_old , score_more_popular_two_weeks_old ) ;
 EXPECT_LT ( score_more_popular_two_weeks_old , kMaxScore ) ;
 }