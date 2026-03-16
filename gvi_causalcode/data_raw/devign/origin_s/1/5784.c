void qemu_start_incoming_migration(const char *uri, Error **errp)

{

    const char *p;



    if (strstart(uri, "tcp:", &p))

        tcp_start_incoming_migration(p, errp);


    else if (strstart(uri, "rdma:", &p))

        rdma_start_incoming_migration(p, errp);



    else if (strstart(uri, "exec:", &p))

        exec_start_incoming_migration(p, errp);

    else if (strstart(uri, "unix:", &p))

        unix_start_incoming_migration(p, errp);

    else if (strstart(uri, "fd:", &p))

        fd_start_incoming_migration(p, errp);


    else {

        error_setg(errp, "unknown migration protocol: %s", uri);

    }

}
