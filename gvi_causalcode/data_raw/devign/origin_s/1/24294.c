static void main_loop(void)

{

    bool nonblocking;

    int last_io __attribute__ ((unused)) = 0;


    int64_t ti;


    int r;



    qemu_main_loop_start();



    for (;;) {


        nonblocking = !kvm_enabled() && last_io > 0;


        nonblocking = cpu_exec_all();

        if (vm_request_pending()) {

            nonblocking = true;

        }



        ti = profile_getclock();


        last_io = main_loop_wait(nonblocking);


        dev_time += profile_getclock() - ti;




        if (qemu_debug_requested()) {

            vm_stop(VMSTOP_DEBUG);

        }

        if (qemu_shutdown_requested()) {

            qemu_kill_report();

            monitor_protocol_event(QEVENT_SHUTDOWN, NULL);

            if (no_shutdown) {

                vm_stop(VMSTOP_SHUTDOWN);

            } else

                break;

        }

        if (qemu_reset_requested()) {

            pause_all_vcpus();

            cpu_synchronize_all_states();

            qemu_system_reset(VMRESET_REPORT);

            resume_all_vcpus();

        }

        if (qemu_powerdown_requested()) {

            monitor_protocol_event(QEVENT_POWERDOWN, NULL);

            qemu_irq_raise(qemu_system_powerdown);

        }

        if ((r = qemu_vmstop_requested())) {

            vm_stop(r);

        }

    }

    bdrv_close_all();

    pause_all_vcpus();

}
