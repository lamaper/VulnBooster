TEST_F ( TtsControllerTest , TestGetMatchingVoice ) {
 std : : unique_ptr < TestableTtsController > tts_controller = std : : make_unique < TestableTtsController > ( ) ;

 std : : unique_ptr < base : : DictionaryValue > lang_to_voices = std : : make_unique < base : : DictionaryValue > ( ) ;
 lang_to_voices -> SetKey ( "es" , base : : Value ( "{
\"name\":\"Voice8\",\"extension\":\"id8\"}
" ) ) ;
 lang_to_voices -> SetKey ( "noLanguage" , base : : Value ( "{
\"name\":\"Android\",\"extension\":\"\"}
" ) ) ;
 pref_service_ . registry ( ) -> RegisterDictionaryPref ( prefs : : kTextToSpeechLangToVoiceName , std : : move ( lang_to_voices ) ) ;
 tts_controller -> pref_service_ = & pref_service_ ;

 Utterance utterance ( nullptr ) ;
 std : : vector < VoiceData > voices ;
 EXPECT_EQ ( - 1 , tts_controller -> GetMatchingVoice ( & utterance , voices ) ) ;
 }
 {
 Utterance utterance ( nullptr ) ;
 std : : vector < VoiceData > voices ;
 voices . push_back ( VoiceData ( ) ) ;
 voices . push_back ( VoiceData ( ) ) ;
 EXPECT_EQ ( 0 , tts_controller -> GetMatchingVoice ( & utterance , voices ) ) ;
 }
 {
 Utterance utterance ( nullptr ) ;
 std : : vector < VoiceData > voices ;
 VoiceData fr_voice ;
 fr_voice . lang = "fr" ;
 voices . push_back ( fr_voice ) ;
 VoiceData en_voice ;
 en_voice . lang = "en" ;
 voices . push_back ( en_voice ) ;
 VoiceData de_voice ;
 de_voice . lang = "de" ;
 voices . push_back ( de_voice ) ;
 EXPECT_EQ ( 1 , tts_controller -> GetMatchingVoice ( & utterance , voices ) ) ;
 }
 {
 std : : vector < VoiceData > voices ;
 VoiceData voice0 ;
 voices . push_back ( voice0 ) ;
 VoiceData voice1 ;
 voice1 . gender = TTS_GENDER_FEMALE ;
 voices . push_back ( voice1 ) ;
 VoiceData voice2 ;
 voice2 . events . insert ( TTS_EVENT_WORD ) ;
 voices . push_back ( voice2 ) ;
 VoiceData voice3 ;
 voice3 . lang = "de-DE" ;
 voices . push_back ( voice3 ) ;
 VoiceData voice4 ;
 voice4 . lang = "fr-CA" ;
 voices . push_back ( voice4 ) ;
 VoiceData voice5 ;
 voice5 . name = "Voice5" ;
 voices . push_back ( voice5 ) ;
 VoiceData voice6 ;
 voice6 . extension_id = "id6" ;
 voices . push_back ( voice6 ) ;
 VoiceData voice7 ;
 voice7 . extension_id = "id7" ;
 voice7 . name = "Voice7" ;
 voice7 . lang = "es-es" ;
 voices . push_back ( voice7 ) ;
 VoiceData voice8 ;
 voice8 . extension_id = "id8" ;
 voice8 . name = "Voice8" ;
 voice8 . lang = "es-mx" ;
 voices . push_back ( voice8 ) ;
 VoiceData voice9 ;
 voice9 . extension_id = "" ;
 voice9 . name = "Android" ;
 voice9 . lang = "" ;
 voice9 . native = true ;
 voices . push_back ( voice9 ) ;
 Utterance utterance ( nullptr ) ;
 EXPECT_EQ ( 0 , tts_controller -> GetMatchingVoice ( & utterance , voices ) ) ;
 utterance . set_gender ( TTS_GENDER_FEMALE ) ;
 EXPECT_EQ ( 1 , tts_controller -> GetMatchingVoice ( & utterance , voices ) ) ;
 std : : set < TtsEventType > types ;
 types . insert ( TTS_EVENT_WORD ) ;
 utterance . set_required_event_types ( types ) ;
 EXPECT_EQ ( 2 , tts_controller -> GetMatchingVoice ( & utterance , voices ) ) ;
 utterance . set_lang ( "de-DE" ) ;
 EXPECT_EQ ( 3 , tts_controller -> GetMatchingVoice ( & utterance , voices ) ) ;
 utterance . set_lang ( "fr-FR" ) ;
 EXPECT_EQ ( 4 , tts_controller -> GetMatchingVoice ( & utterance , voices ) ) ;
 utterance . set_voice_name ( "Voice5" ) ;
 EXPECT_EQ ( 5 , tts_controller -> GetMatchingVoice ( & utterance , voices ) ) ;
 utterance . set_voice_name ( "" ) ;
 utterance . set_extension_id ( "id6" ) ;
 EXPECT_EQ ( 6 , tts_controller -> GetMatchingVoice ( & utterance , voices ) ) ;

 utterance . set_lang ( "es-es" ) ;
 EXPECT_EQ ( 7 , tts_controller -> GetMatchingVoice ( & utterance , voices ) ) ;
 utterance . set_extension_id ( "" ) ;
 utterance . set_lang ( "es-ar" ) ;
 EXPECT_EQ ( 8 , tts_controller -> GetMatchingVoice ( & utterance , voices ) ) ;
 utterance . set_voice_name ( "Android" ) ;
 utterance . set_extension_id ( "" ) ;
 utterance . set_lang ( "" ) ;
 EXPECT_EQ ( 9 , tts_controller -> GetMatchingVoice ( & utterance , voices ) ) ;

 }