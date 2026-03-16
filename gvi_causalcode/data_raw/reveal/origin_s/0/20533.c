IN_PROC_BROWSER_TEST_F ( HostedAppTest , ShouldUseWebAppFrame ) {
 base : : CommandLine : : ForCurrentProcess ( ) -> AppendSwitch ( switches : : kEnableWebAppFrame ) ;
 const Extension * bookmark_app = InstallExtensionWithSourceAndFlags ( test_data_dir_ . AppendASCII ( "app" ) , 1 , extensions : : Manifest : : INTERNAL , extensions : : Extension : : FROM_BOOKMARK ) ;
 ASSERT_TRUE ( bookmark_app ) ;
 WebContents * bookmark_app_window = OpenApplication ( AppLaunchParams ( browser ( ) -> profile ( ) , bookmark_app , extensions : : LAUNCH_CONTAINER_WINDOW , NEW_WINDOW , extensions : : SOURCE_UNTRACKED ) ) ;
 ASSERT_TRUE ( bookmark_app_window ) ;
 ASSERT_TRUE ( LoadExtension ( test_data_dir_ . AppendASCII ( "packaged_app" ) ) ) ;
 const Extension * packaged_app = nullptr ;
 extensions : : ExtensionRegistry * registry = extensions : : ExtensionRegistry : : Get ( browser ( ) -> profile ( ) ) ;
 for ( const scoped_refptr < const extensions : : Extension > & extension : registry -> enabled_extensions ( ) ) {
 if ( extension -> name ( ) == "Packaged App Test" ) packaged_app = extension . get ( ) ;
 }
 ASSERT_TRUE ( packaged_app ) ;
 WebContents * packaged_app_window = OpenApplication ( AppLaunchParams ( browser ( ) -> profile ( ) , packaged_app , extensions : : LAUNCH_CONTAINER_WINDOW , NEW_WINDOW , extensions : : SOURCE_UNTRACKED ) ) ;
 ASSERT_TRUE ( packaged_app_window ) ;
 DevToolsWindow * devtools_window = DevToolsWindowTesting : : OpenDevToolsWindowSync ( browser ( ) , false ) ;
 ASSERT_EQ ( 4u , chrome : : GetBrowserCount ( browser ( ) -> profile ( ) , browser ( ) -> host_desktop_type ( ) ) ) ;
 Browser * bookmark_app_browser = nullptr ;
 Browser * packaged_app_browser = nullptr ;
 Browser * dev_tools_browser = nullptr ;
 for ( chrome : : BrowserIterator it ;
 ! it . done ( ) ;
 it . Next ( ) ) {
 if ( * it == browser ( ) ) {
 continue ;
 }
 else if ( ( * it ) -> app_name ( ) == DevToolsWindow : : kDevToolsApp ) {
 dev_tools_browser = * it ;
 }
 else if ( ( * it ) -> tab_strip_model ( ) -> GetActiveWebContents ( ) == bookmark_app_window ) {
 bookmark_app_browser = * it ;
 }
 else {
 packaged_app_browser = * it ;
 }
 }
 ASSERT_TRUE ( dev_tools_browser ) ;
 ASSERT_TRUE ( bookmark_app_browser ) ;
 ASSERT_TRUE ( bookmark_app_browser != browser ( ) ) ;
 ASSERT_TRUE ( packaged_app_browser ) ;
 ASSERT_TRUE ( packaged_app_browser != browser ( ) ) ;
 ASSERT_TRUE ( packaged_app_browser != bookmark_app_browser ) ;
 EXPECT_FALSE ( browser ( ) -> SupportsWindowFeature ( Browser : : FEATURE_WEBAPPFRAME ) ) ;
 EXPECT_FALSE ( dev_tools_browser -> SupportsWindowFeature ( Browser : : FEATURE_WEBAPPFRAME ) ) ;
 EXPECT_EQ ( browser ( ) -> host_desktop_type ( ) == chrome : : HOST_DESKTOP_TYPE_ASH , bookmark_app_browser -> SupportsWindowFeature ( Browser : : FEATURE_WEBAPPFRAME ) ) ;
 EXPECT_FALSE ( packaged_app_browser -> SupportsWindowFeature ( Browser : : FEATURE_WEBAPPFRAME ) ) ;
 DevToolsWindowTesting : : CloseDevToolsWindowSync ( devtools_window ) ;
 }