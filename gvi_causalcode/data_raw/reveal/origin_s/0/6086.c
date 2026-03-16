static void TestFramePrinting ( WebLocalFrameImpl * frame ) {
 WebPrintParams print_params ;
 WebSize page_size ( 500 , 500 ) ;
 print_params . print_content_area . width = page_size . width ;
 print_params . print_content_area . height = page_size . height ;
 EXPECT_EQ ( 1 , frame -> PrintBegin ( print_params , WebNode ( ) ) ) ;
 PaintRecorder recorder ;
 frame -> PrintPagesForTesting ( recorder . beginRecording ( IntRect ( ) ) , page_size ) ;
 frame -> PrintEnd ( ) ;
 }