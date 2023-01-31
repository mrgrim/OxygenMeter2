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
		constexpr auto path = L"Data/SKSE/Plugins/OxygenMeter2.ini";

		CSimpleIniA ini;
		ini.SetUnicode();

		ini.LoadFile(path);

		ini::get_value(ini, fadeWhenDrowning, "Settings", "Fade out when drowning", ";Oxygen meter fades out when you run out of oxygen and your health starts decreasing");
		ini::get_value(ini, flashWhenBelow, "Settings", "Flash meter when air level below", ";Oxygen meter starts to flash when under this percentage of total air, default is 50");
		ini::get_value(ini, widget_colour, "Colour", "Widget Bar Colour", ";The colour of the widget bar, default is 0x51CCCC");
		ini::get_value(ini, widget_flashcolour, "Colour", "Widget Flash Colour", ";The colour of the flash effect around the widget, default is 0x51CCCC");
		ini::get_value(ini, widget_xpos, "Position", "Widget X Position", ";The X Position for the widget, default is 961.000000");
		ini::get_value(ini, widget_ypos, "Position", "Widget Y Position", ";The Y Position for the widget, default is 1040.000000");
		ini::get_value(ini, widget_rotation, "Position", "Widget Rotation", ";The rotation for the widget, default is 0.000000");
		ini::get_value(ini, widget_xscale, "Position", "Widget X scale", ";The X scale of the widget, default is 75.000000");
		ini::get_value(ini, widget_yscale, "Position", "Widget Y scale", ";The Y scale of the widget, default is 75.000000");

		ini.SaveFile(path);
	}

	bool fadeWhenDrowning{ false };
	float flashWhenBelow{ 50.0f };
	std::uint32_t widget_colour{ 0x51CCCC };
	std::uint32_t widget_flashcolour{ 0x51CCCC };
	float widget_xpos{ 961.0f };
	float widget_ypos{ 1040.0f };
	float widget_rotation{ 0.0f };
	float widget_xscale{ 75.0f };
	float widget_yscale{ 75.0f };

private:
};
