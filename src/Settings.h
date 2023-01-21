#pragma once

class Settings
{
public:
	[[nodiscard]] static Settings* GetSingleton()
	{
		static Settings singleton;
		return std::addressof(singleton);
	}

	void Load()
	{
		constexpr auto path = L"Data/SKSE/Plugins/po3_OxygenMeter2.ini";

		CSimpleIniA ini;
		ini.SetUnicode();

		ini.LoadFile(path);

		//detail::get_value(ini, useLeftMeter, "Settings", "Meter placement", ";Oxygen Meter position. 0 - Right, 1 - Left");
		ini::get_value(ini, fadeWhenDrowning, "Settings", "Fade out when drowning", ";Oxygen meter fades out when you run out of oxygen and your health starts decreasing");
		ini::get_value(ini, flashWhenBelow, "Settings", "Flash meter when air level below", ";Oxygen meter starts to flash when under this percentage of total air, default is 50");
		ini::get_value(ini, widget_colour, "Widget", "Widget Bar Colour", ";The colour of the widget bar");
		ini::get_value(ini, widget_flashcolour, "Widget", "Widget Flash Colour", ";The colour of the flash effect around the widget");
		ini::get_value(ini, widget_xpos, "Widget", "Widget X Position", ";The X Position for the widget, default is 961.000000");
		ini::get_value(ini, widget_ypos, "Widget", "Widget Y Position", ";The Y Position for the widget, default is 1040.000000");
		ini::get_value(ini, widget_rotation, "Widget", "Widget Rotation", ";The rotation for the widget, default is 0.000000");
		ini::get_value(ini, widget_xscale, "Widget", "Widget X scale", ";The X scale of the widget, default is 75.000000");
		ini::get_value(ini, widget_yscale, "Widget", "Widget Y scale", ";The Y scale of the widget, default is 75.000000");

		ini.SaveFile(path);
	}

	std::uint32_t useLeftMeter{ 0 };
	bool fadeWhenDrowning{ true };
	float flashWhenBelow{ 50.0f };
	std::uint32_t widget_colour{ 0xc076e8 };
	std::uint32_t widget_flashcolour{ 0xc076e8 };
	float widget_xpos{ 961.0f };
	float widget_ypos{ 1040.0f };
	float widget_rotation{ 0.0f };
	float widget_xscale{ 75.0f };
	float widget_yscale{ 75.0f };

private:
};
