IN_PROC_BROWSER_TEST_F ( SafeJsonParserImplTest , Isolation ) {
 for ( int i = 0 ;
 i < 5 ;
 i ++ ) {
 base : : RunLoop run_loop ;
 ParseCallback parse_callback ( run_loop . QuitClosure ( ) ) ;
 SafeJsonParser : : Parse ( connector ( ) , "[\"awesome\", \"possum\"]" , base : : Bind ( & ParseCallback : : OnSuccess , base : : Unretained ( & parse_callback ) ) , base : : Bind ( & ParseCallback : : OnError , base : : Unretained ( & parse_callback ) ) ) ;
 run_loop . Run ( ) ;
 EXPECT_TRUE ( parse_callback . success ( ) ) ;
 EXPECT_EQ ( 2U + i , GetServiceStartCount ( data_decoder : : mojom : : kServiceName ) ) ;
 }
 }