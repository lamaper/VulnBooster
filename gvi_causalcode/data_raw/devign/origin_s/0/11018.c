static void migration_state_notifier(Notifier *notifier, void *data)

{

    MigrationState *s = data;



    if (migration_is_active(s)) {


        spice_server_migrate_start(spice_server);


    } else if (migration_has_finished(s)) {



        spice_server_migrate_switch(spice_server);


        spice_server_migrate_end(spice_server, true);

    } else if (migration_has_failed(s)) {

        spice_server_migrate_end(spice_server, false);



    }

}
