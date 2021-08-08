#ifndef PLUGIN_LIFECYLE_H
#define PLUGIN_LIFECYLE_H


class LifecycleManager{
public:
    /*! Plugin start.
    * @param[in]  h     Clicon handle
    *
    * plugin_start is called once everything has been initialized, right before
    * the main event loop is entered.
    */
    static int plugin_start(clicon_handle h);

    /*! Plugin exit.
    * @param[in]  h     Clicon handle
    *
    * plugin_exit is called once after the main event loop is finished
    */
    static int plugin_exit(clicon_handle h);


    /*! Plugin daemon.
    * @param[in]  h     Clicon handle
    *
    * plugin_daemon is called once after damonization has been made but before lowering of privileges
    * the main event loop is entered.
    */
    static int plugin_daemon(clicon_handle h);

};

#endif //PLUGIN_LIFECYLE_H
