void show_progress ( int frame_in , int frame_out , uint64_t dx_time ) {
 fprintf ( stderr , "%d decoded frames/%d showed frames in %" PRId64 " us (%.2f fps)\r" , frame_in , frame_out , dx_time , ( double ) frame_out * 1000000.0 / ( double ) dx_time ) ;
 }