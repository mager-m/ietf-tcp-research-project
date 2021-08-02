#ifndef PLUGIN_STATE_H
#define PLUGIN_STATE_H

#include "plugin_options.h"


class StatedataManager {

    /*! Called to get the state data from the local machine
    *
    * @param[in] h         The CLIGen Handle
    * @param[in] nsc       External XML namespace context, or NULL
    * @param[in] xpath     String with XPATH syntax. or NULL for all
    * @param[in] xstate    XML tree, <config/> on entry.
    * @retval    0         OK
    * @retval    -1        Error
    */
    static int query_statedate_from_machine(clicon_handle h, cvec *nsc, char *xpath, cxobj *xstate);

public:


    /*! Called to get state data from plugin
    * @param[in]    h      Clicon handle
    * @param[in]    nsc    External XML namespace context, or NULL
    * @param[in]    xpath  String with XPATH syntax. or NULL for all
    * @param[in]    xstate XML tree, <config/> on entry.
    * @retval       0      OK
    * @retval      -1      Error
    */
    static int query_statedata(clicon_handle h, cvec *nsc, char *xpath, cxobj *xstate);
};


#endif //PLUGIN_STATE_H
