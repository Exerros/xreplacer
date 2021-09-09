#include "core.hpp"

namespace xrep {

XReplacerCore::XReplacerCore()
    : config(nullptr)
    , parser(nullptr)
    , replacer(nullptr)
    { }

//------------------------------------------------------------------------------
void XReplacerCore::init(int argc, char** argv) {
    LOG(info) << BORDER;
    LOG(info) << "Initialization of xReplaser started";
    fs_path config_path;

    try {
        if (argc == 2) { config_path = fs_path(argv[1]); }
        else           { config_path = fs_path(STANDART_CONFIG_PATH); }

        config = config_ptr(new JsonConfigurator(config_path));

        parser = parser_ptr(new FileSystemParser(config->get_root_dir()));

        replacer = replacer_ptr(
            new FileDataReplacer(config->get_pairs(),
                                 config->get_thread_count())
        );

    } catch (exception::non_FatalException& ex) {
        LOG(error) << ex.what();

    } catch (exception::FatalException& ex) {
        LOG(fatal) << ex.what();
        exit(1);
    }

    LOG(info) << "xReplaser initialization completed successfully";
    LOG(info) << BORDER;
}

//------------------------------------------------------------------------------
int XReplacerCore::run() {
    LOG(info) << "xReplaser starts processing files";
    try {
        parser->search_objects_to_replase();

        if (parser->has_objects_to_replace()) {
            replacer->replase(parser->get_objects_to_replase());

        } else throw exception::parser::NoObjects();

    } catch (std::exception& ex) {
        LOG(fatal) << ex.what();
        exit(2);
    }
    LOG(info) << "xReplaser has finished work";
    LOG(info) << BORDER;

    return 0;
}


} // namespace xrep
