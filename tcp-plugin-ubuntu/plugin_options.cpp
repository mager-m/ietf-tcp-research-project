#include <stdexcept>
#include "plugin_options.h"


CliOptions::CliOptions() {
    this->enableTransactionLogging = 0;
}

void CliOptions::read_args_from_cli(clicon_handle h) {

    // Get user command-line plugin_options (after --)
    int argsCount;
    char **argsValue;
    opterr = 0;
    optind = 1;
    if (clicon_argv_get(h, &argsCount, &argsValue) < 0)
        throw std::runtime_error("Invalid command-line input");

    // set plugin cliOptions
    while (true) {
        int c = getopt(argsCount, argsValue, BACKEND_EXAMPLE_OPTS);
        if (c == -1)
            break;

        switch (c) {
            case 't':   // transaction log
                this->enableTransactionLogging = 1;
                break;
            default:
                throw std::runtime_error("Unknown command-line argument" + std::to_string(c));
        }
    }
}

Settings *Settings::_instance = nullptr;

void Settings::read_cli_args(clicon_handle h) {
    auto *cli_opt = new CliOptions();
    cli_opt->read_args_from_cli(h);
    _instance = new Settings(cli_opt);
}

Settings *Settings::getInstance() {
    if (!_instance) {
        _instance = new Settings();
        return _instance;
    }
    return _instance;
}