

#include "tuxin/tools/colors.h"
#include <sys/epoll.h>
#include <unistd.h>
#include "tuxin/tui/globals.h"

namespace tuxin::globals::colors
{



attr_db::themes attr_db::s_data = 
{
    {
        "Default",
        {
            {
                "Widget",
                {
                    {wstate::Active, {color::grey100, color::grey27}},
                    {wstate::Disable, {color::grey30, color::grey35}}, // keep coherance with widget base
                    {wstate::Normal, {color::grey70, color::grey27}},
                    {wstate::Focus, {color::red4, color::grey27}}
                    //...
                }
            },
            {
                "Frame",
                {
                    {wstate::Active, {color::lightcyan3, color::darkblue}},
                    {wstate::Disable, {color::grey30, color::darkblue}}, // keep coherance with widget base
                    {wstate::Normal, {color::grey100, color::darkblue}},
                    {wstate::Focus, {color::greenyellow, color::darkblue}}
                    //...
                }
            },
            {
                "Label",
                {
                    {wstate::Active, {color::indianred, color::blue}},
                    {wstate::Disable, {color::grey19, color::grey35}}, // Keep coherance with widget base
                    {wstate::Normal, {color::grey70, color::blue}}, // Keep coherance with widget base
                    {wstate::Focus, {color::yellow, color::blue}}
                }
            },
            {
                "Shortkey",
                {
                    {wstate::Active, {color::hotpink4, color::grey27}},
                    {wstate::Disable, {color::grey19, color::grey35}}, // Keep coherance with widget base
                    {wstate::Normal, {color::grey70, color::grey27}},
                    {wstate::Focus, {color::red4, color::grey27}}
                }
            },
            {
                "Icon",
                {
                    {wstate::Active, {color::blue1, color::grey27}}, // Keep coherance with widget base
                    {wstate::Disable, {color::grey19, color::grey35}},
                    {wstate::Normal, {color::blue1, color::grey35}},
                    {wstate::Focus, {color::aquamarine3, color::grey27}},
                    {wstate::Success, {color::green5, color::grey27}}
                }
            },
            {
                "Input-Area", // widget::text_input
                {
                    {wstate::Active, {color::white, color::grey30}}, // Keep coherance with widget base
                    {wstate::Disable, {color::grey39, color::grey35}},
                    {wstate::Normal, {color::grey37, color::grey30}},
                    {wstate::Focus, {color::white, color::grey30}}
                }
            },
            {
                "Input-Field",
                {
                    {wstate::Active, {color::grey70, color::grey27}}, // Keep coherance with widget base
                    {wstate::Disable, {color::grey39, color::grey35}},
                    {wstate::Normal, {color::grey70, color::grey27}},
                    {wstate::Focus, {color::white, color::grey27}}
                },
            },
            {
                "Input-Field:Placeholder",
                {
                    {wstate::Active, {color::darkcyan, color::grey27}}, // Keep coherance with widget base
                    {wstate::Disable, {color::blue, color::grey27}},
                    {wstate::Normal, {color::blue, color::grey27}},
                    {wstate::Focus, {color::blue, color::grey27}}
                }
            },
            {
                "StatusBar",
                {
                    {wstate::Active, {color::lime,      color::grey27}},
                    {wstate::Disable, {color::grey30,   color::grey27}}, // Keep coherance with widget base
                    {wstate::Normal, {color::grey70,    color::grey27}},
                    {wstate::Focus, {color::red4,       color::grey27}}
                  //...
                }
            }
        }
    },
    {
        "C64",
        {
            {
                "Widget",
                {
                    {wstate::Active, {color::darkturquoise, color::darkblue}},
                    {wstate::Disable, {color::grey30, color::darkblue}}, // Keep coherance with widget base
                    {wstate::Normal, {color::grey70, color::darkblue}},
                    {wstate::Focus, {color::red4, color::darkblue}}
                    //...
                }
            },
            {
                "Frame",
                {
                    {wstate::Active, {color::lightcyan3, color::darkblue}},
                    {wstate::Disable, {color::grey30, color::darkblue}}, // Keep coherance with widget base
                    {wstate::Normal, {color::grey100, color::darkblue}},
                    {wstate::Focus, {color::greenyellow, color::darkblue}}
                    //...
                }
            },
            {
                "Label",
                {
                    {wstate::Active, {color::lightcyan3, color::darkblue}},
                    {wstate::Disable, {color::grey19, color::grey35}}, // Keep coherance with widget base
                    {wstate::Normal, {color::grey70, color::darkblue}}, // Keep coherance with widget base
                    {wstate::Focus, {color::yellow, color::darkblue}}
                }
            },
            {
                "Shortkey",
                {
                    {wstate::Active, {color::hotpink4, color::darkblue}},
                    {wstate::Disable, {color::grey19, color::darkblue}}, // Keep coherance with widget base
                    {wstate::Normal, {color::grey70, color::darkblue}},
                    {wstate::Focus, {color::red4, color::darkblue}}
                }
            },
            {
                "Icon",
                {
                    {wstate::Active, {color::blue1, color::darkblue}}, // Keep coherance with widget base
                    {wstate::Disable, {color::grey19, color::darkblue}},
                    {wstate::Normal, {color::blue1, color::darkblue}},
                    {wstate::Focus, {color::aquamarine3, color::darkblue}},
                    {wstate::Success, {color::green5, color::darkblue}}
                }
            },
            {
                "Input-Area", // widget::text_input
                {
                    {wstate::Active, {color::white, color::blue}}, // Keep coherance with widget base
                    {wstate::Disable, {color::grey39, color::blue}},
                    {wstate::Normal, {color::grey37, color::blue}},
                    {wstate::Focus, {color::white, color::blue}}
                }
            },
            {
                "Input-Field",
                {
                    {wstate::Active, {color::lightcyan3, color::blue4}}, // Keep coherance with widget base
                    {wstate::Disable, {color::blue, color::darkblue}},
                    {wstate::Normal, {color::blue, color::darkblue}},
                    {wstate::Focus, {color::blue, color::darkblue}}
                },

            },
            {
                "Input-Field:Placeholder",
                {
                    {wstate::Active, {color::darkcyan, color::blue4}}, // Keep coherance with widget base
                    {wstate::Disable, {color::blue, color::darkblue}},
                    {wstate::Normal, {color::blue, color::darkblue}},
                    {wstate::Focus, {color::blue, color::darkblue}}
                },
            },
            {
                "StatusBar",
                {
                    {wstate::Active, {color::lime, color::blue4}},
                    {wstate::Disable, {color::grey30, color::blue4}}, // Keep coherance with widget base
                    {wstate::Normal, {color::grey70, color::blue4}},
                    {wstate::Focus, {color::red4, color::blue4}}
                      //...
                }
            }
        }
    },
    {
        "C128",
        {
            {
                "Widget",
                {
                    {wstate::Active, {color::darkseagreen, color::grey15}},
                    {wstate::Disable, {color::grey30, color::grey15}}, // Keep coherance with widget base
                    {wstate::Normal, {color::grey70, color::grey15}},
                    {wstate::Focus, {color::red4, color::grey15}}
                    //...
                }
            },
            {
                "Frame",
                {
                    {wstate::Active, {color::darkseagreen, color::grey15}},
                    {wstate::Disable, {color::grey30, color::grey15}}, // Keep coherance with widget base
                    {wstate::Normal, {color::lightcyan3, color::grey15}},
                    {wstate::Focus, {color::greenyellow, color::grey15}}
                    //...
                }
            },
            {
                "Label",
                {
                    {wstate::Active, {color::darkseagreen4, color::grey15}},
                    {wstate::Disable, {color::grey19, color::grey35}}, // Keep coherance with widget base
                    {wstate::Normal, {color::grey70, color::darkblue}}, // Keep coherance with widget base
                    {wstate::Focus, {color::yellow, color::darkblue}}
                }
            },
            {
                "Shortkey",
                {
                    {wstate::Active, {color::hotpink4, color::darkblue}},
                    {wstate::Disable, {color::grey19, color::darkblue}}, // Keep coherance with widget base
                    {wstate::Normal, {color::grey70, color::darkblue}},
                    {wstate::Focus, {color::red4, color::darkblue}}
                }
            },
            {
                "Icon",
                {
                    {wstate::Active, {color::blue1, color::darkblue}}, // Keep coherance with widget base
                    {wstate::Disable, {color::grey19, color::darkblue}},
                    {wstate::Normal, {color::blue1, color::darkblue}},
                    {wstate::Focus, {color::aquamarine3, color::darkblue}},
                    {wstate::Success, {color::green5, color::darkblue}}
                }
            },
            {
                "Input-Area", // widget::text_input
                {
                    {wstate::Active, {color::darkseagreen, color::grey15}}, // Keep coherance with widget base
                    {wstate::Disable, {color::darkseagreen, color::grey15}},
                    {wstate::Normal, {color::darkseagreen, color::grey15}},
                    {wstate::Focus, {color::darkseagreen, color::grey15}}
                }
            },
            {
                "Input-Field",
                {
                    {wstate::Active, {color::darkseagreen, color::grey11}}, // Keep coherance with widget base
                    {wstate::Disable, {color::darkseagreen, color::grey15}},
                    {wstate::Normal, {color::darkseagreen, color::grey15}},
                    {wstate::Focus, {color::darkseagreen, color::grey15}}
                }
            },
            {
                "Input-Field:Placeholder",
                {
                    {wstate::Active, {color::grey23, color::grey11}}, // Keep coherance with widget base
                    {wstate::Disable, {color::darkseagreen, color::grey15}},
                    {wstate::Normal, {color::darkseagreen, color::grey15}},
                    {wstate::Focus, {color::darkseagreen, color::grey15}}
                }
            },
            {
                "StatusBar",
                {
                    {wstate::Active, {color::lime, color::grey15}},
                    {wstate::Disable, {color::grey30, color::grey15}}, // Keep coherance with widget base
                    {wstate::Normal, {color::grey70, color::grey15}},
                    {wstate::Focus, {color::red4, color::grey15}}
                    //...
                }
            }
        }
    }
};


attr_db::themes::iterator attr_db::get_theme(std::string_view Tname)
{
    auto it = attr_db::s_data.begin();
    auto it_end = attr_db::s_data.end();
    while (it != it_end)
    {
        if (it->first == Tname) break;
        ++it;
    }
    // ReSharper disable once CppDFALocalValueEscapesFunction
    return it;
}


bool attr_db::end(attr_db::themes::iterator it)
{
    return it == attr_db::s_data.end();
}

attr_db::themes &tuxin::globals::colors::attr_db::theme()
{
    return attr_db::s_data;
}

}
