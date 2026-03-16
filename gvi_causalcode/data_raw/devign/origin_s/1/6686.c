void CALLBACK host_alarm_handler(UINT uTimerID, UINT uMsg,

                                 DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2)


static void host_alarm_handler(int host_signum)


{



    {

        static int64_t delta_min = INT64_MAX;

        static int64_t delta_max, delta_cum, last_clock, delta, ti;

        static int count;

        ti = qemu_get_clock(vm_clock);

        if (last_clock != 0) {

            delta = ti - last_clock;

            if (delta < delta_min)

                delta_min = delta;

            if (delta > delta_max)

                delta_max = delta;

            delta_cum += delta;

            if (++count == DISP_FREQ) {

                printf("timer: min=%" PRId64 " us max=%" PRId64 " us avg=%" PRId64 " us avg_freq=%0.3f Hz\n",

                       muldiv64(delta_min, 1000000, ticks_per_sec),

                       muldiv64(delta_max, 1000000, ticks_per_sec),

                       muldiv64(delta_cum, 1000000 / DISP_FREQ, ticks_per_sec),

                       (double)ticks_per_sec / ((double)delta_cum / DISP_FREQ));

                count = 0;

                delta_min = INT64_MAX;

                delta_max = 0;

                delta_cum = 0;

            }

        }

        last_clock = ti;

    }


    if (alarm_has_dynticks(alarm_timer) ||

        qemu_timer_expired(active_timers[QEMU_TIMER_VIRTUAL],

                           qemu_get_clock(vm_clock)) ||

        qemu_timer_expired(active_timers[QEMU_TIMER_REALTIME],

                           qemu_get_clock(rt_clock))) {


        struct qemu_alarm_win32 *data = ((struct qemu_alarm_timer*)dwUser)->priv;

        SetEvent(data->host_alarm);


        CPUState *env = next_cpu;



         

        cpu_interrupt(env, CPU_INTERRUPT_EXIT);


        if (env->kqemu_enabled) {

            kqemu_cpu_interrupt(env);

        }


        event_pending = 1;

    }

}
