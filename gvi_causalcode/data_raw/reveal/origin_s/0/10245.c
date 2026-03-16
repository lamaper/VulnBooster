TEST_F ( WebFrameTest , NoLoadingCompletionCallbacksInDetach ) {
 class LoadingObserverFrameClient : public FrameTestHelpers : : TestWebFrameClient {
 public : LoadingObserverFrameClient ( ) = default ;
 ~ LoadingObserverFrameClient ( ) override = default ;
 void FrameDetached ( DetachType type ) override {
 did_call_frame_detached_ = true ;
 TestWebFrameClient : : FrameDetached ( type ) ;
 }
 void DidStopLoading ( ) override {
 did_call_did_stop_loading_ = true ;
 TestWebFrameClient : : DidStopLoading ( ) ;
 }
 void DidFailProvisionalLoad ( const WebURLError & , WebHistoryCommitType ) override {
 EXPECT_TRUE ( false ) << "The load should not have failed." ;
 }
 void DidFinishDocumentLoad ( ) override {
 did_call_did_finish_document_load_ = true ;
 }
 void DidHandleOnloadEvents ( ) override {
 did_call_did_handle_onload_events_ = true ;
 }
 void DidFinishLoad ( ) override {
 EXPECT_TRUE ( false ) << "didFinishLoad() should not have been called." ;
 }
 void DispatchLoad ( ) override {
 EXPECT_TRUE ( false ) << "dispatchLoad() should not have been called." ;
 }
 bool DidCallFrameDetached ( ) const {
 return did_call_frame_detached_ ;
 }
 bool DidCallDidStopLoading ( ) const {
 return did_call_did_stop_loading_ ;
 }
 bool DidCallDidFinishDocumentLoad ( ) const {
 return did_call_did_finish_document_load_ ;
 }
 bool DidCallDidHandleOnloadEvents ( ) const {
 return did_call_did_handle_onload_events_ ;
 }
 private : bool did_call_frame_detached_ = false ;
 bool did_call_did_stop_loading_ = false ;
 bool did_call_did_finish_document_load_ = false ;
 bool did_call_did_handle_onload_events_ = false ;
 }
 ;
 class MainFrameClient : public FrameTestHelpers : : TestWebFrameClient {
 public : MainFrameClient ( ) = default ;
 ~ MainFrameClient ( ) override = default ;
 WebLocalFrame * CreateChildFrame ( WebLocalFrame * parent , WebTreeScopeType scope , const WebString & name , const WebString & fallback_name , WebSandboxFlags sandbox_flags , const ParsedFeaturePolicy & container_policy , const WebFrameOwnerProperties & ) override {
 return CreateLocalChild ( * parent , scope , & child_client_ ) ;
 }
 LoadingObserverFrameClient & ChildClient ( ) {
 return child_client_ ;
 }
 private : LoadingObserverFrameClient child_client_ ;
 }
 ;
 RegisterMockedHttpURLLoad ( "single_iframe.html" ) ;
 URLTestHelpers : : RegisterMockedURLLoad ( ToKURL ( base_url_ + "visible_iframe.html" ) , test : : CoreTestDataPath ( "frame_with_frame.html" ) ) ;
 RegisterMockedHttpURLLoad ( "parent_detaching_frame.html" ) ;
 FrameTestHelpers : : WebViewHelper web_view_helper ;
 MainFrameClient main_frame_client ;
 web_view_helper . InitializeAndLoad ( base_url_ + "single_iframe.html" , & main_frame_client ) ;
 EXPECT_TRUE ( main_frame_client . ChildClient ( ) . DidCallFrameDetached ( ) ) ;
 EXPECT_TRUE ( main_frame_client . ChildClient ( ) . DidCallDidStopLoading ( ) ) ;
 EXPECT_TRUE ( main_frame_client . ChildClient ( ) . DidCallDidFinishDocumentLoad ( ) ) ;
 EXPECT_TRUE ( main_frame_client . ChildClient ( ) . DidCallDidHandleOnloadEvents ( ) ) ;
 web_view_helper . Reset ( ) ;
 }