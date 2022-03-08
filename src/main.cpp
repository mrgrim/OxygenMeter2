#include "Settings.h"
#include "SKSE/API.h"
#include "oxyMeter.h"
#include "Events.h"

const SKSE::MessagingInterface* g_messaging = nullptr;
const SKSE::LoadInterface* g_LoadInterface = nullptr;
const SKSE::QueryInterface* g_QueryInterface = nullptr;

static void SKSEMessageHandler(SKSE::MessagingInterface::Message* message)
{
	switch (message->type) {
	case SKSE::MessagingInterface::kDataLoaded:
		oxygenMenu::Register();
		MenuOpenCloseEventHandler::Register();
		break;

	case SKSE::MessagingInterface::kNewGame:
		oxygenMenu::Show();
		break;

	case SKSE::MessagingInterface::kPostLoadGame:
		oxygenMenu::Show();
		break;
	}
}

extern "C" DLLEXPORT constinit auto SKSEPlugin_Version = []() {
	SKSE::PluginVersionData v;
	v.PluginVersion(Version::MAJOR);
	v.PluginName("Oxygen Meter 2");
	v.AuthorName("powerofthree and OsmosisWrench");
	v.UsesAddressLibrary(true);
	v.CompatibleVersions({ SKSE::RUNTIME_LATEST });

	return v;
}();

void InitializeLog()
{
	auto path = logger::log_directory();
	if (!path) {
		stl::report_and_fail("Failed to find standard logging directory"sv);
	}

	*path /= fmt::format(FMT_STRING("{}.log"), Version::PROJECT);
	auto sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true);

	auto log = std::make_shared<spdlog::logger>("global log"s, std::move(sink));

	log->set_level(spdlog::level::info);
	log->flush_on(spdlog::level::info);

	spdlog::set_default_logger(std::move(log));
	spdlog::set_pattern("[%H:%M:%S:%e] %v"s);

	logger::info(FMT_STRING("{} v{}"), Version::PROJECT, Version::NAME);
}

extern "C" DLLEXPORT bool SKSEAPI SKSEPlugin_Load(const SKSE::LoadInterface* a_skse)
{
	InitializeLog();

	logger::info("loaded plugin");

	SKSE::Init(a_skse);

	Settings::GetSingleton()->Load();

	g_messaging = SKSE::GetMessagingInterface();
	if (!g_messaging) {
		logger::critical("Failed to load messaging interface! This error is fatal, plugin will not load.");
		return false;
	}

	//OxygenMeter::Install();

	g_messaging->RegisterListener("SKSE", SKSEMessageHandler);

	return true;
}
