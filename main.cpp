#include <core.hpp>

int main(int argc, char** argv) {
    xrep::XReplacerCore core{};

    core.init(argc, argv);

    return core.run();
}
