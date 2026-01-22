#include "controller.hpp"
#include <json/json.h>
#include <filesystem>
#include <fstream>

extern int qInitResources();
extern int qCleanupResources();

Controller::Controller(int argc, char** argv) :
	m_App(argc, argv)
{
    qInitResources();
	configureLocale();
	m_MainWindow = new MainWindow();
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
    if(!std::filesystem::exists("settings.json")) 
    {
        Json::Value root;
        root["locale"] = "en_US";
        Json::FastWriter writer;
		std::string jsonOut = writer.write(root);
		std::ofstream out("settings.json");
		out << jsonOut;
        return;
    }
    Json::Value root; // 'root' will contain the root value after parsing
    Json::CharReaderBuilder builder;
    std::string errs;
    std::ifstream wrapper("settings.json");
    bool success = Json::parseFromStream(builder, wrapper, &root, &errs);
	if (success)
	{
		std::string filename = "./translations/" + root["locale"].asString() + ".qm";
        if (std::filesystem::exists(filename))
        {
            m_Translator.load(filename.c_str());
            m_App.installTranslator(&m_Translator);
        }
	}
}
