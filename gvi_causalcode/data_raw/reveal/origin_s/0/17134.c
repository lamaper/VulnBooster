TEST_F ( BudgetDatabaseTest , CheckBackgroundBudgetHistogram ) {
 base : : SimpleTestClock * clock = SetClockForTesting ( ) ;
 SetSiteEngagementScore ( kEngagement ) ;
 GetBudgetDetails ( ) ;
 clock -> Advance ( base : : TimeDelta : : FromDays ( kDefaultExpirationInDays / 2 ) ) ;
 GetBudgetDetails ( ) ;
 clock -> Advance ( base : : TimeDelta : : FromMinutes ( 59 ) ) ;
 GetBudgetDetails ( ) ;
 clock -> Advance ( base : : TimeDelta : : FromDays ( kDefaultExpirationInDays + 1 ) ) ;
 GetBudgetDetails ( ) ;
 std : : vector < base : : Bucket > buckets = GetHistogramTester ( ) -> GetAllSamples ( "PushMessaging.BackgroundBudget" ) ;
 ASSERT_EQ ( 2U , buckets . size ( ) ) ;
 double full_award = kMaxDailyBudget * kEngagement / SiteEngagementScore : : kMaxPoints * kDefaultExpirationInDays ;
 EXPECT_EQ ( floor ( full_award ) , buckets [ 0 ] . min ) ;
 EXPECT_EQ ( 2 , buckets [ 0 ] . count ) ;
 EXPECT_EQ ( floor ( full_award * 1.5 ) , buckets [ 1 ] . min ) ;
 EXPECT_EQ ( 1 , buckets [ 1 ] . count ) ;
 }