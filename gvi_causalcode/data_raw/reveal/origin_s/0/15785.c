static void transform_add ( TSHttpTxn txnp , TransformTestData * test_data ) {
 TSVConn connp ;
 auto * data = new AppendTransformTestData ;
 data -> test_data = test_data ;
 connp = TSTransformCreate ( transformtest_transform , txnp ) ;
 TSContDataSet ( connp , data ) ;
 if ( connp == nullptr ) {
 SDK_RPRINT ( data -> test_data -> test , "TSHttpTxnTransform" , "" , TC_FAIL , "Unable to create Transformation." ) ;
 return ;
 }
 TSHttpTxnHookAdd ( txnp , TS_HTTP_RESPONSE_TRANSFORM_HOOK , connp ) ;
 return ;
 }