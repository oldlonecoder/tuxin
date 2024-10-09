

#include "tuxin/tui/application.h"
#include "tuxin/tui/terminal.h"
#include <csignal>
#include <memory>


namespace tuxin::ui
{

application* application::_app_{nullptr};








application::application(const std::string& a_id, int argc, char** argv): _app_name_(a_id)
{
    if(argc && argv)
        tuxin::string::string_view_list(argc,argv);

    if(application::_app_ == nullptr)
    {
        application::_app_ = this;
    }
    else
        abort();
}


application::~application()
{
    //...
    _args_.clear();
    ///...
}


void application::sig_interrupted(int)
{
    book::interrupted();
    //terminal::end();
    //book::purge(nullptr);
    application::app().terminate();
    exit(0);
}

void application::sig_aborted(int)
{
    book::aborted();
    //terminal::end();
    //book::purge(nullptr);
    application::app().terminate();
    exit(0);
}

void application::sig_crash(int)
{
    book::segfault();
    //terminal::end();
    //book::purge(nullptr);
    application::app().terminate();
    exit(0);
}

void application::sig_winch(int)
{
    book::message() << book::fn::fun << "terminal window resize signal.";
    terminal::query_size();
    // Propagate term_resize_event signal.
    //...
}


book::code application::terminate()
{
    return book::code::implemented;
}

application& application::app()
{
    if(!application::_app_)
        throw book::exception() [book::except() << book::fn::fun << book::fn::endl << " no instance of application!"];

    return *application::_app_;
}

desktop *application::screen_desktop()
{
    return desktop::instance();
}

book::code application::install_signals()
{

    std::signal(SIGSEGV, &application::sig_crash);
    std::signal(SIGABRT, &application::sig_aborted);
    std::signal(SIGINT, &application::sig_interrupted);
    std::signal(SIGWINCH, &application::sig_winch);
    return book::code::done;
}

book::code application::setup()
{
    //...
    book::init();
    install_signals();
    //...
    return book::code::done;
}


}
