TEST_F ( BudgetManagerTest , GetBudgetConsumedOverTime ) {
 SetSiteEngagementScore ( kTestSES ) ;
 const blink : : mojom : : BudgetOperationType type = blink : : mojom : : BudgetOperationType : : SILENT_PUSH ;
 for ( int i = 0 ;
 i < 11 ;
 i ++ ) {
 ASSERT_TRUE ( GetBudget ( ) ) ;
 ASSERT_TRUE ( ReserveBudget ( type ) ) ;
 }
 ASSERT_TRUE ( GetBudget ( ) ) ;
 ASSERT_FALSE ( ReserveBudget ( type ) ) ;
 for ( int i = 0 ;
 i < 11 ;
 i ++ ) ASSERT_TRUE ( ConsumeBudget ( type ) ) ;
 ASSERT_FALSE ( ConsumeBudget ( type ) ) ;
 std : : vector < base : : Bucket > buckets = histogram_tester ( ) -> GetAllSamples ( "Blink.BudgetAPI.Reserve" ) ;
 ASSERT_EQ ( 2U , buckets . size ( ) ) ;
 EXPECT_EQ ( 0 , buckets [ 0 ] . min ) ;
 EXPECT_EQ ( 1 , buckets [ 0 ] . count ) ;
 EXPECT_EQ ( 1 , buckets [ 1 ] . min ) ;
 EXPECT_EQ ( 11 , buckets [ 1 ] . count ) ;
 buckets = histogram_tester ( ) -> GetAllSamples ( "Blink.BudgetAPI.QueryBudget" ) ;
 int num_samples = 0 ;
 for ( const base : : Bucket & bucket : buckets ) num_samples += bucket . count ;
 EXPECT_EQ ( 12 , num_samples ) ;
 }