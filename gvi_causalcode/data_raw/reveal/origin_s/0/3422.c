IN_PROC_BROWSER_TEST_F ( BluetoothChooserBrowserTest , InvokeDialog_PairedModal ) {
 set_status ( FakeBluetoothChooserController : : BluetoothStatus : : IDLE ) ;
 AddPairedDevice ( ) ;
 RunDialog ( ) ;
 }