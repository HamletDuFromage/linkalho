#include "custom_theme.hpp"

brls::Theme CustomTheme::custom_theme()
{
    brls::Theme theme = brls::Theme();

    #define CUSTOM_LIGHT theme.colors[brls::ThemeVariant_LIGHT]
    #define CUSTOM_DARK theme.colors[brls::ThemeVariant_DARK]

    // Light variant
    CUSTOM_LIGHT.backgroundColor[0] = 0.922f;
    CUSTOM_LIGHT.backgroundColor[1] = 0.922f;
    CUSTOM_LIGHT.backgroundColor[2] = 0.922f;
    CUSTOM_LIGHT.backgroundColorRGB = nvgRGB(235, 235, 235);

    CUSTOM_LIGHT.textColor        = nvgRGB(51, 51, 51);
    CUSTOM_LIGHT.descriptionColor = nvgRGB(140, 140, 140);

    CUSTOM_LIGHT.notificationTextColor = nvgRGB(255, 255, 255);
    CUSTOM_LIGHT.backdropColor         = nvgRGBA(0, 0, 0, 178);

    CUSTOM_LIGHT.separatorColor = nvgRGB(45, 45, 45);

    CUSTOM_LIGHT.sidebarColor          = nvgRGB(240, 240, 240);
    CUSTOM_LIGHT.activeTabColor        = nvgRGB(49, 79, 235);
    CUSTOM_LIGHT.sidebarSeparatorColor = nvgRGB(208, 208, 208);

    CUSTOM_LIGHT.highlightBackgroundColor = nvgRGB(252, 255, 248);
    CUSTOM_LIGHT.highlightColor1          = nvgRGB(13, 182, 213);
    CUSTOM_LIGHT.highlightColor2          = nvgRGB(80, 239, 217);

    CUSTOM_LIGHT.listItemSeparatorColor  = nvgRGB(207, 207, 207);
    CUSTOM_LIGHT.listItemValueColor      = nvgRGB(43, 81, 226);
    CUSTOM_LIGHT.listItemFaintValueColor = nvgRGB(181, 184, 191);

    CUSTOM_LIGHT.tableEvenBackgroundColor = nvgRGB(240, 240, 240);
    CUSTOM_LIGHT.tableBodyTextColor       = nvgRGB(131, 131, 131);

    CUSTOM_LIGHT.dropdownBackgroundColor = nvgRGBA(0, 0, 0, 178);

    CUSTOM_LIGHT.nextStageBulletColor = nvgRGB(165, 165, 165);

    CUSTOM_LIGHT.spinnerBarColor = nvgRGBA(131, 131, 131, 102);

    CUSTOM_LIGHT.headerRectangleColor = nvgRGB(127, 127, 127);

    CUSTOM_LIGHT.buttonPlainEnabledBackgroundColor  = nvgRGB(255, 59, 0);
    CUSTOM_LIGHT.buttonPlainDisabledBackgroundColor = nvgRGB(136, 90, 75);
    CUSTOM_LIGHT.buttonPlainEnabledTextColor        = nvgRGB(255, 247, 255);
    CUSTOM_LIGHT.buttonPlainDisabledTextColor       = nvgRGB(167, 129, 118);

    CUSTOM_LIGHT.dialogColor                = nvgRGB(240, 240, 240);
    CUSTOM_LIGHT.dialogBackdrop             = nvgRGBA(0, 0, 0, 100);
    CUSTOM_LIGHT.dialogButtonColor          = nvgRGB(46, 78, 255);
    CUSTOM_LIGHT.dialogButtonSeparatorColor = nvgRGB(210, 210, 210);

    // Dark variant
    CUSTOM_DARK.backgroundColor[0] = 0.176f;
    CUSTOM_DARK.backgroundColor[1] = 0.176f;
    CUSTOM_DARK.backgroundColor[2] = 0.176f;
    CUSTOM_DARK.backgroundColorRGB = nvgRGB(45, 45, 45);

    CUSTOM_DARK.textColor        = nvgRGB(255, 255, 255);
    CUSTOM_DARK.descriptionColor = nvgRGB(163, 163, 163);

    CUSTOM_DARK.notificationTextColor = nvgRGB(255, 255, 255);
    CUSTOM_DARK.backdropColor         = nvgRGBA(0, 0, 0, 178);

    CUSTOM_DARK.separatorColor = nvgRGB(255, 255, 255);

    CUSTOM_DARK.sidebarColor          = nvgRGB(50, 50, 50);
    CUSTOM_DARK.activeTabColor        = nvgRGB(0, 255, 204);
    CUSTOM_DARK.sidebarSeparatorColor = nvgRGB(81, 81, 81);

    CUSTOM_DARK.highlightBackgroundColor = nvgRGB(31, 34, 39);
    CUSTOM_DARK.highlightColor1          = nvgRGB(25, 138, 198);
    CUSTOM_DARK.highlightColor2          = nvgRGB(137, 241, 242);

    CUSTOM_DARK.listItemSeparatorColor  = nvgRGB(78, 78, 78);
    CUSTOM_DARK.listItemValueColor      = nvgRGB(88, 195, 169);
    CUSTOM_DARK.listItemFaintValueColor = nvgRGB(93, 103, 105);

    CUSTOM_DARK.tableEvenBackgroundColor = nvgRGB(57, 58, 60);
    CUSTOM_DARK.tableBodyTextColor       = nvgRGB(155, 157, 156);

    CUSTOM_DARK.dropdownBackgroundColor = nvgRGBA(0, 0, 0, 178); // TODO: 178 may be too much for dark theme

    CUSTOM_DARK.nextStageBulletColor = nvgRGB(165, 165, 165);

    CUSTOM_DARK.spinnerBarColor = nvgRGBA(131, 131, 131, 102); // TODO: get this right

    CUSTOM_DARK.headerRectangleColor = nvgRGB(160, 160, 160);

    CUSTOM_DARK.buttonPlainEnabledBackgroundColor  = nvgRGB(255, 59, 0);
    CUSTOM_DARK.buttonPlainDisabledBackgroundColor = nvgRGB(136, 90, 75);
    CUSTOM_DARK.buttonPlainEnabledTextColor        = nvgRGB(255, 247, 255);
    CUSTOM_DARK.buttonPlainDisabledTextColor       = nvgRGB(167, 129, 118);

    CUSTOM_DARK.dialogColor                = nvgRGB(70, 70, 70);
    CUSTOM_DARK.dialogBackdrop             = nvgRGBA(0, 0, 0, 100);
    CUSTOM_DARK.dialogButtonColor          = nvgRGB(3, 251, 199);
    CUSTOM_DARK.dialogButtonSeparatorColor = nvgRGB(103, 103, 103);

    return theme;
}