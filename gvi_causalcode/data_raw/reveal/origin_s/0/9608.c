TEST_F ( WebFrameTest , GetCanonicalUrlForSharing ) {
 FrameTestHelpers : : WebViewHelper web_view_helper ;
 web_view_helper . Initialize ( ) ;
 WebLocalFrameImpl * frame = web_view_helper . LocalMainFrame ( ) ;
 FrameTestHelpers : : LoadHTMLString ( frame , R "( < head > < link rel = "canonical" href = "https: 
 }