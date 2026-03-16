TEST_F ( BudgetManagerTest , TestUniqueOrigin ) {
 const blink : : mojom : : BudgetOperationType type = blink : : mojom : : BudgetOperationType : : SILENT_PUSH ;
 SetOrigin ( url : : Origin ( GURL ( "file://example.com:443/etc/passwd" ) ) ) ;
 ASSERT_FALSE ( ReserveBudget ( type ) ) ;
 ASSERT_EQ ( blink : : mojom : : BudgetServiceErrorType : : NOT_SUPPORTED , error_ ) ;
 ASSERT_FALSE ( ConsumeBudget ( type ) ) ;
 }