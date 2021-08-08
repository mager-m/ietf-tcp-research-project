#ifndef PLUGIN_OPTIONS_H
#define PLUGIN_OPTIONS_H

/* Command line plugin_options to be passed to getopt(3) */
#define BACKEND_EXAMPLE_OPTS "rsS:iuUt:v:"

#include <cligen/cligen.h>
#include <clixon/clixon.h>
#include <cstdlib>
#include <unistd.h>

class CliOptions {
public:
    // If set, call syslog for every transaction callback  -- -t
    int enableTransactionLogging;

    CliOptions();

    ~CliOptions() = default;

    void read_args_from_cli(clicon_handle h);
};


class Settings {

private:

    static Settings *_instance;

    explicit Settings(CliOptions *opt) : cliOptions(opt) {}

public:

    CliOptions *cliOptions;

    Settings(const Settings &) = delete;

    Settings &operator=(const Settings &) = delete;

    static Settings *getInstance();

    static void read_cli_args(clicon_handle h);

    Settings() = default;
};


#endif //PLUGIN_OPTIONS_H
