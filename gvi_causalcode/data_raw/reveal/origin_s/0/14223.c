IN_PROC_BROWSER_TEST_F ( AppApiTest , MAYBE_BookmarkAppGetsNormalProcess ) {
 ExtensionService * service = extensions : : ExtensionSystem : : Get ( browser ( ) -> profile ( ) ) -> extension_service ( ) ;
 extensions : : ProcessMap * process_map = extensions : : ProcessMap : : Get ( browser ( ) -> profile ( ) ) ;
 GURL base_url = GetTestBaseURL ( "app_process" ) ;
 std : : string error ;
 scoped_refptr < const Extension > extension ;
 {
 base : : ThreadRestrictions : : ScopedAllowIO allow_io ;
 extension = extensions : : file_util : : LoadExtension ( test_data_dir_ . AppendASCII ( "app_process" ) , extensions : : Manifest : : UNPACKED , Extension : : FROM_BOOKMARK , & error ) ;
 }
 service -> OnExtensionInstalled ( extension . get ( ) , syncer : : StringOrdinal : : CreateInitialOrdinal ( ) , extensions : : kInstallFlagInstallImmediately ) ;
 ASSERT_TRUE ( extension . get ( ) ) ;
 ASSERT_TRUE ( extension -> from_bookmark ( ) ) ;
 ui_test_utils : : NavigateToURLWithDisposition ( browser ( ) , base_url . Resolve ( "path1/empty.html" ) , WindowOpenDisposition : : NEW_FOREGROUND_TAB , ui_test_utils : : BROWSER_TEST_WAIT_FOR_NAVIGATION ) ;
 EXPECT_FALSE ( process_map -> Contains ( browser ( ) -> tab_strip_model ( ) -> GetWebContentsAt ( 1 ) -> GetRenderProcessHost ( ) -> GetID ( ) ) ) ;
 EXPECT_FALSE ( browser ( ) -> tab_strip_model ( ) -> GetWebContentsAt ( 1 ) -> GetWebUI ( ) ) ;
 content : : WindowedNotificationObserver tab_added_observer ( chrome : : NOTIFICATION_TAB_ADDED , content : : NotificationService : : AllSources ( ) ) ;
 chrome : : NewTab ( browser ( ) ) ;
 tab_added_observer . Wait ( ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , base_url . Resolve ( "path2/empty.html" ) ) ;
 EXPECT_FALSE ( process_map -> Contains ( browser ( ) -> tab_strip_model ( ) -> GetWebContentsAt ( 2 ) -> GetRenderProcessHost ( ) -> GetID ( ) ) ) ;
 EXPECT_FALSE ( browser ( ) -> tab_strip_model ( ) -> GetWebContentsAt ( 2 ) -> GetWebUI ( ) ) ;
 ASSERT_EQ ( 3 , browser ( ) -> tab_strip_model ( ) -> count ( ) ) ;
 WebContents * tab = browser ( ) -> tab_strip_model ( ) -> GetWebContentsAt ( 1 ) ;
 EXPECT_NE ( tab -> GetRenderProcessHost ( ) , browser ( ) -> tab_strip_model ( ) -> GetWebContentsAt ( 2 ) -> GetRenderProcessHost ( ) ) ;
 ASSERT_EQ ( 1u , chrome : : GetBrowserCount ( browser ( ) -> profile ( ) ) ) ;
 OpenWindow ( tab , base_url . Resolve ( "path1/empty.html" ) , true , true , NULL ) ;
 OpenWindow ( tab , base_url . Resolve ( "path2/empty.html" ) , true , true , NULL ) ;
 const GURL & app_url ( base_url . Resolve ( "path1/empty.html" ) ) ;
 const GURL & non_app_url ( base_url . Resolve ( "path3/empty.html" ) ) ;
 RenderViewHost * host2 = browser ( ) -> tab_strip_model ( ) -> GetWebContentsAt ( 2 ) -> GetRenderViewHost ( ) ;
 NavigateInRenderer ( browser ( ) -> tab_strip_model ( ) -> GetWebContentsAt ( 2 ) , non_app_url ) ;
 EXPECT_EQ ( host2 -> GetProcess ( ) , browser ( ) -> tab_strip_model ( ) -> GetWebContentsAt ( 2 ) -> GetRenderProcessHost ( ) ) ;
 NavigateInRenderer ( browser ( ) -> tab_strip_model ( ) -> GetWebContentsAt ( 2 ) , app_url ) ;
 EXPECT_EQ ( host2 -> GetProcess ( ) , browser ( ) -> tab_strip_model ( ) -> GetWebContentsAt ( 2 ) -> GetRenderProcessHost ( ) ) ;
 }