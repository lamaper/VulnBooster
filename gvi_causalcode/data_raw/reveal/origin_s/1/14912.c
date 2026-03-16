IN_PROC_BROWSER_TEST_F ( SafeJsonParserTest , Parse ) {
 TestParse ( "{
}
" ) ;
 TestParse ( "choke" ) ;
 TestParse ( "{
\"awesome\": true}
" ) ;
 TestParse ( "\"laser\"" ) ;
 TestParse ( "false" ) ;
 TestParse ( "null" ) ;
 TestParse ( "3.14" ) ;
 TestParse ( "[" ) ;
 TestParse ( "\"" ) ;
 TestParse ( std : : string ( ) ) ;
 TestParse ( "☃" ) ;
 TestParse ( "\"☃\"" ) ;
 TestParse ( "\"\\ufdd0\"" ) ;
 TestParse ( "\"\\ufffe\"" ) ;
 TestParse ( "\"\\ud83f\\udffe\"" ) ;
 }