abi_long do_syscall(void *cpu_env, int num, abi_long arg1,
                    abi_long arg2, abi_long arg3, abi_long arg4,
                    abi_long arg5, abi_long arg6, abi_long arg7,
                    abi_long arg8)
{
    CPUState *cpu = ENV_GET_CPU(cpu_env);
    abi_long ret;
    struct stat st;
    struct statfs stfs;
    void *p;

     
    {
        static int flag;
        flag = !flag;
        if (flag) {
            return -TARGET_ERESTARTSYS;


    gemu_log("syscall %d", num);

    trace_guest_user_syscall(cpu, num, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
    if(do_strace)
        print_syscall(num, arg1, arg2, arg3, arg4, arg5, arg6);
    switch(num) {
    case TARGET_NR_exit:
         
        if (block_signals()) {
            ret = -TARGET_ERESTARTSYS;
        if (CPU_NEXT(first_cpu)) {
            TaskState *ts;
            cpu_list_lock();
             
            QTAILQ_REMOVE(&cpus, cpu, node);
            cpu_list_unlock();
            ts = cpu->opaque;
            if (ts->child_tidptr) {
                put_user_u32(0, ts->child_tidptr);
                sys_futex(g2h(ts->child_tidptr), FUTEX_WAKE, INT_MAX,
                          NULL, NULL, 0);
            thread_cpu = NULL;
            object_unref(OBJECT(cpu));
            g_free(ts);
            rcu_unregister_thread();
            pthread_exit(NULL);

        _mcleanup();

        gdb_exit(cpu_env, arg1);
        _exit(arg1);
        ret = 0;  
    case TARGET_NR_read:
        if (arg3 == 0)
            ret = 0;
        else {
            if (!(p = lock_user(VERIFY_WRITE, arg2, arg3, 0)))
                goto efault;
            ret = get_errno(safe_read(arg1, p, arg3));
            if (ret >= 0 &&
                fd_trans_host_to_target_data(arg1)) {
                ret = fd_trans_host_to_target_data(arg1)(p, ret);
            unlock_user(p, arg2, ret);
    case TARGET_NR_write:
        if (!(p = lock_user(VERIFY_READ, arg2, arg3, 1)))
            goto efault;
        ret = get_errno(safe_write(arg1, p, arg3));
        unlock_user(p, arg2, 0);

    case TARGET_NR_open:
        if (!(p = lock_user_string(arg1)))
            goto efault;
        ret = get_errno(do_openat(cpu_env, AT_FDCWD, p,
                                  target_to_host_bitmask(arg2, fcntl_flags_tbl),
                                  arg3));
        fd_trans_unregister(ret);
        unlock_user(p, arg1, 0);

    case TARGET_NR_openat:
        if (!(p = lock_user_string(arg2)))
            goto efault;
        ret = get_errno(do_openat(cpu_env, arg1, p,
                                  target_to_host_bitmask(arg3, fcntl_flags_tbl),
                                  arg4));
        fd_trans_unregister(ret);
        unlock_user(p, arg2, 0);

    case TARGET_NR_name_to_handle_at:
        ret = do_name_to_handle_at(arg1, arg2, arg3, arg4, arg5);


    case TARGET_NR_open_by_handle_at:
        ret = do_open_by_handle_at(arg1, arg2, arg3);
        fd_trans_unregister(ret);

    case TARGET_NR_close:
        fd_trans_unregister(arg1);
        ret = get_errno(close(arg1));
    case TARGET_NR_brk:
        ret = do_brk(arg1);

    case TARGET_NR_fork:
        ret = get_errno(do_fork(cpu_env, SIGCHLD, 0, 0, 0, 0));


    case TARGET_NR_waitpid:
        {
            int status;
            ret = get_errno(safe_wait4(arg1, &status, arg3, 0));
            if (!is_error(ret) && arg2 && ret
                && put_user_s32(host_to_target_waitstatus(status), arg2))
                goto efault;


    case TARGET_NR_waitid:
        {
            siginfo_t info;
            info.si_pid = 0;
            ret = get_errno(safe_waitid(arg1, arg2, &info, arg4, NULL));
            if (!is_error(ret) && arg3 && info.si_pid != 0) {
                if (!(p = lock_user(VERIFY_WRITE, arg3, sizeof(target_siginfo_t), 0)))
                    goto efault;
                host_to_target_siginfo(p, &info);
                unlock_user(p, arg3, sizeof(target_siginfo_t));


    case TARGET_NR_creat:
        if (!(p = lock_user_string(arg1)))
            goto efault;
        ret = get_errno(creat(p, arg2));
        fd_trans_unregister(ret);
        unlock_user(p, arg1, 0);


    case TARGET_NR_link:
        {
            void * p2;
            p = lock_user_string(arg1);
            p2 = lock_user_string(arg2);
            if (!p || !p2)
                ret = -TARGET_EFAULT;
            else
                ret = get_errno(link(p, p2));
            unlock_user(p2, arg2, 0);
            unlock_user(p, arg1, 0);


    case TARGET_NR_linkat:
        {
            void * p2 = NULL;
            if (!arg2 || !arg4)
                goto efault;
            p  = lock_user_string(arg2);
            p2 = lock_user_string(arg4);
            if (!p || !p2)
                ret = -TARGET_EFAULT;
            else
                ret = get_errno(linkat(arg1, p, arg3, p2, arg5));
            unlock_user(p, arg2, 0);
            unlock_user(p2, arg4, 0);


    case TARGET_NR_unlink:
        if (!(p = lock_user_string(arg1)))
            goto efault;
        ret = get_errno(unlink(p));
        unlock_user(p, arg1, 0);


    case TARGET_NR_unlinkat:
        if (!(p = lock_user_string(arg2)))
            goto efault;
        ret = get_errno(unlinkat(arg1, p, arg3));
        unlock_user(p, arg2, 0);

    case TARGET_NR_execve:
        {
            char **argp, **envp;
            int argc, envc;
            abi_ulong gp;
            abi_ulong guest_argp;
            abi_ulong guest_envp;
            abi_ulong addr;
            char **q;
            int total_size = 0;
            argc = 0;
            guest_argp = arg2;
            for (gp = guest_argp; gp; gp += sizeof(abi_ulong)) {
                if (get_user_ual(addr, gp))
                    goto efault;
                if (!addr)
                argc++;
            envc = 0;
            guest_envp = arg3;
            for (gp = guest_envp; gp; gp += sizeof(abi_ulong)) {
                if (get_user_ual(addr, gp))
                    goto efault;
                if (!addr)
                envc++;
            argp = alloca((argc + 1) * sizeof(void *));
            envp = alloca((envc + 1) * sizeof(void *));
            for (gp = guest_argp, q = argp; gp;
                  gp += sizeof(abi_ulong), q++) {
                if (get_user_ual(addr, gp))
                    goto execve_efault;
                if (!addr)
                if (!(*q = lock_user_string(addr)))
                    goto execve_efault;
                total_size += strlen(*q) + 1;
            *q = NULL;
            for (gp = guest_envp, q = envp; gp;
                  gp += sizeof(abi_ulong), q++) {
                if (get_user_ual(addr, gp))
                    goto execve_efault;
                if (!addr)
                if (!(*q = lock_user_string(addr)))
                    goto execve_efault;
                total_size += strlen(*q) + 1;
            *q = NULL;
            if (!(p = lock_user_string(arg1)))
                goto execve_efault;
             
            ret = get_errno(safe_execve(p, argp, envp));
            unlock_user(p, arg1, 0);
            goto execve_end;
        execve_efault:
            ret = -TARGET_EFAULT;
        execve_end:
            for (gp = guest_argp, q = argp; *q;
                  gp += sizeof(abi_ulong), q++) {
                if (get_user_ual(addr, gp)
                    || !addr)
                unlock_user(*q, addr, 0);
            for (gp = guest_envp, q = envp; *q;
                  gp += sizeof(abi_ulong), q++) {
                if (get_user_ual(addr, gp)
                    || !addr)
                unlock_user(*q, addr, 0);
    case TARGET_NR_chdir:
        if (!(p = lock_user_string(arg1)))
            goto efault;
        ret = get_errno(chdir(p));
        unlock_user(p, arg1, 0);

    case TARGET_NR_time:
        {
            time_t host_time;
            ret = get_errno(time(&host_time));
            if (!is_error(ret)
                && arg1
                && put_user_sal(host_time, arg1))
                goto efault;


    case TARGET_NR_mknod:
        if (!(p = lock_user_string(arg1)))
            goto efault;
        ret = get_errno(mknod(p, arg2, arg3));
        unlock_user(p, arg1, 0);


    case TARGET_NR_mknodat:
        if (!(p = lock_user_string(arg2)))
            goto efault;
        ret = get_errno(mknodat(arg1, p, arg3, arg4));
        unlock_user(p, arg2, 0);


    case TARGET_NR_chmod:
        if (!(p = lock_user_string(arg1)))
            goto efault;
        ret = get_errno(chmod(p, arg2));
        unlock_user(p, arg1, 0);


    case TARGET_NR_break:
        goto unimplemented;


    case TARGET_NR_oldstat:
        goto unimplemented;

    case TARGET_NR_lseek:
        ret = get_errno(lseek(arg1, arg2, arg3));

     
    case TARGET_NR_getxpid:
        ((CPUAlphaState *)cpu_env)->ir[IR_A4] = getppid();
        ret = get_errno(getpid());


    case TARGET_NR_getpid:
        ret = get_errno(getpid());

    case TARGET_NR_mount:
        {
             
            void *p2, *p3;
            if (arg1) {
                p = lock_user_string(arg1);
                if (!p) {
                    goto efault;
            } else {
                p = NULL;
            p2 = lock_user_string(arg2);
            if (!p2) {
                if (arg1) {
                    unlock_user(p, arg1, 0);
                goto efault;
            if (arg3) {
                p3 = lock_user_string(arg3);
                if (!p3) {
                    if (arg1) {
                        unlock_user(p, arg1, 0);
                    unlock_user(p2, arg2, 0);
                    goto efault;
            } else {
                p3 = NULL;
             
            if (!arg5) {
                ret = mount(p, p2, p3, (unsigned long)arg4, NULL);
            } else {
                ret = mount(p, p2, p3, (unsigned long)arg4, g2h(arg5));
            ret = get_errno(ret);
            if (arg1) {
                unlock_user(p, arg1, 0);
            unlock_user(p2, arg2, 0);
            if (arg3) {
                unlock_user(p3, arg3, 0);

    case TARGET_NR_umount:
        if (!(p = lock_user_string(arg1)))
            goto efault;
        ret = get_errno(umount(p));
        unlock_user(p, arg1, 0);


    case TARGET_NR_stime:
        {
            time_t host_time;
            if (get_user_sal(host_time, arg1))
                goto efault;
            ret = get_errno(stime(&host_time));

    case TARGET_NR_ptrace:
        goto unimplemented;

    case TARGET_NR_alarm:
        ret = alarm(arg1);


    case TARGET_NR_oldfstat:
        goto unimplemented;


    case TARGET_NR_pause:
        if (!block_signals()) {
            sigsuspend(&((TaskState *)cpu->opaque)->signal_mask);
        ret = -TARGET_EINTR;


    case TARGET_NR_utime:
        {
            struct utimbuf tbuf, *host_tbuf;
            struct target_utimbuf *target_tbuf;
            if (arg2) {
                if (!lock_user_struct(VERIFY_READ, target_tbuf, arg2, 1))
                    goto efault;
                tbuf.actime = tswapal(target_tbuf->actime);
                tbuf.modtime = tswapal(target_tbuf->modtime);
                unlock_user_struct(target_tbuf, arg2, 0);
                host_tbuf = &tbuf;
            } else {
                host_tbuf = NULL;
            if (!(p = lock_user_string(arg1)))
                goto efault;
            ret = get_errno(utime(p, host_tbuf));
            unlock_user(p, arg1, 0);


    case TARGET_NR_utimes:
        {
            struct timeval *tvp, tv[2];
            if (arg2) {
                if (copy_from_user_timeval(&tv[0], arg2)
                    || copy_from_user_timeval(&tv[1],
                                              arg2 + sizeof(struct target_timeval)))
                    goto efault;
                tvp = tv;
            } else {
                tvp = NULL;
            if (!(p = lock_user_string(arg1)))
                goto efault;
            ret = get_errno(utimes(p, tvp));
            unlock_user(p, arg1, 0);


    case TARGET_NR_futimesat:
        {
            struct timeval *tvp, tv[2];
            if (arg3) {
                if (copy_from_user_timeval(&tv[0], arg3)
                    || copy_from_user_timeval(&tv[1],
                                              arg3 + sizeof(struct target_timeval)))
                    goto efault;
                tvp = tv;
            } else {
                tvp = NULL;
            if (!(p = lock_user_string(arg2)))
                goto efault;
            ret = get_errno(futimesat(arg1, path(p), tvp));
            unlock_user(p, arg2, 0);


    case TARGET_NR_stty:
        goto unimplemented;


    case TARGET_NR_gtty:
        goto unimplemented;


    case TARGET_NR_access:
        if (!(p = lock_user_string(arg1)))
            goto efault;
        ret = get_errno(access(path(p), arg2));
        unlock_user(p, arg1, 0);


    case TARGET_NR_faccessat:
        if (!(p = lock_user_string(arg2)))
            goto efault;
        ret = get_errno(faccessat(arg1, p, arg3, 0));
        unlock_user(p, arg2, 0);


    case TARGET_NR_nice:
        ret = get_errno(nice(arg1));


    case TARGET_NR_ftime:
        goto unimplemented;

    case TARGET_NR_sync:
        sync();
        ret = 0;
    case TARGET_NR_kill:
        ret = get_errno(safe_kill(arg1, target_to_host_signal(arg2)));

    case TARGET_NR_rename:
        {
            void *p2;
            p = lock_user_string(arg1);
            p2 = lock_user_string(arg2);
            if (!p || !p2)
                ret = -TARGET_EFAULT;
            else
                ret = get_errno(rename(p, p2));
            unlock_user(p2, arg2, 0);
            unlock_user(p, arg1, 0);


    case TARGET_NR_renameat:
        {
            void *p2;
            p  = lock_user_string(arg2);
            p2 = lock_user_string(arg4);
            if (!p || !p2)
                ret = -TARGET_EFAULT;
            else
                ret = get_errno(renameat(arg1, p, arg3, p2));
            unlock_user(p2, arg4, 0);
            unlock_user(p, arg2, 0);


    case TARGET_NR_mkdir:
        if (!(p = lock_user_string(arg1)))
            goto efault;
        ret = get_errno(mkdir(p, arg2));
        unlock_user(p, arg1, 0);


    case TARGET_NR_mkdirat:
        if (!(p = lock_user_string(arg2)))
            goto efault;
        ret = get_errno(mkdirat(arg1, p, arg3));
        unlock_user(p, arg2, 0);


    case TARGET_NR_rmdir:
        if (!(p = lock_user_string(arg1)))
            goto efault;
        ret = get_errno(rmdir(p));
        unlock_user(p, arg1, 0);

    case TARGET_NR_dup:
        ret = get_errno(dup(arg1));
        if (ret >= 0) {
            fd_trans_dup(arg1, ret);

    case TARGET_NR_pipe:
        ret = do_pipe(cpu_env, arg1, 0, 0);


    case TARGET_NR_pipe2:
        ret = do_pipe(cpu_env, arg1,
                      target_to_host_bitmask(arg2, fcntl_flags_tbl), 1);

    case TARGET_NR_times:
        {
            struct target_tms *tmsp;
            struct tms tms;
            ret = get_errno(times(&tms));
            if (arg1) {
                tmsp = lock_user(VERIFY_WRITE, arg1, sizeof(struct target_tms), 0);
                if (!tmsp)
                    goto efault;
                tmsp->tms_utime = tswapal(host_to_target_clock_t(tms.tms_utime));
                tmsp->tms_stime = tswapal(host_to_target_clock_t(tms.tms_stime));
                tmsp->tms_cutime = tswapal(host_to_target_clock_t(tms.tms_cutime));
                tmsp->tms_cstime = tswapal(host_to_target_clock_t(tms.tms_cstime));
            if (!is_error(ret))
                ret = host_to_target_clock_t(ret);

    case TARGET_NR_prof:
        goto unimplemented;


    case TARGET_NR_signal:
        goto unimplemented;

    case TARGET_NR_acct:
        if (arg1 == 0) {
            ret = get_errno(acct(NULL));
        } else {
            if (!(p = lock_user_string(arg1)))
                goto efault;
            ret = get_errno(acct(path(p)));
            unlock_user(p, arg1, 0);

    case TARGET_NR_umount2:
        if (!(p = lock_user_string(arg1)))
            goto efault;
        ret = get_errno(umount2(p, arg2));
        unlock_user(p, arg1, 0);


    case TARGET_NR_lock:
        goto unimplemented;

    case TARGET_NR_ioctl:
        ret = do_ioctl(arg1, arg2, arg3);
    case TARGET_NR_fcntl:
        ret = do_fcntl(arg1, arg2, arg3);

    case TARGET_NR_mpx:
        goto unimplemented;

    case TARGET_NR_setpgid:
        ret = get_errno(setpgid(arg1, arg2));

    case TARGET_NR_ulimit:
        goto unimplemented;


    case TARGET_NR_oldolduname:
        goto unimplemented;

    case TARGET_NR_umask:
        ret = get_errno(umask(arg1));
    case TARGET_NR_chroot:
        if (!(p = lock_user_string(arg1)))
            goto efault;
        ret = get_errno(chroot(p));
        unlock_user(p, arg1, 0);

    case TARGET_NR_ustat:
        goto unimplemented;


    case TARGET_NR_dup2:
        ret = get_errno(dup2(arg1, arg2));
        if (ret >= 0) {
            fd_trans_dup(arg1, arg2);


    case TARGET_NR_dup3:
        ret = get_errno(dup3(arg1, arg2, arg3));
        if (ret >= 0) {
            fd_trans_dup(arg1, arg2);


    case TARGET_NR_getppid:
        ret = get_errno(getppid());


    case TARGET_NR_getpgrp:
        ret = get_errno(getpgrp());

    case TARGET_NR_setsid:
        ret = get_errno(setsid());

    case TARGET_NR_sigaction:
        {

            struct target_sigaction act, oact, *pact = 0;
            struct target_old_sigaction *old_act;
            if (arg2) {
                if (!lock_user_struct(VERIFY_READ, old_act, arg2, 1))
                    goto efault;
                act._sa_handler = old_act->_sa_handler;
                target_siginitset(&act.sa_mask, old_act->sa_mask);
                act.sa_flags = old_act->sa_flags;
                act.sa_restorer = 0;
                unlock_user_struct(old_act, arg2, 0);
                pact = &act;
            ret = get_errno(do_sigaction(arg1, pact, &oact));
            if (!is_error(ret) && arg3) {
                if (!lock_user_struct(VERIFY_WRITE, old_act, arg3, 0))
                    goto efault;
                old_act->_sa_handler = oact._sa_handler;
                old_act->sa_mask = oact.sa_mask.sig[0];
                old_act->sa_flags = oact.sa_flags;
                unlock_user_struct(old_act, arg3, 1);

	    struct target_sigaction act, oact, *pact, *old_act;
	    if (arg2) {
                if (!lock_user_struct(VERIFY_READ, old_act, arg2, 1))
                    goto efault;
		act._sa_handler = old_act->_sa_handler;
		target_siginitset(&act.sa_mask, old_act->sa_mask.sig[0]);
		act.sa_flags = old_act->sa_flags;
		unlock_user_struct(old_act, arg2, 0);
		pact = &act;
	    } else {
		pact = NULL;
	    ret = get_errno(do_sigaction(arg1, pact, &oact));
	    if (!is_error(ret) && arg3) {
                if (!lock_user_struct(VERIFY_WRITE, old_act, arg3, 0))
                    goto efault;
		old_act->_sa_handler = oact._sa_handler;
		old_act->sa_flags = oact.sa_flags;
		old_act->sa_mask.sig[0] = oact.sa_mask.sig[0];
		old_act->sa_mask.sig[1] = 0;
		old_act->sa_mask.sig[2] = 0;
		old_act->sa_mask.sig[3] = 0;
		unlock_user_struct(old_act, arg3, 1);

            struct target_old_sigaction *old_act;
            struct target_sigaction act, oact, *pact;
            if (arg2) {
                if (!lock_user_struct(VERIFY_READ, old_act, arg2, 1))
                    goto efault;
                act._sa_handler = old_act->_sa_handler;
                target_siginitset(&act.sa_mask, old_act->sa_mask);
                act.sa_flags = old_act->sa_flags;
                act.sa_restorer = old_act->sa_restorer;
                unlock_user_struct(old_act, arg2, 0);
                pact = &act;
            } else {
                pact = NULL;
            ret = get_errno(do_sigaction(arg1, pact, &oact));
            if (!is_error(ret) && arg3) {
                if (!lock_user_struct(VERIFY_WRITE, old_act, arg3, 0))
                    goto efault;
                old_act->_sa_handler = oact._sa_handler;
                old_act->sa_mask = oact.sa_mask.sig[0];
                old_act->sa_flags = oact.sa_flags;
                old_act->sa_restorer = oact.sa_restorer;
                unlock_user_struct(old_act, arg3, 1);


    case TARGET_NR_rt_sigaction:
        {

            struct target_sigaction act, oact, *pact = 0;
            struct target_rt_sigaction *rt_act;
            if (arg4 != sizeof(target_sigset_t)) {
            if (arg2) {
                if (!lock_user_struct(VERIFY_READ, rt_act, arg2, 1))
                    goto efault;
                act._sa_handler = rt_act->_sa_handler;
                act.sa_mask = rt_act->sa_mask;
                act.sa_flags = rt_act->sa_flags;
                act.sa_restorer = arg5;
                unlock_user_struct(rt_act, arg2, 0);
                pact = &act;
            ret = get_errno(do_sigaction(arg1, pact, &oact));
            if (!is_error(ret) && arg3) {
                if (!lock_user_struct(VERIFY_WRITE, rt_act, arg3, 0))
                    goto efault;
                rt_act->_sa_handler = oact._sa_handler;
                rt_act->sa_mask = oact.sa_mask;
                rt_act->sa_flags = oact.sa_flags;
                unlock_user_struct(rt_act, arg3, 1);

            struct target_sigaction *act;
            struct target_sigaction *oact;
            if (arg4 != sizeof(target_sigset_t)) {
            if (arg2) {
                if (!lock_user_struct(VERIFY_READ, act, arg2, 1))
                    goto efault;
            } else
                act = NULL;
            if (arg3) {
                if (!lock_user_struct(VERIFY_WRITE, oact, arg3, 0)) {
                    ret = -TARGET_EFAULT;
                    goto rt_sigaction_fail;
            } else
                oact = NULL;
            ret = get_errno(do_sigaction(arg1, act, oact));
	rt_sigaction_fail:
            if (act)
                unlock_user_struct(act, arg2, 0);
            if (oact)
                unlock_user_struct(oact, arg3, 1);


    case TARGET_NR_sgetmask:
        {
            sigset_t cur_set;
            abi_ulong target_set;
            ret = do_sigprocmask(0, NULL, &cur_set);
            if (!ret) {
                host_to_target_old_sigset(&target_set, &cur_set);
                ret = target_set;


    case TARGET_NR_ssetmask:
        {
            sigset_t set, oset, cur_set;
            abi_ulong target_set = arg1;
             
            ret = do_sigprocmask(0, NULL, &cur_set);
            assert(!ret);
            target_to_host_old_sigset(&set, &target_set);
            sigorset(&set, &set, &cur_set);
            ret = do_sigprocmask(SIG_SETMASK, &set, &oset);
            if (!ret) {
                host_to_target_old_sigset(&target_set, &oset);
                ret = target_set;


    case TARGET_NR_sigprocmask:
        {

            sigset_t set, oldset;
            abi_ulong mask;
            int how;
            switch (arg1) {
            case TARGET_SIG_BLOCK:
                how = SIG_BLOCK;
            case TARGET_SIG_UNBLOCK:
                how = SIG_UNBLOCK;
            case TARGET_SIG_SETMASK:
                how = SIG_SETMASK;
            default:
                goto fail;
            mask = arg2;
            target_to_host_old_sigset(&set, &mask);
            ret = do_sigprocmask(how, &set, &oldset);
            if (!is_error(ret)) {
                host_to_target_old_sigset(&mask, &oldset);
                ret = mask;
                ((CPUAlphaState *)cpu_env)->ir[IR_V0] = 0;  

            sigset_t set, oldset, *set_ptr;
            int how;
            if (arg2) {
                switch (arg1) {
                case TARGET_SIG_BLOCK:
                    how = SIG_BLOCK;
                case TARGET_SIG_UNBLOCK:
                    how = SIG_UNBLOCK;
                case TARGET_SIG_SETMASK:
                    how = SIG_SETMASK;
                default:
                    goto fail;
                if (!(p = lock_user(VERIFY_READ, arg2, sizeof(target_sigset_t), 1)))
                    goto efault;
                target_to_host_old_sigset(&set, p);
                unlock_user(p, arg2, 0);
                set_ptr = &set;
            } else {
                how = 0;
                set_ptr = NULL;
            ret = do_sigprocmask(how, set_ptr, &oldset);
            if (!is_error(ret) && arg3) {
                if (!(p = lock_user(VERIFY_WRITE, arg3, sizeof(target_sigset_t), 0)))
                    goto efault;
                host_to_target_old_sigset(p, &oldset);
                unlock_user(p, arg3, sizeof(target_sigset_t));


    case TARGET_NR_rt_sigprocmask:
        {
            int how = arg1;
            sigset_t set, oldset, *set_ptr;
            if (arg4 != sizeof(target_sigset_t)) {
            if (arg2) {
                switch(how) {
                case TARGET_SIG_BLOCK:
                    how = SIG_BLOCK;
                case TARGET_SIG_UNBLOCK:
                    how = SIG_UNBLOCK;
                case TARGET_SIG_SETMASK:
                    how = SIG_SETMASK;
                default:
                    goto fail;
                if (!(p = lock_user(VERIFY_READ, arg2, sizeof(target_sigset_t), 1)))
                    goto efault;
                target_to_host_sigset(&set, p);
                unlock_user(p, arg2, 0);
                set_ptr = &set;
            } else {
                how = 0;
                set_ptr = NULL;
            ret = do_sigprocmask(how, set_ptr, &oldset);
            if (!is_error(ret) && arg3) {
                if (!(p = lock_user(VERIFY_WRITE, arg3, sizeof(target_sigset_t), 0)))
                    goto efault;
                host_to_target_sigset(p, &oldset);
                unlock_user(p, arg3, sizeof(target_sigset_t));

    case TARGET_NR_sigpending:
        {
            sigset_t set;
            ret = get_errno(sigpending(&set));
            if (!is_error(ret)) {
                if (!(p = lock_user(VERIFY_WRITE, arg1, sizeof(target_sigset_t), 0)))
                    goto efault;
                host_to_target_old_sigset(p, &set);
                unlock_user(p, arg1, sizeof(target_sigset_t));

    case TARGET_NR_rt_sigpending:
        {
            sigset_t set;
             
            if (arg2 > sizeof(target_sigset_t)) {
            ret = get_errno(sigpending(&set));
            if (!is_error(ret)) {
                if (!(p = lock_user(VERIFY_WRITE, arg1, sizeof(target_sigset_t), 0)))
                    goto efault;
                host_to_target_sigset(p, &set);
                unlock_user(p, arg1, sizeof(target_sigset_t));

    case TARGET_NR_sigsuspend:
        {
            TaskState *ts = cpu->opaque;

            abi_ulong mask = arg1;
            target_to_host_old_sigset(&ts->sigsuspend_mask, &mask);

            if (!(p = lock_user(VERIFY_READ, arg1, sizeof(target_sigset_t), 1)))
                goto efault;
            target_to_host_old_sigset(&ts->sigsuspend_mask, p);
            unlock_user(p, arg1, 0);

            ret = get_errno(safe_rt_sigsuspend(&ts->sigsuspend_mask,
                                               SIGSET_T_SIZE));
            if (ret != -TARGET_ERESTARTSYS) {
                ts->in_sigsuspend = 1;

    case TARGET_NR_rt_sigsuspend:
        {
            TaskState *ts = cpu->opaque;
            if (arg2 != sizeof(target_sigset_t)) {
            if (!(p = lock_user(VERIFY_READ, arg1, sizeof(target_sigset_t), 1)))
                goto efault;
            target_to_host_sigset(&ts->sigsuspend_mask, p);
            unlock_user(p, arg1, 0);
            ret = get_errno(safe_rt_sigsuspend(&ts->sigsuspend_mask,
                                               SIGSET_T_SIZE));
            if (ret != -TARGET_ERESTARTSYS) {
                ts->in_sigsuspend = 1;
    case TARGET_NR_rt_sigtimedwait:
        {
            sigset_t set;
            struct timespec uts, *puts;
            siginfo_t uinfo;
            if (arg4 != sizeof(target_sigset_t)) {
            if (!(p = lock_user(VERIFY_READ, arg1, sizeof(target_sigset_t), 1)))
                goto efault;
            target_to_host_sigset(&set, p);
            unlock_user(p, arg1, 0);
            if (arg3) {
                puts = &uts;
                target_to_host_timespec(puts, arg3);
            } else {
                puts = NULL;
            ret = get_errno(safe_rt_sigtimedwait(&set, &uinfo, puts,
                                                 SIGSET_T_SIZE));
            if (!is_error(ret)) {
                if (arg2) {
                    p = lock_user(VERIFY_WRITE, arg2, sizeof(target_siginfo_t),
                                  0);
                    if (!p) {
                        goto efault;
                    host_to_target_siginfo(p, &uinfo);
                    unlock_user(p, arg2, sizeof(target_siginfo_t));
                ret = host_to_target_signal(ret);
    case TARGET_NR_rt_sigqueueinfo:
        {
            siginfo_t uinfo;
            p = lock_user(VERIFY_READ, arg3, sizeof(target_siginfo_t), 1);
            if (!p) {
                goto efault;
            target_to_host_siginfo(&uinfo, p);
            unlock_user(p, arg1, 0);
            ret = get_errno(sys_rt_sigqueueinfo(arg1, arg2, &uinfo));

    case TARGET_NR_sigreturn:
        if (block_signals()) {
            ret = -TARGET_ERESTARTSYS;
        } else {
            ret = do_sigreturn(cpu_env);

    case TARGET_NR_rt_sigreturn:
        if (block_signals()) {
            ret = -TARGET_ERESTARTSYS;
        } else {
            ret = do_rt_sigreturn(cpu_env);
    case TARGET_NR_sethostname:
        if (!(p = lock_user_string(arg1)))
            goto efault;
        ret = get_errno(sethostname(p, arg2));
        unlock_user(p, arg1, 0);
    case TARGET_NR_setrlimit:
        {
            int resource = target_to_host_resource(arg1);
            struct target_rlimit *target_rlim;
            struct rlimit rlim;
            if (!lock_user_struct(VERIFY_READ, target_rlim, arg2, 1))
                goto efault;
            rlim.rlim_cur = target_to_host_rlim(target_rlim->rlim_cur);
            rlim.rlim_max = target_to_host_rlim(target_rlim->rlim_max);
            unlock_user_struct(target_rlim, arg2, 0);
            ret = get_errno(setrlimit(resource, &rlim));
    case TARGET_NR_getrlimit:
        {
            int resource = target_to_host_resource(arg1);
            struct target_rlimit *target_rlim;
            struct rlimit rlim;
            ret = get_errno(getrlimit(resource, &rlim));
            if (!is_error(ret)) {
                if (!lock_user_struct(VERIFY_WRITE, target_rlim, arg2, 0))
                    goto efault;
                target_rlim->rlim_cur = host_to_target_rlim(rlim.rlim_cur);
                target_rlim->rlim_max = host_to_target_rlim(rlim.rlim_max);
                unlock_user_struct(target_rlim, arg2, 1);
    case TARGET_NR_getrusage:
        {
            struct rusage rusage;
            ret = get_errno(getrusage(arg1, &rusage));
            if (!is_error(ret)) {
                ret = host_to_target_rusage(arg2, &rusage);
    case TARGET_NR_gettimeofday:
        {
            struct timeval tv;
            ret = get_errno(gettimeofday(&tv, NULL));
            if (!is_error(ret)) {
                if (copy_to_user_timeval(arg1, &tv))
                    goto efault;
    case TARGET_NR_settimeofday:
        {
            struct timeval tv, *ptv = NULL;
            struct timezone tz, *ptz = NULL;
            if (arg1) {
                if (copy_from_user_timeval(&tv, arg1)) {
                    goto efault;
                ptv = &tv;
            if (arg2) {
                if (copy_from_user_timezone(&tz, arg2)) {
                    goto efault;
                ptz = &tz;
            ret = get_errno(settimeofday(ptv, ptz));

    case TARGET_NR_select:

        ret = do_select(arg1, arg2, arg3, arg4, arg5);

        {
            struct target_sel_arg_struct *sel;
            abi_ulong inp, outp, exp, tvp;
            long nsel;
            if (!lock_user_struct(VERIFY_READ, sel, arg1, 1))
                goto efault;
            nsel = tswapal(sel->n);
            inp = tswapal(sel->inp);
            outp = tswapal(sel->outp);
            exp = tswapal(sel->exp);
            tvp = tswapal(sel->tvp);
            unlock_user_struct(sel, arg1, 0);
            ret = do_select(nsel, inp, outp, exp, tvp);



    case TARGET_NR_pselect6:
        {
            abi_long rfd_addr, wfd_addr, efd_addr, n, ts_addr;
            fd_set rfds, wfds, efds;
            fd_set *rfds_ptr, *wfds_ptr, *efds_ptr;
            struct timespec ts, *ts_ptr;
             
            sigset_t set;
            struct {
                sigset_t *set;
                size_t size;
            } sig, *sig_ptr;
            abi_ulong arg_sigset, arg_sigsize, *arg7;
            target_sigset_t *target_sigset;
            n = arg1;
            rfd_addr = arg2;
            wfd_addr = arg3;
            efd_addr = arg4;
            ts_addr = arg5;
            ret = copy_from_user_fdset_ptr(&rfds, &rfds_ptr, rfd_addr, n);
            if (ret) {
                goto fail;
            ret = copy_from_user_fdset_ptr(&wfds, &wfds_ptr, wfd_addr, n);
            if (ret) {
                goto fail;
            ret = copy_from_user_fdset_ptr(&efds, &efds_ptr, efd_addr, n);
            if (ret) {
                goto fail;
             
            if (ts_addr) {
                if (target_to_host_timespec(&ts, ts_addr)) {
                    goto efault;
                ts_ptr = &ts;
            } else {
                ts_ptr = NULL;
             
            if (arg6) {
                sig_ptr = &sig;
                sig.size = SIGSET_T_SIZE;
                arg7 = lock_user(VERIFY_READ, arg6, sizeof(*arg7) * 2, 1);
                if (!arg7) {
                    goto efault;
                arg_sigset = tswapal(arg7[0]);
                arg_sigsize = tswapal(arg7[1]);
                unlock_user(arg7, arg6, 0);
                if (arg_sigset) {
                    sig.set = &set;
                    if (arg_sigsize != sizeof(*target_sigset)) {
                         
                        goto fail;
                    target_sigset = lock_user(VERIFY_READ, arg_sigset,
                                              sizeof(*target_sigset), 1);
                    if (!target_sigset) {
                        goto efault;
                    target_to_host_sigset(&set, target_sigset);
                    unlock_user(target_sigset, arg_sigset, 0);
                } else {
                    sig.set = NULL;
            } else {
                sig_ptr = NULL;
            ret = get_errno(safe_pselect6(n, rfds_ptr, wfds_ptr, efds_ptr,
                                          ts_ptr, sig_ptr));
            if (!is_error(ret)) {
                if (rfd_addr && copy_to_user_fdset(rfd_addr, &rfds, n))
                    goto efault;
                if (wfd_addr && copy_to_user_fdset(wfd_addr, &wfds, n))
                    goto efault;
                if (efd_addr && copy_to_user_fdset(efd_addr, &efds, n))
                    goto efault;
                if (ts_addr && host_to_target_timespec(ts_addr, &ts))
                    goto efault;


    case TARGET_NR_symlink:
        {
            void *p2;
            p = lock_user_string(arg1);
            p2 = lock_user_string(arg2);
            if (!p || !p2)
                ret = -TARGET_EFAULT;
            else
                ret = get_errno(symlink(p, p2));
            unlock_user(p2, arg2, 0);
            unlock_user(p, arg1, 0);


    case TARGET_NR_symlinkat:
        {
            void *p2;
            p  = lock_user_string(arg1);
            p2 = lock_user_string(arg3);
            if (!p || !p2)
                ret = -TARGET_EFAULT;
            else
                ret = get_errno(symlinkat(p, arg2, p2));
            unlock_user(p2, arg3, 0);
            unlock_user(p, arg1, 0);


    case TARGET_NR_oldlstat:
        goto unimplemented;


    case TARGET_NR_readlink:
        {
            void *p2;
            p = lock_user_string(arg1);
            p2 = lock_user(VERIFY_WRITE, arg2, arg3, 0);
            if (!p || !p2) {
                ret = -TARGET_EFAULT;
            } else if (!arg3) {
                 
            } else if (is_proc_myself((const char *)p, "exe")) {
                char real[PATH_MAX], *temp;
                temp = realpath(exec_path, real);
                 
                if (temp == NULL) {
                    ret = get_errno(-1);
                } else {
                     
                    ret = MIN(strlen(real), arg3);
                     
                    memcpy(p2, real, ret);
            } else {
                ret = get_errno(readlink(path(p), p2, arg3));
            unlock_user(p2, arg2, ret);
            unlock_user(p, arg1, 0);


    case TARGET_NR_readlinkat:
        {
            void *p2;
            p  = lock_user_string(arg2);
            p2 = lock_user(VERIFY_WRITE, arg3, arg4, 0);
            if (!p || !p2) {
                ret = -TARGET_EFAULT;
            } else if (is_proc_myself((const char *)p, "exe")) {
                char real[PATH_MAX], *temp;
                temp = realpath(exec_path, real);
                ret = temp == NULL ? get_errno(-1) : strlen(real) ;
                snprintf((char *)p2, arg4, "%s", real);
            } else {
                ret = get_errno(readlinkat(arg1, path(p), p2, arg4));
            unlock_user(p2, arg3, ret);
            unlock_user(p, arg2, 0);


    case TARGET_NR_uselib:
        goto unimplemented;


    case TARGET_NR_swapon:
        if (!(p = lock_user_string(arg1)))
            goto efault;
        ret = get_errno(swapon(p, arg2));
        unlock_user(p, arg1, 0);

    case TARGET_NR_reboot:
        if (arg3 == LINUX_REBOOT_CMD_RESTART2) {
            
           p = lock_user_string(arg4);
           if (!p) {
              goto efault;
           ret = get_errno(reboot(arg1, arg2, arg3, p));
           unlock_user(p, arg4, 0);
        } else {
           ret = get_errno(reboot(arg1, arg2, arg3, NULL));

    case TARGET_NR_readdir:
        goto unimplemented;


    case TARGET_NR_mmap:

    (defined(TARGET_ARM) && defined(TARGET_ABI32)) || \
    defined(TARGET_M68K) || defined(TARGET_CRIS) || defined(TARGET_MICROBLAZE) \
    || defined(TARGET_S390X)
        {
            abi_ulong *v;
            abi_ulong v1, v2, v3, v4, v5, v6;
            if (!(v = lock_user(VERIFY_READ, arg1, 6 * sizeof(abi_ulong), 1)))
                goto efault;
            v1 = tswapal(v[0]);
            v2 = tswapal(v[1]);
            v3 = tswapal(v[2]);
            v4 = tswapal(v[3]);
            v5 = tswapal(v[4]);
            v6 = tswapal(v[5]);
            unlock_user(v, arg1, 0);
            ret = get_errno(target_mmap(v1, v2, v3,
                                        target_to_host_bitmask(v4, mmap_flags_tbl),
                                        v5, v6));

        ret = get_errno(target_mmap(arg1, arg2, arg3,
                                    target_to_host_bitmask(arg4, mmap_flags_tbl),
                                    arg5,
                                    arg6));



    case TARGET_NR_mmap2:



        ret = get_errno(target_mmap(arg1, arg2, arg3,
                                    target_to_host_bitmask(arg4, mmap_flags_tbl),
                                    arg5,
                                    arg6 << MMAP_SHIFT));

    case TARGET_NR_munmap:
        ret = get_errno(target_munmap(arg1, arg2));
    case TARGET_NR_mprotect:
        {
            TaskState *ts = cpu->opaque;
             
            if ((arg3 & PROT_GROWSDOWN)
                && arg1 >= ts->info->stack_limit
                && arg1 <= ts->info->start_stack) {
                arg3 &= ~PROT_GROWSDOWN;
                arg2 = arg2 + arg1 - ts->info->stack_limit;
                arg1 = ts->info->stack_limit;
        ret = get_errno(target_mprotect(arg1, arg2, arg3));

    case TARGET_NR_mremap:
        ret = get_errno(target_mremap(arg1, arg2, arg3, arg4, arg5));


    case TARGET_NR_msync:
        ret = get_errno(msync(g2h(arg1), arg2, arg3));


    case TARGET_NR_mlock:
        ret = get_errno(mlock(g2h(arg1), arg2));


    case TARGET_NR_munlock:
        ret = get_errno(munlock(g2h(arg1), arg2));


    case TARGET_NR_mlockall:
        ret = get_errno(mlockall(target_to_host_mlockall_arg(arg1)));


    case TARGET_NR_munlockall:
        ret = get_errno(munlockall());

    case TARGET_NR_truncate:
        if (!(p = lock_user_string(arg1)))
            goto efault;
        ret = get_errno(truncate(p, arg2));
        unlock_user(p, arg1, 0);
    case TARGET_NR_ftruncate:
        ret = get_errno(ftruncate(arg1, arg2));
    case TARGET_NR_fchmod:
        ret = get_errno(fchmod(arg1, arg2));

    case TARGET_NR_fchmodat:
        if (!(p = lock_user_string(arg2)))
            goto efault;
        ret = get_errno(fchmodat(arg1, p, arg3, 0));
        unlock_user(p, arg2, 0);

    case TARGET_NR_getpriority:
         
        errno = 0;
        ret = getpriority(arg1, arg2);
        if (ret == -1 && errno != 0) {
            ret = -host_to_target_errno(errno);

         
        ((CPUAlphaState *)cpu_env)->ir[IR_V0] = 0;

         
        ret = 20 - ret;

    case TARGET_NR_setpriority:
        ret = get_errno(setpriority(arg1, arg2, arg3));

    case TARGET_NR_profil:
        goto unimplemented;

    case TARGET_NR_statfs:
        if (!(p = lock_user_string(arg1)))
            goto efault;
        ret = get_errno(statfs(path(p), &stfs));
        unlock_user(p, arg1, 0);
    convert_statfs:
        if (!is_error(ret)) {
            struct target_statfs *target_stfs;
            if (!lock_user_struct(VERIFY_WRITE, target_stfs, arg2, 0))
                goto efault;
            __put_user(stfs.f_type, &target_stfs->f_type);
            __put_user(stfs.f_bsize, &target_stfs->f_bsize);
            __put_user(stfs.f_blocks, &target_stfs->f_blocks);
            __put_user(stfs.f_bfree, &target_stfs->f_bfree);
            __put_user(stfs.f_bavail, &target_stfs->f_bavail);
            __put_user(stfs.f_files, &target_stfs->f_files);
            __put_user(stfs.f_ffree, &target_stfs->f_ffree);
            __put_user(stfs.f_fsid.__val[0], &target_stfs->f_fsid.val[0]);
            __put_user(stfs.f_fsid.__val[1], &target_stfs->f_fsid.val[1]);
            __put_user(stfs.f_namelen, &target_stfs->f_namelen);
            __put_user(stfs.f_frsize, &target_stfs->f_frsize);
            memset(target_stfs->f_spare, 0, sizeof(target_stfs->f_spare));
            unlock_user_struct(target_stfs, arg2, 1);
    case TARGET_NR_fstatfs:
        ret = get_errno(fstatfs(arg1, &stfs));
        goto convert_statfs;

    case TARGET_NR_statfs64:
        if (!(p = lock_user_string(arg1)))
            goto efault;
        ret = get_errno(statfs(path(p), &stfs));
        unlock_user(p, arg1, 0);
    convert_statfs64:
        if (!is_error(ret)) {
            struct target_statfs64 *target_stfs;
            if (!lock_user_struct(VERIFY_WRITE, target_stfs, arg3, 0))
                goto efault;
            __put_user(stfs.f_type, &target_stfs->f_type);
            __put_user(stfs.f_bsize, &target_stfs->f_bsize);
            __put_user(stfs.f_blocks, &target_stfs->f_blocks);
            __put_user(stfs.f_bfree, &target_stfs->f_bfree);
            __put_user(stfs.f_bavail, &target_stfs->f_bavail);
            __put_user(stfs.f_files, &target_stfs->f_files);
            __put_user(stfs.f_ffree, &target_stfs->f_ffree);
            __put_user(stfs.f_fsid.__val[0], &target_stfs->f_fsid.val[0]);
            __put_user(stfs.f_fsid.__val[1], &target_stfs->f_fsid.val[1]);
            __put_user(stfs.f_namelen, &target_stfs->f_namelen);
            __put_user(stfs.f_frsize, &target_stfs->f_frsize);
            memset(target_stfs->f_spare, 0, sizeof(target_stfs->f_spare));
            unlock_user_struct(target_stfs, arg3, 1);
    case TARGET_NR_fstatfs64:
        ret = get_errno(fstatfs(arg1, &stfs));
        goto convert_statfs64;


    case TARGET_NR_ioperm:
        goto unimplemented;


    case TARGET_NR_socketcall:
        ret = do_socketcall(arg1, arg2);


    case TARGET_NR_accept:
        ret = do_accept4(arg1, arg2, arg3, 0);


    case TARGET_NR_accept4:
        ret = do_accept4(arg1, arg2, arg3, arg4);


    case TARGET_NR_bind:
        ret = do_bind(arg1, arg2, arg3);


    case TARGET_NR_connect:
        ret = do_connect(arg1, arg2, arg3);


    case TARGET_NR_getpeername:
        ret = do_getpeername(arg1, arg2, arg3);


    case TARGET_NR_getsockname:
        ret = do_getsockname(arg1, arg2, arg3);


    case TARGET_NR_getsockopt:
        ret = do_getsockopt(arg1, arg2, arg3, arg4, arg5);


    case TARGET_NR_listen:
        ret = get_errno(listen(arg1, arg2));


    case TARGET_NR_recv:
        ret = do_recvfrom(arg1, arg2, arg3, arg4, 0, 0);


    case TARGET_NR_recvfrom:
        ret = do_recvfrom(arg1, arg2, arg3, arg4, arg5, arg6);


    case TARGET_NR_recvmsg:
        ret = do_sendrecvmsg(arg1, arg2, arg3, 0);


    case TARGET_NR_send:
        ret = do_sendto(arg1, arg2, arg3, arg4, 0, 0);


    case TARGET_NR_sendmsg:
        ret = do_sendrecvmsg(arg1, arg2, arg3, 1);


    case TARGET_NR_sendmmsg:
        ret = do_sendrecvmmsg(arg1, arg2, arg3, arg4, 1);
    case TARGET_NR_recvmmsg:
        ret = do_sendrecvmmsg(arg1, arg2, arg3, arg4, 0);


    case TARGET_NR_sendto:
        ret = do_sendto(arg1, arg2, arg3, arg4, arg5, arg6);


    case TARGET_NR_shutdown:
        ret = get_errno(shutdown(arg1, arg2));


    case TARGET_NR_getrandom:
        p = lock_user(VERIFY_WRITE, arg1, arg2, 0);
        if (!p) {
            goto efault;
        ret = get_errno(getrandom(p, arg2, arg3));
        unlock_user(p, arg1, ret);


    case TARGET_NR_socket:
        ret = do_socket(arg1, arg2, arg3);
        fd_trans_unregister(ret);


    case TARGET_NR_socketpair:
        ret = do_socketpair(arg1, arg2, arg3, arg4);


    case TARGET_NR_setsockopt:
        ret = do_setsockopt(arg1, arg2, arg3, arg4, (socklen_t) arg5);

    case TARGET_NR_syslog:
        if (!(p = lock_user_string(arg2)))
            goto efault;
        ret = get_errno(sys_syslog((int)arg1, p, (int)arg3));
        unlock_user(p, arg2, 0);
    case TARGET_NR_setitimer:
        {
            struct itimerval value, ovalue, *pvalue;
            if (arg2) {
                pvalue = &value;
                if (copy_from_user_timeval(&pvalue->it_interval, arg2)
                    || copy_from_user_timeval(&pvalue->it_value,
                                              arg2 + sizeof(struct target_timeval)))
                    goto efault;
            } else {
                pvalue = NULL;
            ret = get_errno(setitimer(arg1, pvalue, &ovalue));
            if (!is_error(ret) && arg3) {
                if (copy_to_user_timeval(arg3,
                                         &ovalue.it_interval)
                    || copy_to_user_timeval(arg3 + sizeof(struct target_timeval),
                                            &ovalue.it_value))
                    goto efault;
    case TARGET_NR_getitimer:
        {
            struct itimerval value;
            ret = get_errno(getitimer(arg1, &value));
            if (!is_error(ret) && arg2) {
                if (copy_to_user_timeval(arg2,
                                         &value.it_interval)
                    || copy_to_user_timeval(arg2 + sizeof(struct target_timeval),
                                            &value.it_value))
                    goto efault;

    case TARGET_NR_stat:
        if (!(p = lock_user_string(arg1)))
            goto efault;
        ret = get_errno(stat(path(p), &st));
        unlock_user(p, arg1, 0);
        goto do_stat;


    case TARGET_NR_lstat:
        if (!(p = lock_user_string(arg1)))
            goto efault;
        ret = get_errno(lstat(path(p), &st));
        unlock_user(p, arg1, 0);
        goto do_stat;

    case TARGET_NR_fstat:
        {
            ret = get_errno(fstat(arg1, &st));

        do_stat:

            if (!is_error(ret)) {
                struct target_stat *target_st;
                if (!lock_user_struct(VERIFY_WRITE, target_st, arg2, 0))
                    goto efault;
                memset(target_st, 0, sizeof(*target_st));
                __put_user(st.st_dev, &target_st->st_dev);
                __put_user(st.st_ino, &target_st->st_ino);
                __put_user(st.st_mode, &target_st->st_mode);
                __put_user(st.st_uid, &target_st->st_uid);
                __put_user(st.st_gid, &target_st->st_gid);
                __put_user(st.st_nlink, &target_st->st_nlink);
                __put_user(st.st_rdev, &target_st->st_rdev);
                __put_user(st.st_size, &target_st->st_size);
                __put_user(st.st_blksize, &target_st->st_blksize);
                __put_user(st.st_blocks, &target_st->st_blocks);
                __put_user(st.st_atime, &target_st->target_st_atime);
                __put_user(st.st_mtime, &target_st->target_st_mtime);
                __put_user(st.st_ctime, &target_st->target_st_ctime);
                unlock_user_struct(target_st, arg2, 1);

    case TARGET_NR_olduname:
        goto unimplemented;


    case TARGET_NR_iopl:
        goto unimplemented;

    case TARGET_NR_vhangup:
        ret = get_errno(vhangup());

    case TARGET_NR_idle:
        goto unimplemented;


    case TARGET_NR_syscall:
        ret = do_syscall(cpu_env, arg1 & 0xffff, arg2, arg3, arg4, arg5,
                         arg6, arg7, arg8, 0);

    case TARGET_NR_wait4:
        {
            int status;
            abi_long status_ptr = arg2;
            struct rusage rusage, *rusage_ptr;
            abi_ulong target_rusage = arg4;
            abi_long rusage_err;
            if (target_rusage)
                rusage_ptr = &rusage;
            else
                rusage_ptr = NULL;
            ret = get_errno(safe_wait4(arg1, &status, arg3, rusage_ptr));
            if (!is_error(ret)) {
                if (status_ptr && ret) {
                    status = host_to_target_waitstatus(status);
                    if (put_user_s32(status, status_ptr))
                        goto efault;
                if (target_rusage) {
                    rusage_err = host_to_target_rusage(target_rusage, &rusage);
                    if (rusage_err) {
                        ret = rusage_err;

    case TARGET_NR_swapoff:
        if (!(p = lock_user_string(arg1)))
            goto efault;
        ret = get_errno(swapoff(p));
        unlock_user(p, arg1, 0);

    case TARGET_NR_sysinfo:
        {
            struct target_sysinfo *target_value;
            struct sysinfo value;
            ret = get_errno(sysinfo(&value));
            if (!is_error(ret) && arg1)
            {
                if (!lock_user_struct(VERIFY_WRITE, target_value, arg1, 0))
                    goto efault;
                __put_user(value.uptime, &target_value->uptime);
                __put_user(value.loads[0], &target_value->loads[0]);
                __put_user(value.loads[1], &target_value->loads[1]);
                __put_user(value.loads[2], &target_value->loads[2]);
                __put_user(value.totalram, &target_value->totalram);
                __put_user(value.freeram, &target_value->freeram);
                __put_user(value.sharedram, &target_value->sharedram);
                __put_user(value.bufferram, &target_value->bufferram);
                __put_user(value.totalswap, &target_value->totalswap);
                __put_user(value.freeswap, &target_value->freeswap);
                __put_user(value.procs, &target_value->procs);
                __put_user(value.totalhigh, &target_value->totalhigh);
                __put_user(value.freehigh, &target_value->freehigh);
                __put_user(value.mem_unit, &target_value->mem_unit);
                unlock_user_struct(target_value, arg1, 1);

    case TARGET_NR_ipc:
	ret = do_ipc(arg1, arg2, arg3, arg4, arg5, arg6);


    case TARGET_NR_semget:
        ret = get_errno(semget(arg1, arg2, arg3));


    case TARGET_NR_semop:
        ret = do_semop(arg1, arg2, arg3);


    case TARGET_NR_semctl:
        ret = do_semctl(arg1, arg2, arg3, arg4);


    case TARGET_NR_msgctl:
        ret = do_msgctl(arg1, arg2, arg3);


    case TARGET_NR_msgget:
        ret = get_errno(msgget(arg1, arg2));


    case TARGET_NR_msgrcv:
        ret = do_msgrcv(arg1, arg2, arg3, arg4, arg5);


    case TARGET_NR_msgsnd:
        ret = do_msgsnd(arg1, arg2, arg3, arg4);


    case TARGET_NR_shmget:
        ret = get_errno(shmget(arg1, arg2, arg3));


    case TARGET_NR_shmctl:
        ret = do_shmctl(arg1, arg2, arg3);


    case TARGET_NR_shmat:
        ret = do_shmat(arg1, arg2, arg3);


    case TARGET_NR_shmdt:
        ret = do_shmdt(arg1);

    case TARGET_NR_fsync:
        ret = get_errno(fsync(arg1));
    case TARGET_NR_clone:

        ret = get_errno(do_fork(cpu_env, arg1, arg2, arg4, arg6, arg5));

        ret = get_errno(do_fork(cpu_env, arg1, arg2, arg3, arg4, arg5));

        ret = get_errno(do_fork(cpu_env, arg2, arg1, arg3, arg5, arg4));

        ret = get_errno(do_fork(cpu_env, arg1, arg2, arg3, arg5, arg4));


         
    case TARGET_NR_exit_group:

        _mcleanup();

        gdb_exit(cpu_env, arg1);
        ret = get_errno(exit_group(arg1));

    case TARGET_NR_setdomainname:
        if (!(p = lock_user_string(arg1)))
            goto efault;
        ret = get_errno(setdomainname(p, arg2));
        unlock_user(p, arg1, 0);
    case TARGET_NR_uname:
         
        {
            struct new_utsname * buf;
            if (!lock_user_struct(VERIFY_WRITE, buf, arg1, 0))
                goto efault;
            ret = get_errno(sys_uname(buf));
            if (!is_error(ret)) {
                 
                strcpy (buf->machine, cpu_to_uname_machine(cpu_env));
                 
                if (qemu_uname_release && *qemu_uname_release) {
                    g_strlcpy(buf->release, qemu_uname_release,
                              sizeof(buf->release));
            unlock_user_struct(buf, arg1, 1);

    case TARGET_NR_modify_ldt:
        ret = do_modify_ldt(cpu_env, arg1, arg2, arg3);

    case TARGET_NR_vm86old:
        goto unimplemented;
    case TARGET_NR_vm86:
        ret = do_vm86(cpu_env, arg1, arg2);


    case TARGET_NR_adjtimex:
        goto unimplemented;

    case TARGET_NR_create_module:

    case TARGET_NR_init_module:
    case TARGET_NR_delete_module:

    case TARGET_NR_get_kernel_syms:

        goto unimplemented;
    case TARGET_NR_quotactl:
        goto unimplemented;
    case TARGET_NR_getpgid:
        ret = get_errno(getpgid(arg1));
    case TARGET_NR_fchdir:
        ret = get_errno(fchdir(arg1));

    case TARGET_NR_bdflush:
        goto unimplemented;


    case TARGET_NR_sysfs:
        goto unimplemented;

    case TARGET_NR_personality:
        ret = get_errno(personality(arg1));

    case TARGET_NR_afs_syscall:
        goto unimplemented;


    case TARGET_NR__llseek:
        {
            int64_t res;

            res = lseek(arg1, ((uint64_t)arg2 << 32) | (abi_ulong)arg3, arg5);
            if (res == -1) {
                ret = get_errno(res);
            } else {
                ret = 0;

            ret = get_errno(_llseek(arg1, arg2, arg3, &res, arg5));

            if ((ret == 0) && put_user_s64(res, arg4)) {
                goto efault;


    case TARGET_NR_getdents:


        {
            struct target_dirent *target_dirp;
            struct linux_dirent *dirp;
            abi_long count = arg3;
            dirp = g_try_malloc(count);
            if (!dirp) {
                ret = -TARGET_ENOMEM;
                goto fail;
            ret = get_errno(sys_getdents(arg1, dirp, count));
            if (!is_error(ret)) {
                struct linux_dirent *de;
		struct target_dirent *tde;
                int len = ret;
                int reclen, treclen;
		int count1, tnamelen;
		count1 = 0;
                de = dirp;
                if (!(target_dirp = lock_user(VERIFY_WRITE, arg2, count, 0)))
                    goto efault;
		tde = target_dirp;
                while (len > 0) {
                    reclen = de->d_reclen;
                    tnamelen = reclen - offsetof(struct linux_dirent, d_name);
                    assert(tnamelen >= 0);
                    treclen = tnamelen + offsetof(struct target_dirent, d_name);
                    assert(count1 + treclen <= count);
                    tde->d_reclen = tswap16(treclen);
                    tde->d_ino = tswapal(de->d_ino);
                    tde->d_off = tswapal(de->d_off);
                    memcpy(tde->d_name, de->d_name, tnamelen);
                    de = (struct linux_dirent *)((char *)de + reclen);
                    len -= reclen;
                    tde = (struct target_dirent *)((char *)tde + treclen);
		    count1 += treclen;
		ret = count1;
                unlock_user(target_dirp, arg2, ret);
            g_free(dirp);

        {
            struct linux_dirent *dirp;
            abi_long count = arg3;
            if (!(dirp = lock_user(VERIFY_WRITE, arg2, count, 0)))
                goto efault;
            ret = get_errno(sys_getdents(arg1, dirp, count));
            if (!is_error(ret)) {
                struct linux_dirent *de;
                int len = ret;
                int reclen;
                de = dirp;
                while (len > 0) {
                    reclen = de->d_reclen;
                    if (reclen > len)
                    de->d_reclen = tswap16(reclen);
                    tswapls(&de->d_ino);
                    tswapls(&de->d_off);
                    de = (struct linux_dirent *)((char *)de + reclen);
                    len -= reclen;
            unlock_user(dirp, arg2, ret);


         
        {
            struct linux_dirent64 *dirp;
            abi_long count = arg3;
            dirp = lock_user(VERIFY_WRITE, arg2, count, 0);
            if (!dirp) {
                goto efault;
            ret = get_errno(sys_getdents64(arg1, dirp, count));
            if (!is_error(ret)) {
                 
                struct linux_dirent64 *de;
                struct target_dirent *tde;
                int len = ret;
                int tlen = 0;
                de = dirp;
                tde = (struct target_dirent *)dirp;
                while (len > 0) {
                    int namelen, treclen;
                    int reclen = de->d_reclen;
                    uint64_t ino = de->d_ino;
                    int64_t off = de->d_off;
                    uint8_t type = de->d_type;
                    namelen = strlen(de->d_name);
                    treclen = offsetof(struct target_dirent, d_name)
                        + namelen + 2;
                    treclen = QEMU_ALIGN_UP(treclen, sizeof(abi_long));
                    memmove(tde->d_name, de->d_name, namelen + 1);
                    tde->d_ino = tswapal(ino);
                    tde->d_off = tswapal(off);
                    tde->d_reclen = tswap16(treclen);
                     
                    *(((char *)tde) + treclen - 1) = type;
                    de = (struct linux_dirent64 *)((char *)de + reclen);
                    tde = (struct target_dirent *)((char *)tde + treclen);
                    len -= reclen;
                    tlen += treclen;
                ret = tlen;
            unlock_user(dirp, arg2, ret);



    case TARGET_NR_getdents64:
        {
            struct linux_dirent64 *dirp;
            abi_long count = arg3;
            if (!(dirp = lock_user(VERIFY_WRITE, arg2, count, 0)))
                goto efault;
            ret = get_errno(sys_getdents64(arg1, dirp, count));
            if (!is_error(ret)) {
                struct linux_dirent64 *de;
                int len = ret;
                int reclen;
                de = dirp;
                while (len > 0) {
                    reclen = de->d_reclen;
                    if (reclen > len)
                    de->d_reclen = tswap16(reclen);
                    tswap64s((uint64_t *)&de->d_ino);
                    tswap64s((uint64_t *)&de->d_off);
                    de = (struct linux_dirent64 *)((char *)de + reclen);
                    len -= reclen;
            unlock_user(dirp, arg2, ret);


    case TARGET_NR__newselect:
        ret = do_select(arg1, arg2, arg3, arg4, arg5);



    case TARGET_NR_poll:


    case TARGET_NR_ppoll:

        {
            struct target_pollfd *target_pfd;
            unsigned int nfds = arg2;
            struct pollfd *pfd;
            unsigned int i;
            pfd = NULL;
            target_pfd = NULL;
            if (nfds) {
                target_pfd = lock_user(VERIFY_WRITE, arg1,
                                       sizeof(struct target_pollfd) * nfds, 1);
                if (!target_pfd) {
                    goto efault;
                pfd = alloca(sizeof(struct pollfd) * nfds);
                for (i = 0; i < nfds; i++) {
                    pfd[i].fd = tswap32(target_pfd[i].fd);
                    pfd[i].events = tswap16(target_pfd[i].events);
            switch (num) {

            case TARGET_NR_ppoll:
            {
                struct timespec _timeout_ts, *timeout_ts = &_timeout_ts;
                target_sigset_t *target_set;
                sigset_t _set, *set = &_set;
                if (arg3) {
                    if (target_to_host_timespec(timeout_ts, arg3)) {
                        unlock_user(target_pfd, arg1, 0);
                        goto efault;
                } else {
                    timeout_ts = NULL;
                if (arg4) {
                    if (arg5 != sizeof(target_sigset_t)) {
                        unlock_user(target_pfd, arg1, 0);
                    target_set = lock_user(VERIFY_READ, arg4, sizeof(target_sigset_t), 1);
                    if (!target_set) {
                        unlock_user(target_pfd, arg1, 0);
                        goto efault;
                    target_to_host_sigset(set, target_set);
                } else {
                    set = NULL;
                ret = get_errno(safe_ppoll(pfd, nfds, timeout_ts,
                                           set, SIGSET_T_SIZE));
                if (!is_error(ret) && arg3) {
                    host_to_target_timespec(arg3, timeout_ts);
                if (arg4) {
                    unlock_user(target_set, arg4, 0);


            case TARGET_NR_poll:
            {
                struct timespec ts, *pts;
                if (arg3 >= 0) {
                     
                    ts.tv_sec = arg3 / 1000;
                    ts.tv_nsec = (arg3 % 1000) * 1000000LL;
                    pts = &ts;
                } else {
                     
                    pts = NULL;
                ret = get_errno(safe_ppoll(pfd, nfds, pts, NULL, 0));

            default:
                g_assert_not_reached();
            if (!is_error(ret)) {
                for(i = 0; i < nfds; i++) {
                    target_pfd[i].revents = tswap16(pfd[i].revents);
            unlock_user(target_pfd, arg1, sizeof(struct target_pollfd) * nfds);

    case TARGET_NR_flock:
         
        ret = get_errno(safe_flock(arg1, arg2));
    case TARGET_NR_readv:
        {
            struct iovec *vec = lock_iovec(VERIFY_WRITE, arg2, arg3, 0);
            if (vec != NULL) {
                ret = get_errno(safe_readv(arg1, vec, arg3));
                unlock_iovec(vec, arg2, arg3, 1);
            } else {
                ret = -host_to_target_errno(errno);
    case TARGET_NR_writev:
        {
            struct iovec *vec = lock_iovec(VERIFY_READ, arg2, arg3, 1);
            if (vec != NULL) {
                ret = get_errno(safe_writev(arg1, vec, arg3));
                unlock_iovec(vec, arg2, arg3, 0);
            } else {
                ret = -host_to_target_errno(errno);
    case TARGET_NR_getsid:
        ret = get_errno(getsid(arg1));

    case TARGET_NR_fdatasync:
        ret = get_errno(fdatasync(arg1));


    case TARGET_NR__sysctl:
         
        ret = -TARGET_ENOTDIR;

    case TARGET_NR_sched_getaffinity:
        {
            unsigned int mask_size;
            unsigned long *mask;
             
            if (arg2 & (sizeof(abi_ulong) - 1)) {
            mask_size = (arg2 + (sizeof(*mask) - 1)) & ~(sizeof(*mask) - 1);
            mask = alloca(mask_size);
            ret = get_errno(sys_sched_getaffinity(arg1, mask_size, mask));
            if (!is_error(ret)) {
                if (ret > arg2) {
                     
                    int numcpus = sysconf(_SC_NPROCESSORS_CONF);
                    if (numcpus > arg2 * 8) {
                    ret = arg2;
                if (copy_to_user(arg3, mask, ret)) {
                    goto efault;
    case TARGET_NR_sched_setaffinity:
        {
            unsigned int mask_size;
            unsigned long *mask;
             
            if (arg2 & (sizeof(abi_ulong) - 1)) {
            mask_size = (arg2 + (sizeof(*mask) - 1)) & ~(sizeof(*mask) - 1);
            mask = alloca(mask_size);
            if (!lock_user_struct(VERIFY_READ, p, arg3, 1)) {
                goto efault;
            memcpy(mask, p, arg2);
            unlock_user_struct(p, arg2, 0);
            ret = get_errno(sys_sched_setaffinity(arg1, mask_size, mask));
    case TARGET_NR_sched_setparam:
        {
            struct sched_param *target_schp;
            struct sched_param schp;
            if (arg2 == 0) {
                return -TARGET_EINVAL;
            if (!lock_user_struct(VERIFY_READ, target_schp, arg2, 1))
                goto efault;
            schp.sched_priority = tswap32(target_schp->sched_priority);
            unlock_user_struct(target_schp, arg2, 0);
            ret = get_errno(sched_setparam(arg1, &schp));
    case TARGET_NR_sched_getparam:
        {
            struct sched_param *target_schp;
            struct sched_param schp;
            if (arg2 == 0) {
                return -TARGET_EINVAL;
            ret = get_errno(sched_getparam(arg1, &schp));
            if (!is_error(ret)) {
                if (!lock_user_struct(VERIFY_WRITE, target_schp, arg2, 0))
                    goto efault;
                target_schp->sched_priority = tswap32(schp.sched_priority);
                unlock_user_struct(target_schp, arg2, 1);
    case TARGET_NR_sched_setscheduler:
        {
            struct sched_param *target_schp;
            struct sched_param schp;
            if (arg3 == 0) {
                return -TARGET_EINVAL;
            if (!lock_user_struct(VERIFY_READ, target_schp, arg3, 1))
                goto efault;
            schp.sched_priority = tswap32(target_schp->sched_priority);
            unlock_user_struct(target_schp, arg3, 0);
            ret = get_errno(sched_setscheduler(arg1, arg2, &schp));
    case TARGET_NR_sched_getscheduler:
        ret = get_errno(sched_getscheduler(arg1));
    case TARGET_NR_sched_yield:
        ret = get_errno(sched_yield());
    case TARGET_NR_sched_get_priority_max:
        ret = get_errno(sched_get_priority_max(arg1));
    case TARGET_NR_sched_get_priority_min:
        ret = get_errno(sched_get_priority_min(arg1));
    case TARGET_NR_sched_rr_get_interval:
        {
            struct timespec ts;
            ret = get_errno(sched_rr_get_interval(arg1, &ts));
            if (!is_error(ret)) {
                ret = host_to_target_timespec(arg2, &ts);
    case TARGET_NR_nanosleep:
        {
            struct timespec req, rem;
            target_to_host_timespec(&req, arg1);
            ret = get_errno(safe_nanosleep(&req, &rem));
            if (is_error(ret) && arg2) {
                host_to_target_timespec(arg2, &rem);

    case TARGET_NR_query_module:
        goto unimplemented;


    case TARGET_NR_nfsservctl:
        goto unimplemented;

    case TARGET_NR_prctl:
        switch (arg1) {
        case PR_GET_PDEATHSIG:
        {
            int deathsig;
            ret = get_errno(prctl(arg1, &deathsig, arg3, arg4, arg5));
            if (!is_error(ret) && arg2
                && put_user_ual(deathsig, arg2)) {
                goto efault;

        case PR_GET_NAME:
        {
            void *name = lock_user(VERIFY_WRITE, arg2, 16, 1);
            if (!name) {
                goto efault;
            ret = get_errno(prctl(arg1, (unsigned long)name,
                                  arg3, arg4, arg5));
            unlock_user(name, arg2, 16);
        case PR_SET_NAME:
        {
            void *name = lock_user(VERIFY_READ, arg2, 16, 1);
            if (!name) {
                goto efault;
            ret = get_errno(prctl(arg1, (unsigned long)name,
                                  arg3, arg4, arg5));
            unlock_user(name, arg2, 0);

        default:
             
            ret = get_errno(prctl(arg1, arg2, arg3, arg4, arg5));

    case TARGET_NR_arch_prctl:

        ret = do_arch_prctl(cpu_env, arg1, arg2);

        goto unimplemented;



    case TARGET_NR_pread64:
        if (regpairs_aligned(cpu_env)) {
            arg4 = arg5;
            arg5 = arg6;
        if (!(p = lock_user(VERIFY_WRITE, arg2, arg3, 0)))
            goto efault;
        ret = get_errno(pread64(arg1, p, arg3, target_offset64(arg4, arg5)));
        unlock_user(p, arg2, ret);
    case TARGET_NR_pwrite64:
        if (regpairs_aligned(cpu_env)) {
            arg4 = arg5;
            arg5 = arg6;
        if (!(p = lock_user(VERIFY_READ, arg2, arg3, 1)))
            goto efault;
        ret = get_errno(pwrite64(arg1, p, arg3, target_offset64(arg4, arg5)));
        unlock_user(p, arg2, 0);

    case TARGET_NR_getcwd:
        if (!(p = lock_user(VERIFY_WRITE, arg1, arg2, 0)))
            goto efault;
        ret = get_errno(sys_getcwd1(p, arg2));
        unlock_user(p, arg1, ret);
    case TARGET_NR_capget:
    case TARGET_NR_capset:
    {
        struct target_user_cap_header *target_header;
        struct target_user_cap_data *target_data = NULL;
        struct __user_cap_header_struct header;
        struct __user_cap_data_struct data[2];
        struct __user_cap_data_struct *dataptr = NULL;
        int i, target_datalen;
        int data_items = 1;
        if (!lock_user_struct(VERIFY_WRITE, target_header, arg1, 1)) {
            goto efault;
        header.version = tswap32(target_header->version);
        header.pid = tswap32(target_header->pid);
        if (header.version != _LINUX_CAPABILITY_VERSION) {
             
            data_items = 2;
        target_datalen = sizeof(*target_data) * data_items;
        if (arg2) {
            if (num == TARGET_NR_capget) {
                target_data = lock_user(VERIFY_WRITE, arg2, target_datalen, 0);
            } else {
                target_data = lock_user(VERIFY_READ, arg2, target_datalen, 1);
            if (!target_data) {
                unlock_user_struct(target_header, arg1, 0);
                goto efault;
            if (num == TARGET_NR_capset) {
                for (i = 0; i < data_items; i++) {
                    data[i].effective = tswap32(target_data[i].effective);
                    data[i].permitted = tswap32(target_data[i].permitted);
                    data[i].inheritable = tswap32(target_data[i].inheritable);
            dataptr = data;
        if (num == TARGET_NR_capget) {
            ret = get_errno(capget(&header, dataptr));
        } else {
            ret = get_errno(capset(&header, dataptr));
         
        target_header->version = tswap32(header.version);
        unlock_user_struct(target_header, arg1, 1);
        if (arg2) {
            if (num == TARGET_NR_capget) {
                for (i = 0; i < data_items; i++) {
                    target_data[i].effective = tswap32(data[i].effective);
                    target_data[i].permitted = tswap32(data[i].permitted);
                    target_data[i].inheritable = tswap32(data[i].inheritable);
                unlock_user(target_data, arg2, target_datalen);
            } else {
                unlock_user(target_data, arg2, 0);
    case TARGET_NR_sigaltstack:
        ret = do_sigaltstack(arg1, arg2, get_sp_from_cpustate((CPUArchState *)cpu_env));

    case TARGET_NR_sendfile:
    {
        off_t *offp = NULL;
        off_t off;
        if (arg3) {
            ret = get_user_sal(off, arg3);
            if (is_error(ret)) {
            offp = &off;
        ret = get_errno(sendfile(arg1, arg2, offp, arg4));
        if (!is_error(ret) && arg3) {
            abi_long ret2 = put_user_sal(off, arg3);
            if (is_error(ret2)) {
                ret = ret2;

    case TARGET_NR_sendfile64:
    {
        off_t *offp = NULL;
        off_t off;
        if (arg3) {
            ret = get_user_s64(off, arg3);
            if (is_error(ret)) {
            offp = &off;
        ret = get_errno(sendfile(arg1, arg2, offp, arg4));
        if (!is_error(ret) && arg3) {
            abi_long ret2 = put_user_s64(off, arg3);
            if (is_error(ret2)) {
                ret = ret2;


    case TARGET_NR_sendfile:

    case TARGET_NR_sendfile64:

        goto unimplemented;


    case TARGET_NR_getpmsg:
        goto unimplemented;


    case TARGET_NR_putpmsg:
        goto unimplemented;


    case TARGET_NR_vfork:
        ret = get_errno(do_fork(cpu_env, CLONE_VFORK | CLONE_VM | SIGCHLD,
                        0, 0, 0, 0));


    case TARGET_NR_ugetrlimit:
    {
	struct rlimit rlim;
	int resource = target_to_host_resource(arg1);
	ret = get_errno(getrlimit(resource, &rlim));
	if (!is_error(ret)) {
	    struct target_rlimit *target_rlim;
            if (!lock_user_struct(VERIFY_WRITE, target_rlim, arg2, 0))
                goto efault;
	    target_rlim->rlim_cur = host_to_target_rlim(rlim.rlim_cur);
	    target_rlim->rlim_max = host_to_target_rlim(rlim.rlim_max);
            unlock_user_struct(target_rlim, arg2, 1);


    case TARGET_NR_truncate64:
        if (!(p = lock_user_string(arg1)))
            goto efault;
	ret = target_truncate64(cpu_env, p, arg2, arg3, arg4);
        unlock_user(p, arg1, 0);


    case TARGET_NR_ftruncate64:
	ret = target_ftruncate64(cpu_env, arg1, arg2, arg3, arg4);


    case TARGET_NR_stat64:
        if (!(p = lock_user_string(arg1)))
            goto efault;
        ret = get_errno(stat(path(p), &st));
        unlock_user(p, arg1, 0);
        if (!is_error(ret))
            ret = host_to_target_stat64(cpu_env, arg2, &st);


    case TARGET_NR_lstat64:
        if (!(p = lock_user_string(arg1)))
            goto efault;
        ret = get_errno(lstat(path(p), &st));
        unlock_user(p, arg1, 0);
        if (!is_error(ret))
            ret = host_to_target_stat64(cpu_env, arg2, &st);


    case TARGET_NR_fstat64:
        ret = get_errno(fstat(arg1, &st));
        if (!is_error(ret))
            ret = host_to_target_stat64(cpu_env, arg2, &st);



    case TARGET_NR_fstatat64:


    case TARGET_NR_newfstatat:

        if (!(p = lock_user_string(arg2)))
            goto efault;
        ret = get_errno(fstatat(arg1, path(p), &st, arg4));
        if (!is_error(ret))
            ret = host_to_target_stat64(cpu_env, arg3, &st);


    case TARGET_NR_lchown:
        if (!(p = lock_user_string(arg1)))
            goto efault;
        ret = get_errno(lchown(p, low2highuid(arg2), low2highgid(arg3)));
        unlock_user(p, arg1, 0);


    case TARGET_NR_getuid:
        ret = get_errno(high2lowuid(getuid()));


    case TARGET_NR_getgid:
        ret = get_errno(high2lowgid(getgid()));


    case TARGET_NR_geteuid:
        ret = get_errno(high2lowuid(geteuid()));


    case TARGET_NR_getegid:
        ret = get_errno(high2lowgid(getegid()));

    case TARGET_NR_setreuid:
        ret = get_errno(setreuid(low2highuid(arg1), low2highuid(arg2)));
    case TARGET_NR_setregid:
        ret = get_errno(setregid(low2highgid(arg1), low2highgid(arg2)));
    case TARGET_NR_getgroups:
        {
            int gidsetsize = arg1;
            target_id *target_grouplist;
            gid_t *grouplist;
            int i;
            grouplist = alloca(gidsetsize * sizeof(gid_t));
            ret = get_errno(getgroups(gidsetsize, grouplist));
            if (gidsetsize == 0)
            if (!is_error(ret)) {
                target_grouplist = lock_user(VERIFY_WRITE, arg2, gidsetsize * sizeof(target_id), 0);
                if (!target_grouplist)
                    goto efault;
                for(i = 0;i < ret; i++)
                    target_grouplist[i] = tswapid(high2lowgid(grouplist[i]));
                unlock_user(target_grouplist, arg2, gidsetsize * sizeof(target_id));
    case TARGET_NR_setgroups:
        {
            int gidsetsize = arg1;
            target_id *target_grouplist;
            gid_t *grouplist = NULL;
            int i;
            if (gidsetsize) {
                grouplist = alloca(gidsetsize * sizeof(gid_t));
                target_grouplist = lock_user(VERIFY_READ, arg2, gidsetsize * sizeof(target_id), 1);
                if (!target_grouplist) {
                    ret = -TARGET_EFAULT;
                    goto fail;
                for (i = 0; i < gidsetsize; i++) {
                    grouplist[i] = low2highgid(tswapid(target_grouplist[i]));
                unlock_user(target_grouplist, arg2, 0);
            ret = get_errno(setgroups(gidsetsize, grouplist));
    case TARGET_NR_fchown:
        ret = get_errno(fchown(arg1, low2highuid(arg2), low2highgid(arg3)));

    case TARGET_NR_fchownat:
        if (!(p = lock_user_string(arg2))) 
            goto efault;
        ret = get_errno(fchownat(arg1, p, low2highuid(arg3),
                                 low2highgid(arg4), arg5));
        unlock_user(p, arg2, 0);


    case TARGET_NR_setresuid:
        ret = get_errno(sys_setresuid(low2highuid(arg1),
                                      low2highuid(arg2),
                                      low2highuid(arg3)));


    case TARGET_NR_getresuid:
        {
            uid_t ruid, euid, suid;
            ret = get_errno(getresuid(&ruid, &euid, &suid));
            if (!is_error(ret)) {
                if (put_user_id(high2lowuid(ruid), arg1)
                    || put_user_id(high2lowuid(euid), arg2)
                    || put_user_id(high2lowuid(suid), arg3))
                    goto efault;


    case TARGET_NR_setresgid:
        ret = get_errno(sys_setresgid(low2highgid(arg1),
                                      low2highgid(arg2),
                                      low2highgid(arg3)));


    case TARGET_NR_getresgid:
        {
            gid_t rgid, egid, sgid;
            ret = get_errno(getresgid(&rgid, &egid, &sgid));
            if (!is_error(ret)) {
                if (put_user_id(high2lowgid(rgid), arg1)
                    || put_user_id(high2lowgid(egid), arg2)
                    || put_user_id(high2lowgid(sgid), arg3))
                    goto efault;


    case TARGET_NR_chown:
        if (!(p = lock_user_string(arg1)))
            goto efault;
        ret = get_errno(chown(p, low2highuid(arg2), low2highgid(arg3)));
        unlock_user(p, arg1, 0);

    case TARGET_NR_setuid:
        ret = get_errno(sys_setuid(low2highuid(arg1)));
    case TARGET_NR_setgid:
        ret = get_errno(sys_setgid(low2highgid(arg1)));
    case TARGET_NR_setfsuid:
        ret = get_errno(setfsuid(arg1));
    case TARGET_NR_setfsgid:
        ret = get_errno(setfsgid(arg1));

    case TARGET_NR_lchown32:
        if (!(p = lock_user_string(arg1)))
            goto efault;
        ret = get_errno(lchown(p, arg2, arg3));
        unlock_user(p, arg1, 0);


    case TARGET_NR_getuid32:
        ret = get_errno(getuid());


    
    case TARGET_NR_getxuid:
         {
            uid_t euid;
            euid=geteuid();
            ((CPUAlphaState *)cpu_env)->ir[IR_A4]=euid;
        ret = get_errno(getuid());


    
    case TARGET_NR_getxgid:
         {
            uid_t egid;
            egid=getegid();
            ((CPUAlphaState *)cpu_env)->ir[IR_A4]=egid;
        ret = get_errno(getgid());


     
    case TARGET_NR_osf_getsysinfo:
        ret = -TARGET_EOPNOTSUPP;
        switch (arg1) {
          case TARGET_GSI_IEEE_FP_CONTROL:
            {
                uint64_t swcr, fpcr = cpu_alpha_load_fpcr (cpu_env);
                 
                swcr = (fpcr >> 35) & SWCR_STATUS_MASK;
                swcr |= (fpcr >> 36) & SWCR_MAP_DMZ;
                swcr |= (~fpcr >> 48) & (SWCR_TRAP_ENABLE_INV
                                        | SWCR_TRAP_ENABLE_DZE
                                        | SWCR_TRAP_ENABLE_OVF);
                swcr |= (~fpcr >> 57) & (SWCR_TRAP_ENABLE_UNF
                                        | SWCR_TRAP_ENABLE_INE);
                swcr |= (fpcr >> 47) & SWCR_MAP_UMZ;
                swcr |= (~fpcr >> 41) & SWCR_TRAP_ENABLE_DNO;
                if (put_user_u64 (swcr, arg2))
                        goto efault;
                ret = 0;


     
    case TARGET_NR_osf_setsysinfo:
        ret = -TARGET_EOPNOTSUPP;
        switch (arg1) {
          case TARGET_SSI_IEEE_FP_CONTROL:
            {
                uint64_t swcr, fpcr, orig_fpcr;
                if (get_user_u64 (swcr, arg2)) {
                    goto efault;
                orig_fpcr = cpu_alpha_load_fpcr(cpu_env);
                fpcr = orig_fpcr & FPCR_DYN_MASK;
                 
                fpcr |= (swcr & SWCR_STATUS_MASK) << 35;
                fpcr |= (swcr & SWCR_MAP_DMZ) << 36;
                fpcr |= (~swcr & (SWCR_TRAP_ENABLE_INV
                                  | SWCR_TRAP_ENABLE_DZE
                                  | SWCR_TRAP_ENABLE_OVF)) << 48;
                fpcr |= (~swcr & (SWCR_TRAP_ENABLE_UNF
                                  | SWCR_TRAP_ENABLE_INE)) << 57;
                fpcr |= (swcr & SWCR_MAP_UMZ ? FPCR_UNDZ | FPCR_UNFD : 0);
                fpcr |= (~swcr & SWCR_TRAP_ENABLE_DNO) << 41;
                cpu_alpha_store_fpcr(cpu_env, fpcr);
                ret = 0;
          case TARGET_SSI_IEEE_RAISE_EXCEPTION:
            {
                uint64_t exc, fpcr, orig_fpcr;
                int si_code;
                if (get_user_u64(exc, arg2)) {
                    goto efault;
                orig_fpcr = cpu_alpha_load_fpcr(cpu_env);
                 
                fpcr = orig_fpcr | ((exc & SWCR_STATUS_MASK) << 35);
                cpu_alpha_store_fpcr(cpu_env, fpcr);
                ret = 0;
                 
                fpcr &= ~(orig_fpcr & FPCR_STATUS_MASK);
                 
                si_code = 0;
                if ((fpcr & (FPCR_INE | FPCR_INED)) == FPCR_INE) {
                    si_code = TARGET_FPE_FLTRES;
                if ((fpcr & (FPCR_UNF | FPCR_UNFD)) == FPCR_UNF) {
                    si_code = TARGET_FPE_FLTUND;
                if ((fpcr & (FPCR_OVF | FPCR_OVFD)) == FPCR_OVF) {
                    si_code = TARGET_FPE_FLTOVF;
                if ((fpcr & (FPCR_DZE | FPCR_DZED)) == FPCR_DZE) {
                    si_code = TARGET_FPE_FLTDIV;
                if ((fpcr & (FPCR_INV | FPCR_INVD)) == FPCR_INV) {
                    si_code = TARGET_FPE_FLTINV;
                if (si_code != 0) {
                    target_siginfo_t info;
                    info.si_signo = SIGFPE;
                    info.si_errno = 0;
                    info.si_code = si_code;
                    info._sifields._sigfault._addr
                        = ((CPUArchState *)cpu_env)->pc;
                    queue_signal((CPUArchState *)cpu_env, info.si_signo, &info);


     
    case TARGET_NR_osf_sigprocmask:
        {
            abi_ulong mask;
            int how;
            sigset_t set, oldset;
            switch(arg1) {
            case TARGET_SIG_BLOCK:
                how = SIG_BLOCK;
            case TARGET_SIG_UNBLOCK:
                how = SIG_UNBLOCK;
            case TARGET_SIG_SETMASK:
                how = SIG_SETMASK;
            default:
                goto fail;
            mask = arg2;
            target_to_host_old_sigset(&set, &mask);
            ret = do_sigprocmask(how, &set, &oldset);
            if (!ret) {
                host_to_target_old_sigset(&mask, &oldset);
                ret = mask;


    case TARGET_NR_getgid32:
        ret = get_errno(getgid());


    case TARGET_NR_geteuid32:
        ret = get_errno(geteuid());


    case TARGET_NR_getegid32:
        ret = get_errno(getegid());


    case TARGET_NR_setreuid32:
        ret = get_errno(setreuid(arg1, arg2));


    case TARGET_NR_setregid32:
        ret = get_errno(setregid(arg1, arg2));


    case TARGET_NR_getgroups32:
        {
            int gidsetsize = arg1;
            uint32_t *target_grouplist;
            gid_t *grouplist;
            int i;
            grouplist = alloca(gidsetsize * sizeof(gid_t));
            ret = get_errno(getgroups(gidsetsize, grouplist));
            if (gidsetsize == 0)
            if (!is_error(ret)) {
                target_grouplist = lock_user(VERIFY_WRITE, arg2, gidsetsize * 4, 0);
                if (!target_grouplist) {
                    ret = -TARGET_EFAULT;
                    goto fail;
                for(i = 0;i < ret; i++)
                    target_grouplist[i] = tswap32(grouplist[i]);
                unlock_user(target_grouplist, arg2, gidsetsize * 4);


    case TARGET_NR_setgroups32:
        {
            int gidsetsize = arg1;
            uint32_t *target_grouplist;
            gid_t *grouplist;
            int i;
            grouplist = alloca(gidsetsize * sizeof(gid_t));
            target_grouplist = lock_user(VERIFY_READ, arg2, gidsetsize * 4, 1);
            if (!target_grouplist) {
                ret = -TARGET_EFAULT;
                goto fail;
            for(i = 0;i < gidsetsize; i++)
                grouplist[i] = tswap32(target_grouplist[i]);
            unlock_user(target_grouplist, arg2, 0);
            ret = get_errno(setgroups(gidsetsize, grouplist));


    case TARGET_NR_fchown32:
        ret = get_errno(fchown(arg1, arg2, arg3));


    case TARGET_NR_setresuid32:
        ret = get_errno(sys_setresuid(arg1, arg2, arg3));


    case TARGET_NR_getresuid32:
        {
            uid_t ruid, euid, suid;
            ret = get_errno(getresuid(&ruid, &euid, &suid));
            if (!is_error(ret)) {
                if (put_user_u32(ruid, arg1)
                    || put_user_u32(euid, arg2)
                    || put_user_u32(suid, arg3))
                    goto efault;


    case TARGET_NR_setresgid32:
        ret = get_errno(sys_setresgid(arg1, arg2, arg3));


    case TARGET_NR_getresgid32:
        {
            gid_t rgid, egid, sgid;
            ret = get_errno(getresgid(&rgid, &egid, &sgid));
            if (!is_error(ret)) {
                if (put_user_u32(rgid, arg1)
                    || put_user_u32(egid, arg2)
                    || put_user_u32(sgid, arg3))
                    goto efault;


    case TARGET_NR_chown32:
        if (!(p = lock_user_string(arg1)))
            goto efault;
        ret = get_errno(chown(p, arg2, arg3));
        unlock_user(p, arg1, 0);


    case TARGET_NR_setuid32:
        ret = get_errno(sys_setuid(arg1));


    case TARGET_NR_setgid32:
        ret = get_errno(sys_setgid(arg1));


    case TARGET_NR_setfsuid32:
        ret = get_errno(setfsuid(arg1));


    case TARGET_NR_setfsgid32:
        ret = get_errno(setfsgid(arg1));

    case TARGET_NR_pivot_root:
        goto unimplemented;

    case TARGET_NR_mincore:
        {
            void *a;
            ret = -TARGET_EFAULT;
            if (!(a = lock_user(VERIFY_READ, arg1,arg2, 0)))
                goto efault;
            if (!(p = lock_user_string(arg3)))
                goto mincore_fail;
            ret = get_errno(mincore(a, arg2, p));
            unlock_user(p, arg3, ret);
            mincore_fail:
            unlock_user(a, arg1, 0);


    case TARGET_NR_arm_fadvise64_64:
         
        ret = posix_fadvise(arg1, target_offset64(arg3, arg4),
                            target_offset64(arg5, arg6), arg2);
        ret = -host_to_target_errno(ret);



    case TARGET_NR_fadvise64_64:
         
        if (regpairs_aligned(cpu_env)) {
             
            arg2 = arg3;
            arg3 = arg4;
            arg4 = arg5;
            arg5 = arg6;
            arg6 = arg7;
        ret = -host_to_target_errno(posix_fadvise(arg1,
                                                  target_offset64(arg2, arg3),
                                                  target_offset64(arg4, arg5),
                                                  arg6));


    case TARGET_NR_fadvise64:
         
        if (regpairs_aligned(cpu_env)) {
             
            arg2 = arg3;
            arg3 = arg4;
            arg4 = arg5;
            arg5 = arg6;
        ret = -host_to_target_errno(posix_fadvise(arg1,
                                                  target_offset64(arg2, arg3),
                                                  arg4, arg5));




    case TARGET_NR_fadvise64_64:


    case TARGET_NR_fadvise64:


        switch (arg4) {
        case 4: arg4 = POSIX_FADV_NOREUSE + 1; break;  
        case 5: arg4 = POSIX_FADV_NOREUSE + 2; break;  
        case 6: arg4 = POSIX_FADV_DONTNEED; break;
        case 7: arg4 = POSIX_FADV_NOREUSE; break;
        default: break;

        ret = -host_to_target_errno(posix_fadvise(arg1, arg2, arg3, arg4));



    case TARGET_NR_madvise:
         
        ret = get_errno(0);


    case TARGET_NR_fcntl64:
    {
	int cmd;
	struct flock64 fl;
        from_flock64_fn *copyfrom = copy_from_user_flock64;
        to_flock64_fn *copyto = copy_to_user_flock64;

        if (((CPUARMState *)cpu_env)->eabi) {
            copyfrom = copy_from_user_eabi_flock64;
            copyto = copy_to_user_eabi_flock64;

	cmd = target_to_host_fcntl_cmd(arg2);
        if (cmd == -TARGET_EINVAL) {
            ret = cmd;
        switch(arg2) {
        case TARGET_F_GETLK64:
            ret = copyfrom(&fl, arg3);
            if (ret) {
            ret = get_errno(fcntl(arg1, cmd, &fl));
            if (ret == 0) {
                ret = copyto(arg3, &fl);
        case TARGET_F_SETLK64:
        case TARGET_F_SETLKW64:
            ret = copyfrom(&fl, arg3);
            if (ret) {
            ret = get_errno(safe_fcntl(arg1, cmd, &fl));
        default:
            ret = do_fcntl(arg1, arg2, arg3);


    case TARGET_NR_cacheflush:
         
        ret = 0;


    case TARGET_NR_security:
        goto unimplemented;


    case TARGET_NR_getpagesize:
        ret = TARGET_PAGE_SIZE;

    case TARGET_NR_gettid:
        ret = get_errno(gettid());

    case TARGET_NR_readahead:

        if (regpairs_aligned(cpu_env)) {
            arg2 = arg3;
            arg3 = arg4;
            arg4 = arg5;
        ret = get_errno(readahead(arg1, ((off64_t)arg3 << 32) | arg2, arg4));

        ret = get_errno(readahead(arg1, arg2, arg3));




    case TARGET_NR_listxattr:
    case TARGET_NR_llistxattr:
    {
        void *p, *b = 0;
        if (arg2) {
            b = lock_user(VERIFY_WRITE, arg2, arg3, 0);
            if (!b) {
                ret = -TARGET_EFAULT;
        p = lock_user_string(arg1);
        if (p) {
            if (num == TARGET_NR_listxattr) {
                ret = get_errno(listxattr(p, b, arg3));
            } else {
                ret = get_errno(llistxattr(p, b, arg3));
        } else {
            ret = -TARGET_EFAULT;
        unlock_user(p, arg1, 0);
        unlock_user(b, arg2, arg3);
    case TARGET_NR_flistxattr:
    {
        void *b = 0;
        if (arg2) {
            b = lock_user(VERIFY_WRITE, arg2, arg3, 0);
            if (!b) {
                ret = -TARGET_EFAULT;
        ret = get_errno(flistxattr(arg1, b, arg3));
        unlock_user(b, arg2, arg3);
    case TARGET_NR_setxattr:
    case TARGET_NR_lsetxattr:
        {
            void *p, *n, *v = 0;
            if (arg3) {
                v = lock_user(VERIFY_READ, arg3, arg4, 1);
                if (!v) {
                    ret = -TARGET_EFAULT;
            p = lock_user_string(arg1);
            n = lock_user_string(arg2);
            if (p && n) {
                if (num == TARGET_NR_setxattr) {
                    ret = get_errno(setxattr(p, n, v, arg4, arg5));
                } else {
                    ret = get_errno(lsetxattr(p, n, v, arg4, arg5));
            } else {
                ret = -TARGET_EFAULT;
            unlock_user(p, arg1, 0);
            unlock_user(n, arg2, 0);
            unlock_user(v, arg3, 0);
    case TARGET_NR_fsetxattr:
        {
            void *n, *v = 0;
            if (arg3) {
                v = lock_user(VERIFY_READ, arg3, arg4, 1);
                if (!v) {
                    ret = -TARGET_EFAULT;
            n = lock_user_string(arg2);
            if (n) {
                ret = get_errno(fsetxattr(arg1, n, v, arg4, arg5));
            } else {
                ret = -TARGET_EFAULT;
            unlock_user(n, arg2, 0);
            unlock_user(v, arg3, 0);
    case TARGET_NR_getxattr:
    case TARGET_NR_lgetxattr:
        {
            void *p, *n, *v = 0;
            if (arg3) {
                v = lock_user(VERIFY_WRITE, arg3, arg4, 0);
                if (!v) {
                    ret = -TARGET_EFAULT;
            p = lock_user_string(arg1);
            n = lock_user_string(arg2);
            if (p && n) {
                if (num == TARGET_NR_getxattr) {
                    ret = get_errno(getxattr(p, n, v, arg4));
                } else {
                    ret = get_errno(lgetxattr(p, n, v, arg4));
            } else {
                ret = -TARGET_EFAULT;
            unlock_user(p, arg1, 0);
            unlock_user(n, arg2, 0);
            unlock_user(v, arg3, arg4);
    case TARGET_NR_fgetxattr:
        {
            void *n, *v = 0;
            if (arg3) {
                v = lock_user(VERIFY_WRITE, arg3, arg4, 0);
                if (!v) {
                    ret = -TARGET_EFAULT;
            n = lock_user_string(arg2);
            if (n) {
                ret = get_errno(fgetxattr(arg1, n, v, arg4));
            } else {
                ret = -TARGET_EFAULT;
            unlock_user(n, arg2, 0);
            unlock_user(v, arg3, arg4);
    case TARGET_NR_removexattr:
    case TARGET_NR_lremovexattr:
        {
            void *p, *n;
            p = lock_user_string(arg1);
            n = lock_user_string(arg2);
            if (p && n) {
                if (num == TARGET_NR_removexattr) {
                    ret = get_errno(removexattr(p, n));
                } else {
                    ret = get_errno(lremovexattr(p, n));
            } else {
                ret = -TARGET_EFAULT;
            unlock_user(p, arg1, 0);
            unlock_user(n, arg2, 0);
    case TARGET_NR_fremovexattr:
        {
            void *n;
            n = lock_user_string(arg2);
            if (n) {
                ret = get_errno(fremovexattr(arg1, n));
            } else {
                ret = -TARGET_EFAULT;
            unlock_user(n, arg2, 0);



    case TARGET_NR_set_thread_area:

      ((CPUMIPSState *) cpu_env)->active_tc.CP0_UserLocal = arg1;
      ret = 0;

      if (arg1 & 0xff)
      else {
          ((CPUCRISState *) cpu_env)->pregs[PR_PID] = arg1;
          ret = 0;

      ret = do_set_thread_area(cpu_env, arg1);

      {
          TaskState *ts = cpu->opaque;
          ts->tp_value = arg1;
          ret = 0;

      goto unimplemented_nowarn;



    case TARGET_NR_get_thread_area:

        ret = do_get_thread_area(cpu_env, arg1);

        {
            TaskState *ts = cpu->opaque;
            ret = ts->tp_value;

        goto unimplemented_nowarn;



    case TARGET_NR_getdomainname:
        goto unimplemented_nowarn;


    case TARGET_NR_clock_gettime:
    {
        struct timespec ts;
        ret = get_errno(clock_gettime(arg1, &ts));
        if (!is_error(ret)) {
            host_to_target_timespec(arg2, &ts);


    case TARGET_NR_clock_getres:
    {
        struct timespec ts;
        ret = get_errno(clock_getres(arg1, &ts));
        if (!is_error(ret)) {
            host_to_target_timespec(arg2, &ts);


    case TARGET_NR_clock_nanosleep:
    {
        struct timespec ts;
        target_to_host_timespec(&ts, arg3);
        ret = get_errno(safe_clock_nanosleep(arg1, arg2,
                                             &ts, arg4 ? &ts : NULL));
        if (arg4)
            host_to_target_timespec(arg4, &ts);

         
        if (ret && ret != -TARGET_ERESTARTSYS) {
            ((CPUPPCState *)cpu_env)->crf[0] |= 1;



    case TARGET_NR_set_tid_address:
        ret = get_errno(set_tid_address((int *)g2h(arg1)));

    case TARGET_NR_tkill:
        ret = get_errno(safe_tkill((int)arg1, target_to_host_signal(arg2)));
    case TARGET_NR_tgkill:
        ret = get_errno(safe_tgkill((int)arg1, (int)arg2,
                        target_to_host_signal(arg3)));

    case TARGET_NR_set_robust_list:
    case TARGET_NR_get_robust_list:
         
        goto unimplemented_nowarn;


    case TARGET_NR_utimensat:
        {
            struct timespec *tsp, ts[2];
            if (!arg3) {
                tsp = NULL;
            } else {
                target_to_host_timespec(ts, arg3);
                target_to_host_timespec(ts+1, arg3+sizeof(struct target_timespec));
                tsp = ts;
            if (!arg2)
                ret = get_errno(sys_utimensat(arg1, NULL, tsp, arg4));
            else {
                if (!(p = lock_user_string(arg2))) {
                    ret = -TARGET_EFAULT;
                    goto fail;
                ret = get_errno(sys_utimensat(arg1, path(p), tsp, arg4));
                unlock_user(p, arg2, 0);

    case TARGET_NR_futex:
        ret = do_futex(arg1, arg2, arg3, arg4, arg5, arg6);

    case TARGET_NR_inotify_init:
        ret = get_errno(sys_inotify_init());



    case TARGET_NR_inotify_init1:
        ret = get_errno(sys_inotify_init1(arg1));



    case TARGET_NR_inotify_add_watch:
        p = lock_user_string(arg2);
        ret = get_errno(sys_inotify_add_watch(arg1, path(p), arg3));
        unlock_user(p, arg2, 0);


    case TARGET_NR_inotify_rm_watch:
        ret = get_errno(sys_inotify_rm_watch(arg1, arg2));


    case TARGET_NR_mq_open:
        {
            struct mq_attr posix_mq_attr, *attrp;
            p = lock_user_string(arg1 - 1);
            if (arg4 != 0) {
                copy_from_user_mq_attr (&posix_mq_attr, arg4);
                attrp = &posix_mq_attr;
            } else {
                attrp = 0;
            ret = get_errno(mq_open(p, arg2, arg3, attrp));
            unlock_user (p, arg1, 0);
    case TARGET_NR_mq_unlink:
        p = lock_user_string(arg1 - 1);
        ret = get_errno(mq_unlink(p));
        unlock_user (p, arg1, 0);
    case TARGET_NR_mq_timedsend:
        {
            struct timespec ts;
            p = lock_user (VERIFY_READ, arg2, arg3, 1);
            if (arg5 != 0) {
                target_to_host_timespec(&ts, arg5);
                ret = get_errno(safe_mq_timedsend(arg1, p, arg3, arg4, &ts));
                host_to_target_timespec(arg5, &ts);
            } else {
                ret = get_errno(safe_mq_timedsend(arg1, p, arg3, arg4, NULL));
            unlock_user (p, arg2, arg3);
    case TARGET_NR_mq_timedreceive:
        {
            struct timespec ts;
            unsigned int prio;
            p = lock_user (VERIFY_READ, arg2, arg3, 1);
            if (arg5 != 0) {
                target_to_host_timespec(&ts, arg5);
                ret = get_errno(safe_mq_timedreceive(arg1, p, arg3,
                                                     &prio, &ts));
                host_to_target_timespec(arg5, &ts);
            } else {
                ret = get_errno(safe_mq_timedreceive(arg1, p, arg3,
                                                     &prio, NULL));
            unlock_user (p, arg2, arg3);
            if (arg4 != 0)
                put_user_u32(prio, arg4);
     
 
 
    case TARGET_NR_mq_getsetattr:
        {
            struct mq_attr posix_mq_attr_in, posix_mq_attr_out;
            ret = 0;
            if (arg3 != 0) {
                ret = mq_getattr(arg1, &posix_mq_attr_out);
                copy_to_user_mq_attr(arg3, &posix_mq_attr_out);
            if (arg2 != 0) {
                copy_from_user_mq_attr(&posix_mq_attr_in, arg2);
                ret |= mq_setattr(arg1, &posix_mq_attr_in, &posix_mq_attr_out);



    case TARGET_NR_tee:
        {
            ret = get_errno(tee(arg1,arg2,arg3,arg4));


    case TARGET_NR_splice:
        {
            loff_t loff_in, loff_out;
            loff_t *ploff_in = NULL, *ploff_out = NULL;
            if (arg2) {
                if (get_user_u64(loff_in, arg2)) {
                    goto efault;
                ploff_in = &loff_in;
            if (arg4) {
                if (get_user_u64(loff_out, arg4)) {
                    goto efault;
                ploff_out = &loff_out;
            ret = get_errno(splice(arg1, ploff_in, arg3, ploff_out, arg5, arg6));
            if (arg2) {
                if (put_user_u64(loff_in, arg2)) {
                    goto efault;
            if (arg4) {
                if (put_user_u64(loff_out, arg4)) {
                    goto efault;


	case TARGET_NR_vmsplice:
        {
            struct iovec *vec = lock_iovec(VERIFY_READ, arg2, arg3, 1);
            if (vec != NULL) {
                ret = get_errno(vmsplice(arg1, vec, arg3, arg4));
                unlock_iovec(vec, arg2, arg3, 0);
            } else {
                ret = -host_to_target_errno(errno);




    case TARGET_NR_eventfd:
        ret = get_errno(eventfd(arg1, 0));
        fd_trans_unregister(ret);


    case TARGET_NR_eventfd2:
    {
        int host_flags = arg2 & (~(TARGET_O_NONBLOCK | TARGET_O_CLOEXEC));
        if (arg2 & TARGET_O_NONBLOCK) {
            host_flags |= O_NONBLOCK;
        if (arg2 & TARGET_O_CLOEXEC) {
            host_flags |= O_CLOEXEC;
        ret = get_errno(eventfd(arg1, host_flags));
        fd_trans_unregister(ret);



    case TARGET_NR_fallocate:

        ret = get_errno(fallocate(arg1, arg2, target_offset64(arg3, arg4),
                                  target_offset64(arg5, arg6)));

        ret = get_errno(fallocate(arg1, arg2, arg3, arg4));




    case TARGET_NR_sync_file_range:


        ret = get_errno(sync_file_range(arg1, target_offset64(arg3, arg4),
                                        target_offset64(arg5, arg6), arg7));

        ret = get_errno(sync_file_range(arg1, target_offset64(arg2, arg3),
                                        target_offset64(arg4, arg5), arg6));


        ret = get_errno(sync_file_range(arg1, arg2, arg3, arg4));



    case TARGET_NR_sync_file_range2:

        ret = get_errno(sync_file_range(arg1, target_offset64(arg3, arg4),
                                        target_offset64(arg5, arg6), arg2));

        ret = get_errno(sync_file_range(arg1, arg3, arg4, arg2));




    case TARGET_NR_signalfd4:
        ret = do_signalfd4(arg1, arg2, arg4);


    case TARGET_NR_signalfd:
        ret = do_signalfd4(arg1, arg2, 0);



    case TARGET_NR_epoll_create:
        ret = get_errno(epoll_create(arg1));


    case TARGET_NR_epoll_create1:
        ret = get_errno(epoll_create1(arg1));


    case TARGET_NR_epoll_ctl:
    {
        struct epoll_event ep;
        struct epoll_event *epp = 0;
        if (arg4) {
            struct target_epoll_event *target_ep;
            if (!lock_user_struct(VERIFY_READ, target_ep, arg4, 1)) {
                goto efault;
            ep.events = tswap32(target_ep->events);
             
            ep.data.u64 = tswap64(target_ep->data.u64);
            unlock_user_struct(target_ep, arg4, 0);
            epp = &ep;
        ret = get_errno(epoll_ctl(arg1, arg2, arg3, epp));



    case TARGET_NR_epoll_wait:


    case TARGET_NR_epoll_pwait:

    {
        struct target_epoll_event *target_ep;
        struct epoll_event *ep;
        int epfd = arg1;
        int maxevents = arg3;
        int timeout = arg4;
        if (maxevents <= 0 || maxevents > TARGET_EP_MAX_EVENTS) {
        target_ep = lock_user(VERIFY_WRITE, arg2,
                              maxevents * sizeof(struct target_epoll_event), 1);
        if (!target_ep) {
            goto efault;
        ep = alloca(maxevents * sizeof(struct epoll_event));
        switch (num) {

        case TARGET_NR_epoll_pwait:
        {
            target_sigset_t *target_set;
            sigset_t _set, *set = &_set;
            if (arg5) {
                if (arg6 != sizeof(target_sigset_t)) {
                target_set = lock_user(VERIFY_READ, arg5,
                                       sizeof(target_sigset_t), 1);
                if (!target_set) {
                    unlock_user(target_ep, arg2, 0);
                    goto efault;
                target_to_host_sigset(set, target_set);
                unlock_user(target_set, arg5, 0);
            } else {
                set = NULL;
            ret = get_errno(safe_epoll_pwait(epfd, ep, maxevents, timeout,
                                             set, SIGSET_T_SIZE));


        case TARGET_NR_epoll_wait:
            ret = get_errno(safe_epoll_pwait(epfd, ep, maxevents, timeout,
                                             NULL, 0));

        default:
            ret = -TARGET_ENOSYS;
        if (!is_error(ret)) {
            int i;
            for (i = 0; i < ret; i++) {
                target_ep[i].events = tswap32(ep[i].events);
                target_ep[i].data.u64 = tswap64(ep[i].data.u64);
        unlock_user(target_ep, arg2, ret * sizeof(struct target_epoll_event));



    case TARGET_NR_prlimit64:
    {
         
        struct target_rlimit64 *target_rnew, *target_rold;
        struct host_rlimit64 rnew, rold, *rnewp = 0;
        int resource = target_to_host_resource(arg2);
        if (arg3) {
            if (!lock_user_struct(VERIFY_READ, target_rnew, arg3, 1)) {
                goto efault;
            rnew.rlim_cur = tswap64(target_rnew->rlim_cur);
            rnew.rlim_max = tswap64(target_rnew->rlim_max);
            unlock_user_struct(target_rnew, arg3, 0);
            rnewp = &rnew;
        ret = get_errno(sys_prlimit64(arg1, resource, rnewp, arg4 ? &rold : 0));
        if (!is_error(ret) && arg4) {
            if (!lock_user_struct(VERIFY_WRITE, target_rold, arg4, 1)) {
                goto efault;
            target_rold->rlim_cur = tswap64(rold.rlim_cur);
            target_rold->rlim_max = tswap64(rold.rlim_max);
            unlock_user_struct(target_rold, arg4, 1);


    case TARGET_NR_gethostname:
    {
        char *name = lock_user(VERIFY_WRITE, arg1, arg2, 0);
        if (name) {
            ret = get_errno(gethostname(name, arg2));
            unlock_user(name, arg1, arg2);
        } else {
            ret = -TARGET_EFAULT;


    case TARGET_NR_atomic_cmpxchg_32:
    {
         
        abi_ulong mem_value;
        if (get_user_u32(mem_value, arg6)) {
            target_siginfo_t info;
            info.si_signo = SIGSEGV;
            info.si_errno = 0;
            info.si_code = TARGET_SEGV_MAPERR;
            info._sifields._sigfault._addr = arg6;
            queue_signal((CPUArchState *)cpu_env, info.si_signo, &info);
            ret = 0xdeadbeef;
        if (mem_value == arg2)
            put_user_u32(arg1, arg6);
        ret = mem_value;


    case TARGET_NR_atomic_barrier:
    {
         
        ret = 0;


    case TARGET_NR_timer_create:
    {
         
        struct sigevent host_sevp = { {0}, }, *phost_sevp = NULL;
        int clkid = arg1;
        int timer_index = next_free_host_timer();
        if (timer_index < 0) {
            ret = -TARGET_EAGAIN;
        } else {
            timer_t *phtimer = g_posix_timers  + timer_index;
            if (arg2) {
                phost_sevp = &host_sevp;
                ret = target_to_host_sigevent(phost_sevp, arg2);
                if (ret != 0) {
            ret = get_errno(timer_create(clkid, phost_sevp, phtimer));
            if (ret) {
                phtimer = NULL;
            } else {
                if (put_user(TIMER_MAGIC | timer_index, arg3, target_timer_t)) {
                    goto efault;


    case TARGET_NR_timer_settime:
    {
         
        target_timer_t timerid = get_timer_id(arg1);
        if (timerid < 0) {
            ret = timerid;
        } else if (arg3 == 0) {
        } else {
            timer_t htimer = g_posix_timers[timerid];
            struct itimerspec hspec_new = {{0},}, hspec_old = {{0},};
            target_to_host_itimerspec(&hspec_new, arg3);
            ret = get_errno(
                          timer_settime(htimer, arg2, &hspec_new, &hspec_old));
            host_to_target_itimerspec(arg2, &hspec_old);


    case TARGET_NR_timer_gettime:
    {
         
        target_timer_t timerid = get_timer_id(arg1);
        if (timerid < 0) {
            ret = timerid;
        } else if (!arg2) {
            ret = -TARGET_EFAULT;
        } else {
            timer_t htimer = g_posix_timers[timerid];
            struct itimerspec hspec;
            ret = get_errno(timer_gettime(htimer, &hspec));
            if (host_to_target_itimerspec(arg2, &hspec)) {
                ret = -TARGET_EFAULT;


    case TARGET_NR_timer_getoverrun:
    {
         
        target_timer_t timerid = get_timer_id(arg1);
        if (timerid < 0) {
            ret = timerid;
        } else {
            timer_t htimer = g_posix_timers[timerid];
            ret = get_errno(timer_getoverrun(htimer));
        fd_trans_unregister(ret);


    case TARGET_NR_timer_delete:
    {
         
        target_timer_t timerid = get_timer_id(arg1);
        if (timerid < 0) {
            ret = timerid;
        } else {
            timer_t htimer = g_posix_timers[timerid];
            ret = get_errno(timer_delete(htimer));
            g_posix_timers[timerid] = 0;


    case TARGET_NR_timerfd_create:
        ret = get_errno(timerfd_create(arg1,
                target_to_host_bitmask(arg2, fcntl_flags_tbl)));


    case TARGET_NR_timerfd_gettime:
        {
            struct itimerspec its_curr;
            ret = get_errno(timerfd_gettime(arg1, &its_curr));
            if (arg2 && host_to_target_itimerspec(arg2, &its_curr)) {
                goto efault;


    case TARGET_NR_timerfd_settime:
        {
            struct itimerspec its_new, its_old, *p_new;
            if (arg3) {
                if (target_to_host_itimerspec(&its_new, arg3)) {
                    goto efault;
                p_new = &its_new;
            } else {
                p_new = NULL;
            ret = get_errno(timerfd_settime(arg1, arg2, p_new, &its_old));
            if (arg4 && host_to_target_itimerspec(arg4, &its_old)) {
                goto efault;


    case TARGET_NR_ioprio_get:
        ret = get_errno(ioprio_get(arg1, arg2));


    case TARGET_NR_ioprio_set:
        ret = get_errno(ioprio_set(arg1, arg2, arg3));


    case TARGET_NR_setns:
        ret = get_errno(setns(arg1, arg2));


    case TARGET_NR_unshare:
        ret = get_errno(unshare(arg1));

    default:
    unimplemented:
        gemu_log("qemu: Unsupported syscall: %d\n", num);

    unimplemented_nowarn:

        ret = -TARGET_ENOSYS;
fail:

    gemu_log(" = " TARGET_ABI_FMT_ld "\n", ret);

    if(do_strace)
        print_syscall_ret(num, ret);
    trace_guest_user_syscall_ret(cpu, num, ret);
    return ret;
efault:
    ret = -TARGET_EFAULT;
    goto fail;