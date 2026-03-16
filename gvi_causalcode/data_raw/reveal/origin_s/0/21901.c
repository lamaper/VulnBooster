static int list_config ( char * interface ) {
 if ( ! interface ) {
 errmsg_print ( "ERROR: No interface specified." ) ;
 return EXIT_CODE_NO_INTERFACE_SPECIFIED ;
 }
 if ( is_specified_interface ( interface , INTERFACE_ANDROID_BLUETOOTH_EXTERNAL_PARSER ) ) {
 printf ( "arg {
number=0}
{
call=--adb-server-ip}
{
display=ADB Server IP Address}
{
type=string}
{
default=127.0.0.1}
\n" "arg {
number=1}
{
call=--adb-server-tcp-port}
{
display=ADB Server TCP Port}
{
type=integer}
{
range=0,65535}
{
default=5037}
\n" "arg {
number=2}
{
call=--bt-server-tcp-port}
{
display=Bluetooth Server TCP Port}
{
type=integer}
{
range=0,65535}
{
default=4330}
\n" "arg {
number=3}
{
call=--bt-forward-socket}
{
display=Forward Bluetooth Socket}
{
type=boolean}
{
default=false}
\n" "arg {
number=4}
{
call=--bt-local-ip}
{
display=Bluetooth Local IP Address}
{
type=string}
{
default=127.0.0.1}
\n" "arg {
number=5}
{
call=--bt-local-tcp-port}
{
display=Bluetooth Local TCP Port}
{
type=integer}
{
range=0,65535}
{
default=4330}
{
tooltip=Used to do \"adb forward tcp:LOCAL_TCP_PORT tcp:SERVER_TCP_PORT\"}
\n" "arg {
number=6}
{
call=--verbose}
{
display=Verbose/Debug output on console}
{
type=boolean}
{
default=false}
\n" ) ;
 return EXIT_CODE_SUCCESS ;
 }
 else if ( is_specified_interface ( interface , INTERFACE_ANDROID_BLUETOOTH_HCIDUMP ) || is_specified_interface ( interface , INTERFACE_ANDROID_BLUETOOTH_BTSNOOP_NET ) || is_specified_interface ( interface , INTERFACE_ANDROID_WIFI_TCPDUMP ) ) {
 printf ( "arg {
number=0}
{
call=--adb-server-ip}
{
display=ADB Server IP Address}
{
type=string}
{
default=127.0.0.1}
\n" "arg {
number=1}
{
call=--adb-server-tcp-port}
{
display=ADB Server TCP Port}
{
type=integer}
{
range=0,65535}
{
default=5037}
\n" "arg {
number=2}
{
call=--verbose}
{
display=Verbose/Debug output on console}
{
type=boolean}
{
default=false}
\n" ) ;
 return EXIT_CODE_SUCCESS ;
 }
 else if ( is_specified_interface ( interface , INTERFACE_ANDROID_LOGCAT_MAIN ) || is_specified_interface ( interface , INTERFACE_ANDROID_LOGCAT_SYSTEM ) || is_specified_interface ( interface , INTERFACE_ANDROID_LOGCAT_RADIO ) || is_specified_interface ( interface , INTERFACE_ANDROID_LOGCAT_EVENTS ) ) {
 printf ( "arg {
number=0}
{
call=--adb-server-ip}
{
display=ADB Server IP Address}
{
type=string}
{
default=127.0.0.1}
\n" "arg {
number=1}
{
call=--adb-server-tcp-port}
{
display=ADB Server TCP Port}
{
type=integer}
{
range=0,65535}
{
default=5037}
\n" "arg {
number=2}
{
call=--logcat-text}
{
display=Use text logcat}
{
type=boolean}
{
default=false}
\n" "arg {
number=3}
{
call=--verbose}
{
display=Verbose/Debug output on console}
{
type=boolean}
{
default=false}
\n" ) ;
 return EXIT_CODE_SUCCESS ;
 }
 else if ( is_specified_interface ( interface , INTERFACE_ANDROID_LOGCAT_TEXT_MAIN ) || is_specified_interface ( interface , INTERFACE_ANDROID_LOGCAT_TEXT_SYSTEM ) || is_specified_interface ( interface , INTERFACE_ANDROID_LOGCAT_TEXT_RADIO ) || is_specified_interface ( interface , INTERFACE_ANDROID_LOGCAT_TEXT_EVENTS ) || is_specified_interface ( interface , INTERFACE_ANDROID_LOGCAT_TEXT_CRASH ) ) {
 printf ( "arg {
number=0}
{
call=--adb-server-ip}
{
display=ADB Server IP Address}
{
type=string}
{
default=127.0.0.1}
\n" "arg {
number=1}
{
call=--adb-server-tcp-port}
{
display=ADB Server TCP Port}
{
type=integer}
{
range=0,65535}
{
default=5037}
\n" "arg {
number=2}
{
call=--verbose}
{
display=Verbose/Debug output on console}
{
type=boolean}
{
default=false}
\n" ) ;
 return EXIT_CODE_SUCCESS ;
 }
 errmsg_print ( "ERROR: Invalid interface: <%s>" , interface ) ;
 return EXIT_CODE_INVALID_INTERFACE ;
 }