TEST_F ( BudgetDatabaseTest , SpendBudgetTest ) {
 base : : SimpleTestClock * clock = SetClockForTesting ( ) ;
 SetSiteEngagementScore ( kEngagement ) ;
 GetBudgetDetails ( ) ;
 clock -> Advance ( base : : TimeDelta : : FromDays ( 1 ) ) ;
 GetBudgetDetails ( ) ;
 clock -> Advance ( base : : TimeDelta : : FromDays ( 1 ) ) ;
 GetBudgetDetails ( ) ;
 ASSERT_TRUE ( SpendBudget ( 1 ) ) ;
 GetBudgetDetails ( ) ;
 double daily_budget = kMaxDailyBudget * ( kEngagement / SiteEngagementScore : : kMaxPoints ) ;
 ASSERT_EQ ( 4U , prediction_ . size ( ) ) ;
 ASSERT_DOUBLE_EQ ( ( 2 + kDefaultExpirationInDays ) * daily_budget - 1 , prediction_ [ 0 ] -> budget_at ) ;
 ASSERT_DOUBLE_EQ ( daily_budget * 2 , prediction_ [ 1 ] -> budget_at ) ;
 ASSERT_DOUBLE_EQ ( daily_budget , prediction_ [ 2 ] -> budget_at ) ;
 ASSERT_DOUBLE_EQ ( 0 , prediction_ [ 3 ] -> budget_at ) ;
 ASSERT_TRUE ( SpendBudget ( ( 1 + kDefaultExpirationInDays ) * daily_budget ) ) ;
 GetBudgetDetails ( ) ;
 ASSERT_EQ ( 2U , prediction_ . size ( ) ) ;
 ASSERT_DOUBLE_EQ ( daily_budget - 1 , prediction_ [ 0 ] -> budget_at ) ;
 EXPECT_FALSE ( SpendBudget ( kEngagement ) ) ;
 GetBudgetDetails ( ) ;
 ASSERT_EQ ( 2U , prediction_ . size ( ) ) ;
 ASSERT_DOUBLE_EQ ( daily_budget - 1 , prediction_ [ 0 ] -> budget_at ) ;
 clock -> Advance ( base : : TimeDelta : : FromDays ( kDefaultExpirationInDays + 1 ) ) ;
 EXPECT_TRUE ( SpendBudget ( daily_budget * kDefaultExpirationInDays ) ) ;
 }