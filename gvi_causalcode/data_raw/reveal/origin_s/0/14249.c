TEST_F ( BudgetManagerTest , TestInsecureOrigin ) {
 const blink : : mojom : : BudgetOperationType type = blink : : mojom : : BudgetOperationType : : SILENT_PUSH ;
 SetOrigin ( url : : Origin ( GURL ( "http://example.com" ) ) ) ;
 SetSiteEngagementScore ( kTestSES ) ;
 ASSERT_FALSE ( ReserveBudget ( type ) ) ;
 ASSERT_EQ ( blink : : mojom : : BudgetServiceErrorType : : NOT_SUPPORTED , error_ ) ;
 ASSERT_FALSE ( ConsumeBudget ( type ) ) ;
 }