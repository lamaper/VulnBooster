static void main_loop(void)

{

    int r;


    qemu_system_ready = 1;

    qemu_cond_broadcast(&qemu_system_cond);




    for (;;) {

        do {


            int64_t ti;



            tcg_cpu_exec();



            ti = profile_getclock();


            main_loop_wait(qemu_calculate_timeout());


            dev_time += profile_getclock() - ti;


        } while (vm_can_run());



        if (qemu_debug_requested()) {

            monitor_protocol_event(QEVENT_DEBUG, NULL);

            vm_stop(EXCP_DEBUG);

        }

        if (qemu_shutdown_requested()) {

            monitor_protocol_event(QEVENT_SHUTDOWN, NULL);

            if (no_shutdown) {

                vm_stop(0);

                no_shutdown = 0;

            } else

                break;

        }

        if (qemu_reset_requested()) {

            monitor_protocol_event(QEVENT_RESET, NULL);

            pause_all_vcpus();

            qemu_system_reset();

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

    pause_all_vcpus();

}
