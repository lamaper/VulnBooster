static int transformtest_transform ( TSCont contp , TSEvent event , void * ) {
 auto * data = static_cast < AppendTransformTestData * > ( TSContDataGet ( contp ) ) ;
 if ( data -> test_data -> test_passed_transform_create == false ) {
 data -> test_data -> test_passed_transform_create = true ;
 SDK_RPRINT ( data -> test_data -> test , "TSTransformCreate" , "TestCase1" , TC_PASS , "ok" ) ;
 }
 if ( TSVConnClosedGet ( contp ) ) {
 delete data ;
 TSContDestroy ( contp ) ;
 return 0 ;
 }
 else {
 switch ( event ) {
 case TS_EVENT_ERROR : {
 TSVIO write_vio ;
 write_vio = TSVConnWriteVIOGet ( contp ) ;
 TSContCall ( TSVIOContGet ( write_vio ) , TS_EVENT_ERROR , write_vio ) ;
 }
 break ;
 case TS_EVENT_VCONN_WRITE_COMPLETE : TSVConnShutdown ( TSTransformOutputVConnGet ( contp ) , 0 , 1 ) ;
 break ;
 case TS_EVENT_VCONN_WRITE_READY : default : handle_transform ( contp ) ;
 break ;
 }
 }
 return 0 ;
 }