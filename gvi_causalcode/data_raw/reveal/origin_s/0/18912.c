IN_PROC_BROWSER_TEST_F ( ChooserDialogViewTest , InitialState ) {
 EXPECT_EQ ( table_view_ -> RowCount ( ) , 1 ) ;
 EXPECT_EQ ( table_model_ -> GetText ( 0 , 0 ) , l10n_util : : GetStringUTF16 ( IDS_DEVICE_CHOOSER_NO_DEVICES_FOUND_PROMPT ) ) ;
 EXPECT_FALSE ( table_view_ -> enabled ( ) ) ;
 EXPECT_EQ ( table_view_ -> SelectedRowCount ( ) , 0 ) ;
 EXPECT_EQ ( table_view_ -> FirstSelectedRow ( ) , - 1 ) ;
 }