TEST_F ( BudgetDatabaseTest , AddEngagementBudgetTest ) {
 base : : SimpleTestClock * clock = SetClockForTesting ( ) ;
 base : : Time expiration_time = clock -> Now ( ) + base : : TimeDelta : : FromDays ( kDefaultExpirationInDays ) ;
 SetSiteEngagementScore ( kEngagement ) ;
 double daily_budget = kMaxDailyBudget * ( kEngagement / SiteEngagementScore : : kMaxPoints ) ;
 GetBudgetDetails ( ) ;
 ASSERT_TRUE ( success_ ) ;
 ASSERT_EQ ( 2U , prediction_ . size ( ) ) ;
 ASSERT_DOUBLE_EQ ( daily_budget * kDefaultExpirationInDays , prediction_ [ 0 ] -> budget_at ) ;
 ASSERT_EQ ( 0 , prediction_ [ 1 ] -> budget_at ) ;
 ASSERT_EQ ( expiration_time . ToDoubleT ( ) , prediction_ [ 1 ] -> time ) ;
 clock -> Advance ( base : : TimeDelta : : FromDays ( 1 ) ) ;
 GetBudgetDetails ( ) ;
 ASSERT_TRUE ( success_ ) ;
 ASSERT_EQ ( 3U , prediction_ . size ( ) ) ;
 ASSERT_DOUBLE_EQ ( daily_budget * ( kDefaultExpirationInDays + 1 ) , prediction_ [ 0 ] -> budget_at ) ;
 ASSERT_DOUBLE_EQ ( daily_budget , prediction_ [ 1 ] -> budget_at ) ;
 ASSERT_EQ ( expiration_time . ToDoubleT ( ) , prediction_ [ 1 ] -> time ) ;
 ASSERT_DOUBLE_EQ ( 0 , prediction_ [ 2 ] -> budget_at ) ;
 ASSERT_EQ ( ( expiration_time + base : : TimeDelta : : FromDays ( 1 ) ) . ToDoubleT ( ) , prediction_ [ 2 ] -> time ) ;
 clock -> Advance ( base : : TimeDelta : : FromMinutes ( 59 ) ) ;
 GetBudgetDetails ( ) ;
 ASSERT_TRUE ( success_ ) ;
 ASSERT_EQ ( 3U , prediction_ . size ( ) ) ;
 ASSERT_DOUBLE_EQ ( daily_budget * ( kDefaultExpirationInDays + 1 ) , prediction_ [ 0 ] -> budget_at ) ;
 }