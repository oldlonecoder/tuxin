//#include "tuxin/tools/book.h"

//-------------------------------------
//#include "tuxin/tools/sscan.h"
//#include "tuxin/est/expression.h"
//#include "tuxin/tui/events.h"
//#include "tuxin/tools/application.h"
//=====================================
#include "tuxin/tui/globals.h"
#include "tuxin/tui/input_track.h"
#include "tuxin/tui/application.h"
#include "tuxin/tui/window.h"
#include "tuxin/tui/statusbar.h"
#include <unistd.h>

namespace tuxin::ui
{
class app : public application
{

    intrack*        intrack_ptr{nullptr};
    ui::statusbar*  statusbar{nullptr};
    window*         desk{nullptr};
    window*         C64Win{nullptr};
public:

    app(const std::string& app_name, int argc, char **argv);
    ~app() override;
    book::code run() override;
    book::code terminate() override;
protected:
    book::code setup() override;
    book::action terminal_resize_signal(rectangle _r) const;
    book::code setup_ui() override;
};


app::app(const std::string& app_name, int argc, char **argv): application(app_name,argc,argv)
{}

app::~app()
{

}

book::code app::run()
{

    try
    {
        setup();
        setup_ui();
        book::debug() << book::fn::fun << "setup:";

        // - loop here ...
        book::code c{book::code::rejected};

        while(c != book::code::cancel)      //  ESC return "cancel"
        {
            event ev; // new event .
            c = event::get_stdin_event(ev);
            if(c != book::code::cancel)
                c = intrack_ptr->update_event_data(ev);
        }

        return book::code::terminate;
    }
    catch(book::exception& e)
    {
        book::except() << "terminate...";
        return book::code::rejected;
    }
}


book::code app::setup()
{
    //...
    application::setup(); // install signals and init book logs; nothig more to do for now.
    book::debug() << book::fn::fun << "setup base application:";
    book::out() << "starting the terminal:";
    terminal::begin();
    terminal::resize_signal().Connect(this, &app::terminal_resize_signal);
    //...
    book::out() << book::code::done;
    return book::code::complete;
}

book::action app::terminal_resize_signal(rectangle _r) const
{
    //...
    book::test() << book::fn::fun << color::blueviolet << " new terminal geometry: " << color::yellow << _r << color::reset;
    desk->resize(_r.dwh);
    desk->redraw();
    C64Win->redraw();

    return book::action::continu;
}

book::code app::setup_ui()
{
    desk = new window{"Desktop Window",0};
    desk->set_theme("Default");
    desk->set_geometry({{1,1},terminal::geometry().dwh});
    desk->set_anchor(0); //globals::anchor::width_fit|globals::anchor::height_fit);
    desk->emplace();
    desk->redraw();
    auto painter = desk->begin_paint();
    painter.clear();
    painter.to({1,1}) << "[Desktop Window!]";
    desk->end_paint(painter);
    statusbar = new ui::statusbar(desk,"statusbar");
    statusbar->set_theme("C64");
    statusbar->setup_ui();
    statusbar->draw();
    // painter = statusbar->begin_paint();
    // painter.clear();
    // painter <<"[statusbar]";
    // statusbar->end_paint(painter);

    intrack_ptr = new intrack{this->statusbar, "Mouse Track"};
    intrack_ptr->set_theme("C64");
    intrack_ptr->setup_ui();
    painter = intrack_ptr->begin_paint();
    painter.clear();
    painter << "input tracking here";
    intrack_ptr->end_paint(painter);

    C64Win = new window{"C64 Window", globals::uistyle::Frame|globals::uistyle::statusbar};
    C64Win->set_theme("C64");
    C64Win->set_geometry({{2,2}, ui::size{88,28}});
    C64Win->setup_ui();
    C64Win->draw();
    painter = C64Win->begin_paint();
    painter.to({5,3}) ;
    painter << "This is the C64 theme";

    C64Win->end_paint(painter);
    return book::code::done;
}

book::code app::terminate()
{
    book::debug() << book::fn::fun << "terminate application:";
    application::terminate();
    book::out() << "As long as tuxin::ui::application is not derived from object, we delete our stuff here:";
    delete desk;
    delete C64Win;
    // -----------------------------------------------------------------------------------------------------
    terminal::end();
    book::purge(nullptr);
    return book::code::terminate;
}


}// namespace tuxin::ui



auto main(int argc, char** argv)->int
{
    tuxin::string str = "hello, and welcome to the tuxin API; ...";
    std::cout << str() << std::endl;
    tuxin::ui::app app{"tuxin tddv application", argc, argv};
    app.run();
    app.terminate();
    return 0;
}
