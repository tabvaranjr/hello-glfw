#include "TestApplication.h"
#include "ApplicationParameters.h"

int main(int argc, char* argv[])
{
    auto parameters = ApplicationParameters::createFromCommandLineArguments(argc, argv);

    TestApplication app(parameters);

    app.run();

    return 0;
}
