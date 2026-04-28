#include "controller.hpp"
#include <json/json.h>
#include <filesystem>
#include <fstream>

extern int qInitResources();
extern int qCleanupResources();

namespace fs = std::filesystem;

Controller::Controller(int argc, char** argv) :
	m_App(argc, argv)
{
    fs::path programPath = fs::weakly_canonical(fs::absolute(argv[0]));
    m_ProgramPath = QString::fromStdString(programPath.parent_path().generic_string().c_str());
    qInitResources();
	configureLocale();
	m_MainWindow = new MainWindow(m_ProgramPath.toStdString());
    m_MainWindow->show();
}

Controller::~Controller()
{
    delete m_MainWindow;
    qCleanupResources();
}

void Controller::run()
{
    while (m_MainWindow->isRunning())
        m_App.processEvents();
}

void Controller::readSettings()
{
}

void Controller::configureLocale()
{
    fs::path programPath = m_ProgramPath.toStdString() + "/settings.json";
    if(!fs::exists(programPath.generic_string()))
    {
        Json::Value root;
        root["locale"] = "en_US";
        Json::FastWriter writer;
		std::string jsonOut = writer.write(root);
		std::ofstream out(programPath);
		out << jsonOut;
        return;
    }
    Json::Value root; // 'root' will contain the root value after parsing
    Json::CharReaderBuilder builder;
    std::string errs;
    std::ifstream wrapper(programPath);
    bool success = Json::parseFromStream(builder, wrapper, &root, &errs);
	if (success)
	{
		fs::path filename = fs::weakly_canonical
        (fs::path(m_ProgramPath.toStdString()) / fs::path( 
            "./translations/" + root["locale"].asString() + ".qm"));
        if (std::filesystem::exists(filename))
        {
            auto loadResult = m_Translator.load(filename.generic_string().c_str());
            m_App.installTranslator(&m_Translator);
        }
	}
}
