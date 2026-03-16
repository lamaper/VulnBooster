TEST_F ( TtsControllerTest , TestTtsControllerShutdown ) {
 DummyTtsPlatformImpl platform_impl ;
 TestableTtsController * controller = new TestableTtsController ( ) ;
 controller -> SetPlatformImpl ( & platform_impl ) ;
 Utterance * utterance1 = new Utterance ( nullptr ) ;
 utterance1 -> set_can_enqueue ( true ) ;
 utterance1 -> set_src_id ( 1 ) ;
 controller -> SpeakOrEnqueue ( utterance1 ) ;
 Utterance * utterance2 = new Utterance ( nullptr ) ;
 utterance2 -> set_can_enqueue ( true ) ;
 utterance2 -> set_src_id ( 2 ) ;
 controller -> SpeakOrEnqueue ( utterance2 ) ;
 delete controller ;
 }