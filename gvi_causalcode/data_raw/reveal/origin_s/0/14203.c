TEST_F ( WebFrameTest , RecordSameDocumentNavigationToHistogram ) {
 const char * histogramName = "RendererScheduler.UpdateForSameDocumentNavigationCount" ;
 FrameTestHelpers : : WebViewHelper web_view_helper ;
 HistogramTester tester ;
 web_view_helper . InitializeAndLoad ( "about:blank" ) ;
 LocalFrame * frame = ToLocalFrame ( web_view_helper . GetWebView ( ) -> GetPage ( ) -> MainFrame ( ) ) ;
 FrameLoader & main_frame_loader = web_view_helper . GetWebView ( ) -> MainFrameImpl ( ) -> GetFrame ( ) -> Loader ( ) ;
 scoped_refptr < SerializedScriptValue > message = SerializeString ( "message" , ToScriptStateForMainWorld ( frame ) ) ;
 tester . ExpectTotalCount ( histogramName , 0 ) ;
 main_frame_loader . UpdateForSameDocumentNavigation ( ToKURL ( "about:blank" ) , kSameDocumentNavigationHistoryApi , message , kScrollRestorationAuto , WebFrameLoadType : : kReplaceCurrentItem , frame -> GetDocument ( ) ) ;
 tester . ExpectBucketCount ( histogramName , kSPANavTypeHistoryPushStateOrReplaceState , 1 ) ;
 main_frame_loader . UpdateForSameDocumentNavigation ( ToKURL ( "about:blank" ) , kSameDocumentNavigationDefault , message , kScrollRestorationManual , WebFrameLoadType : : kBackForward , frame -> GetDocument ( ) ) ;
 tester . ExpectBucketCount ( histogramName , kSPANavTypeSameDocumentBackwardOrForward , 1 ) ;
 main_frame_loader . UpdateForSameDocumentNavigation ( ToKURL ( "about:blank" ) , kSameDocumentNavigationDefault , message , kScrollRestorationManual , WebFrameLoadType : : kReplaceCurrentItem , frame -> GetDocument ( ) ) ;
 tester . ExpectBucketCount ( histogramName , kSPANavTypeOtherFragmentNavigation , 1 ) ;
 tester . ExpectTotalCount ( histogramName , 3 ) ;
 }