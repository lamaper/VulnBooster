IN_PROC_BROWSER_TEST_F ( BluetoothChooserBrowserTest , InvokeDialog_ConnectedModal ) {
 set_status ( FakeBluetoothChooserController : : BluetoothStatus : : IDLE ) ;
 AddConnectedDevice ( ) ;
 RunDialog ( ) ;
 }