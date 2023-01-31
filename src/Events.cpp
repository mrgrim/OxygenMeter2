#pragma once
#include "Events.h"
#include "oxyMeter.h"
#include "Settings.h"
#include "RE/U/UI.h"
#include "string.h"

MenuOpenCloseEventHandler* MenuOpenCloseEventHandler::GetSingleton()
{
	static MenuOpenCloseEventHandler singleton;
	return std::addressof(singleton);
}

void MenuOpenCloseEventHandler::Register()
{
	auto ui = RE::UI::GetSingleton();
	ui->AddEventSink(GetSingleton());
}

RE::BSEventNotifyControl MenuOpenCloseEventHandler::ProcessEvent(const RE::MenuOpenCloseEvent* a_event, RE::BSTEventSource<RE::MenuOpenCloseEvent>*)
{
	// from ersh TrueHud pretty much verbatim

	using ContextID = RE::UserEvents::INPUT_CONTEXT_ID;
	// On HUD menu open/close - open/close the plugin's HUD menu
	if (a_event && a_event->menuName == RE::HUDMenu::MENU_NAME) {
		if (a_event->opening) {
			oxygenMenu::Show();
		} else {
			oxygenMenu::Hide();
		}
	}

	// Hide the widgets when a menu is open
	auto controlMap = RE::ControlMap::GetSingleton();
	if (controlMap) {
		auto& priorityStack = controlMap->contextPriorityStack;
		if (priorityStack.empty()) {
			oxygenMenu::SetMenuVisibilityMode(oxygenMenu::MenuVisibilityMode::kHidden);
		} 
		else if (priorityStack.back() == ContextID::kGameplay ||
				 priorityStack.back() == ContextID::kFavorites ||
				 priorityStack.back() == ContextID::kConsole) 
		{
			oxygenMenu::SetMenuVisibilityMode(oxygenMenu::MenuVisibilityMode::kVisible);
		} else {
			oxygenMenu::SetMenuVisibilityMode(oxygenMenu::MenuVisibilityMode::kHidden);
		}
	}

	return RE::BSEventNotifyControl::kContinue;
}
