TEST_F ( BudgetDatabaseTest , GetBudgetNegativeTime ) {
 base : : SimpleTestClock * clock = SetClockForTesting ( ) ;
 SetSiteEngagementScore ( kEngagement ) ;
 GetBudgetDetails ( ) ;
 clock -> Advance ( base : : TimeDelta : : FromDays ( 1 ) ) ;
 GetBudgetDetails ( ) ;
 ASSERT_EQ ( 3U , prediction_ . size ( ) ) ;
 double budget = prediction_ [ 0 ] -> budget_at ;
 clock -> SetNow ( clock -> Now ( ) - base : : TimeDelta : : FromDays ( 5 ) ) ;
 GetBudgetDetails ( ) ;
 ASSERT_EQ ( 3U , prediction_ . size ( ) ) ;
 ASSERT_EQ ( budget , prediction_ [ 0 ] -> budget_at ) ;
 clock -> SetNow ( clock -> Now ( ) + base : : TimeDelta : : FromDays ( 5 ) ) ;
 GetBudgetDetails ( ) ;
 ASSERT_EQ ( 3U , prediction_ . size ( ) ) ;
 ASSERT_EQ ( budget , prediction_ [ 0 ] -> budget_at ) ;
 }