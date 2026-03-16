TEST_F ( BudgetDatabaseTest , GetBudgetNoBudgetOrSES ) {
 GetBudgetDetails ( ) ;
 ASSERT_TRUE ( success_ ) ;
 ASSERT_EQ ( 2U , prediction_ . size ( ) ) ;
 EXPECT_EQ ( 0 , prediction_ [ 0 ] -> budget_at ) ;
 }