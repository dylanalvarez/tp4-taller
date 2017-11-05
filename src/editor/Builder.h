#ifndef TP4_TALLER_BUILDER_H
#define TP4_TALLER_BUILDER_H


#include <gtkmm/builder.h>

class Builder {
public:
    explicit Builder(Glib::RefPtr<Gtk::Builder> &builder) : builder(builder) {}

    template<class T_Widget>
    void get_widget(const Glib::ustring &name, T_Widget *&widget) {
        builder->get_widget(name, widget);
    }

    template<typename T_Widget, typename... Args>
    void get_widget_derived(const Glib::ustring &name, T_Widget *&widget,
                            Args &&... args) {
        builder->get_widget_derived(name, widget);
        widget->init(args...);
    }

private:
    Glib::RefPtr<Gtk::Builder> builder;
};


#endif //TP4_TALLER_BUILDER_H
