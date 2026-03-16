TEST_F ( SoundContentSettingObserverTest , MuteByDefaultAndExceptionRecordsException ) {
 ChangeSoundContentSettingTo ( CONTENT_SETTING_BLOCK ) ;
 ChangeDefaultSoundContentSettingTo ( CONTENT_SETTING_BLOCK ) ;
 SimulateAudioStarting ( ) ;
 EXPECT_TRUE ( RecordedSiteMuted ( ) ) ;
 ExpectRecordedForReason ( SoundContentSettingObserver : : MuteReason : : kSiteException ) ;
 }