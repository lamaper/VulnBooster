void proto_reg_handoff_btgatt ( void ) {
 const struct uuid_dissectors_t {
 const gchar * const uuid ;
 gchar * const short_name ;
 int ( * const dissect_func ) ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , void * data ) ;
 }
 uuid_dissectors [ ] = {
 {
 "6e400001-b5a3-f393-e0a9-e50e24dcca9e" , "Nordic UART Service" , NULL }
 , {
 "6e400002-b5a3-f393-e0a9-e50e24dcca9e" , "Nordic UART Tx" , dissect_btgatt_nordic_uart_tx }
 , {
 "6e400003-b5a3-f393-e0a9-e50e24dcca9e" , "Nordic UART Rx" , dissect_btgatt_nordic_uart_rx }
 , {
 "00001530-1212-efde-1523-785feabcd123" , "Nordic DFU Service" , NULL }
 , {
 "00001531-1212-efde-1523-785feabcd123" , "Nordic DFU Control Point" , dissect_btgatt_nordic_dfu_control_point }
 , {
 "00001532-1212-efde-1523-785feabcd123" , "Nordic DFU Packet" , dissect_btgatt_nordic_dfu_packet }
 , {
 "e95d0753-251d-470a-a062-fa1922dfa9a8" , "micro:bit Accelerometer Service" , NULL }
 , {
 "e95dca4b-251d-470a-a062-fa1922dfa9a8" , "micro:bit Accelerometer Data" , dissect_btgatt_microbit_accelerometer_data }
 , {
 "e95dfb24-251d-470a-a062-fa1922dfa9a8" , "micro:bit Accelerometer Period" , dissect_btgatt_microbit_accelerometer_period }
 , {
 "e95df2d8-251d-470a-a062-fa1922dfa9a8" , "micro:bit Magnetometer Service" , NULL }
 , {
 "e95dfb11-251d-470a-a062-fa1922dfa9a8" , "micro:bit Magnetometer Data" , dissect_btgatt_microbit_magnetometer_data }
 , {
 "e95d386c-251d-470a-a062-fa1922dfa9a8" , "micro:bit Magnetometer Period" , dissect_btgatt_microbit_magnetometer_period }
 , {
 "e95d9715-251d-470a-a062-fa1922dfa9a8" , "micro:bit Magnetometer Bearing" , dissect_btgatt_microbit_magnetometer_bearing }
 , {
 "e95d9882-251d-470a-a062-fa1922dfa9a8" , "micro:bit Button Service" , NULL }
 , {
 "e95dda90-251d-470a-a062-fa1922dfa9a8" , "micro:bit Button A State" , dissect_btgatt_microbit_button_a_state }
 , {
 "e95dda91-251d-470a-a062-fa1922dfa9a8" , "micro:bit Button B State" , dissect_btgatt_microbit_button_b_state }
 , {
 "e95d127b-251d-470a-a062-fa1922dfa9a8" , "micro:bit IO Pin Service" , NULL }
 , {
 "e95d8d00-251d-470a-a062-fa1922dfa9a8" , "micro:bit Pin Data" , dissect_btgatt_microbit_pin_data }
 , {
 "e95d5899-251d-470a-a062-fa1922dfa9a8" , "micro:bit Pin AD Configuration" , dissect_btgatt_microbit_pin_ad_config }
 , {
 "e95db9fe-251d-470a-a062-fa1922dfa9a8" , "micro:bit Pin IO Configuration" , dissect_btgatt_microbit_pin_io_config }
 , {
 "e95dd822-251d-470a-a062-fa1922dfa9a8" , "micro:bit PWM Control" , dissect_btgatt_microbit_pwm_control }
 , {
 "e95dd91d-251d-470a-a062-fa1922dfa9a8" , "micro:bit LED Service" , NULL }
 , {
 "e95d7b77-251d-470a-a062-fa1922dfa9a8" , "micro:bit LED Matrix State" , dissect_btgatt_microbit_led_matrix }
 , {
 "e95d93ee-251d-470a-a062-fa1922dfa9a8" , "micro:bit LED Text" , dissect_btgatt_microbit_led_text }
 , {
 "e95d0d2d-251d-470a-a062-fa1922dfa9a8" , "micro:bit Scrolling Delay" , dissect_btgatt_microbit_scrolling_delay }
 , {
 "e95d93af-251d-470a-a062-fa1922dfa9a8" , "micro:bit Event Service" , NULL }
 , {
 "e95db84c-251d-470a-a062-fa1922dfa9a8" , "micro:bit MicroBit Requirements" , dissect_btgatt_microbit_microbit_requirements }
 , {
 "e95d9775-251d-470a-a062-fa1922dfa9a8" , "micro:bit MicroBit Event" , dissect_btgatt_microbit_microbit_event }
 , {
 "e95d23c4-251d-470a-a062-fa1922dfa9a8" , "micro:bit Client Requirements" , dissect_btgatt_microbit_client_requirements }
 , {
 "e95d5404-251d-470a-a062-fa1922dfa9a8" , "micro:bit Client Event" , dissect_btgatt_microbit_client_event }
 , {
 "e95d93b0-251d-470a-a062-fa1922dfa9a8" , "micro:bit DFU Control Service" , NULL }
 , {
 "e95d93b1-251d-470a-a062-fa1922dfa9a8" , "micro:bit DFU Control" , dissect_btgatt_microbit_dfu_control }
 , {
 "e95d6100-251d-470a-a062-fa1922dfa9a8" , "micro:bit Temperature Service" , NULL }
 , {
 "e95d9250-251d-470a-a062-fa1922dfa9a8" , "micro:bit Temperature" , dissect_btgatt_microbit_temperature_value }
 , {
 "e95d1b25-251d-470a-a062-fa1922dfa9a8" , "micro:bit Temperature Period" , dissect_btgatt_microbit_temperature_period }
 , {
 NULL , NULL , NULL }
 , }
 ;
 for ( gint i = 0 ;
 uuid_dissectors [ i ] . uuid ;
 i ++ ) {
 wmem_tree_insert_string ( bluetooth_uuids , uuid_dissectors [ i ] . uuid , uuid_dissectors [ i ] . short_name , 0 ) ;
 if ( uuid_dissectors [ i ] . dissect_func ) {
 dissector_handle_t handle = create_dissector_handle ( uuid_dissectors [ i ] . dissect_func , proto_btgatt ) ;
 dissector_add_string ( "bluetooth.uuid" , uuid_dissectors [ i ] . uuid , handle ) ;
 }
 }
 }