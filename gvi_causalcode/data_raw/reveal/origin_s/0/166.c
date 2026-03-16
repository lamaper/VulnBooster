IN_PROC_BROWSER_TEST_F ( PrintPreviewDialogControllerBrowserTest , PdfPluginDisabled ) {
 {
 base : : RunLoop run_loop ;
 content : : PluginService : : GetInstance ( ) -> GetPlugins ( base : : Bind ( & PluginsLoadedCallback , run_loop . QuitClosure ( ) ) ) ;
 run_loop . Run ( ) ;
 }
 content : : WebPluginInfo pdf_plugin_info ;
 ASSERT_TRUE ( GetPdfPluginInfo ( & pdf_plugin_info ) ) ;
 {
 base : : RunLoop run_loop ;
 PluginPrefs : : GetForProfile ( browser ( ) -> profile ( ) ) -> EnablePlugin ( false , base : : FilePath : : FromUTF8Unsafe ( ChromeContentClient : : kPDFPluginPath ) , base : : Bind ( & PluginEnabledCallback , run_loop . QuitClosure ( ) ) ) ;
 run_loop . Run ( ) ;
 }
 ChromePluginServiceFilter * filter = ChromePluginServiceFilter : : GetInstance ( ) ;
 content : : WebPluginInfo dummy_pdf_plugin_info = pdf_plugin_info ;
 EXPECT_FALSE ( filter -> IsPluginAvailable ( initiator ( ) -> GetRenderProcessHost ( ) -> GetID ( ) , initiator ( ) -> GetMainFrame ( ) -> GetRoutingID ( ) , browser ( ) -> profile ( ) -> GetResourceContext ( ) , GURL ( ) , url : : Origin ( GURL ( "http://google.com" ) ) , & dummy_pdf_plugin_info ) ) ;
 PrintPreview ( ) ;
 WebContents * preview_dialog = GetPrintPreviewDialog ( ) ;
 ASSERT_TRUE ( preview_dialog ) ;
 ASSERT_NE ( initiator ( ) , preview_dialog ) ;
 const int kExpectedFrameCount = 2 ;
 int frame_count ;
 do {
 base : : RunLoop run_loop ;
 base : : ThreadTaskRunnerHandle : : Get ( ) -> PostDelayedTask ( FROM_HERE , run_loop . QuitClosure ( ) , base : : TimeDelta : : FromSeconds ( 1 ) ) ;
 run_loop . Run ( ) ;
 frame_count = 0 ;
 preview_dialog -> ForEachFrame ( base : : Bind ( & CountFrames , base : : Unretained ( & frame_count ) ) ) ;
 }
 while ( frame_count < kExpectedFrameCount ) ;
 ASSERT_EQ ( kExpectedFrameCount , frame_count ) ;
 preview_dialog -> ForEachFrame ( base : : Bind ( & CheckPdfPluginForRenderFrame ) ) ;
 }