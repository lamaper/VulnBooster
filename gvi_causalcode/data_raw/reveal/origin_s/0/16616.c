IN_PROC_BROWSER_TEST_F ( ExtensionApiTest , SandboxedPages ) {
 EXPECT_TRUE ( RunExtensionSubtest ( "sandboxed_pages" , "main.html" ) ) << message_ ;
 }