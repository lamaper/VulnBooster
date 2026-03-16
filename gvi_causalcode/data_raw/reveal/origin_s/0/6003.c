TEST_F ( BudgetDatabaseTest , CheckEngagementHistograms ) {
 base : : SimpleTestClock * clock = SetClockForTesting ( ) ;
 double cost = 2 ;
 double engagement = 2 * cost * SiteEngagementScore : : kMaxPoints / kDefaultExpirationInDays / kMaxDailyBudget ;
 SetSiteEngagementScore ( engagement ) ;
 GetBudgetDetails ( ) ;
 ASSERT_TRUE ( SpendBudget ( cost ) ) ;
 ASSERT_TRUE ( SpendBudget ( cost ) ) ;
 ASSERT_FALSE ( SpendBudget ( cost ) ) ;
 clock -> Advance ( base : : TimeDelta : : FromDays ( 12 ) ) ;
 GetBudgetDetails ( ) ;
 SetSiteEngagementScore ( engagement * 2 ) ;
 ASSERT_TRUE ( SpendBudget ( cost ) ) ;
 ASSERT_TRUE ( SpendBudget ( cost ) ) ;
 ASSERT_FALSE ( SpendBudget ( cost ) ) ;
 std : : vector < base : : Bucket > no_budget_buckets = GetHistogramTester ( ) -> GetAllSamples ( "PushMessaging.SESForNoBudgetOrigin" ) ;
 ASSERT_EQ ( 2U , no_budget_buckets . size ( ) ) ;
 EXPECT_EQ ( floor ( engagement ) , no_budget_buckets [ 0 ] . min ) ;
 EXPECT_EQ ( 1 , no_budget_buckets [ 0 ] . count ) ;
 EXPECT_EQ ( floor ( engagement * 2 ) , no_budget_buckets [ 1 ] . min ) ;
 EXPECT_EQ ( 1 , no_budget_buckets [ 1 ] . count ) ;
 std : : vector < base : : Bucket > low_budget_buckets = GetHistogramTester ( ) -> GetAllSamples ( "PushMessaging.SESForLowBudgetOrigin" ) ;
 ASSERT_EQ ( 2U , low_budget_buckets . size ( ) ) ;
 EXPECT_EQ ( floor ( engagement ) , low_budget_buckets [ 0 ] . min ) ;
 EXPECT_EQ ( 1 , low_budget_buckets [ 0 ] . count ) ;
 EXPECT_EQ ( floor ( engagement * 2 ) , low_budget_buckets [ 1 ] . min ) ;
 EXPECT_EQ ( 1 , low_budget_buckets [ 1 ] . count ) ;
 }