TEST_F ( SoundContentSettingObserverTest , MuteByDefaultRecordsCorrectly ) {
 ChangeDefaultSoundContentSettingTo ( CONTENT_SETTING_BLOCK ) ;
 SimulateAudioStarting ( ) ;
 EXPECT_TRUE ( RecordedSiteMuted ( ) ) ;
 ExpectRecordedForReason ( SoundContentSettingObserver : : MuteReason : : kMuteByDefault ) ;
 }