static int checkHttpTxnParentProxy ( ContData * data , TSHttpTxn txnp ) {
 const char * hostname = "txnpp.example.com" ;
 int port = 10180 ;
 const char * hostnameget = nullptr ;
 int portget = 0 ;
 TSHttpTxnParentProxySet ( txnp , ( char * ) hostname , port ) ;
 if ( TSHttpTxnParentProxyGet ( txnp , & hostnameget , & portget ) != TS_SUCCESS ) {
 SDK_RPRINT ( data -> test , "TSHttpTxnParentProxySet" , "TestCase1" , TC_FAIL , "TSHttpTxnParentProxyGet doesn't return TS_SUCCESS" ) ;
 SDK_RPRINT ( data -> test , "TSHttpTxnParentProxyGet" , "TestCase1" , TC_FAIL , "TSHttpTxnParentProxyGet doesn't return TS_SUCCESS" ) ;
 return TS_EVENT_CONTINUE ;
 }
 if ( ( strcmp ( hostname , hostnameget ) == 0 ) && ( port == portget ) ) {
 SDK_RPRINT ( data -> test , "TSHttpTxnParentProxySet" , "TestCase1" , TC_PASS , "ok" ) ;
 SDK_RPRINT ( data -> test , "TSHttpTxnParentProxyGet" , "TestCase1" , TC_PASS , "ok" ) ;
 data -> test_passed_Parent_Proxy = true ;
 }
 else {
 SDK_RPRINT ( data -> test , "TSHttpTxnParentProxySet" , "TestCase1" , TC_FAIL , "Value's Mismatch" ) ;
 SDK_RPRINT ( data -> test , "TSHttpTxnParentProxyGet" , "TestCase1" , TC_FAIL , "Value's Mismatch" ) ;
 }
 return TS_EVENT_CONTINUE ;
 }