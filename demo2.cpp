#include <iostream>
#include <gtkmm-3.0/gtkmm.h>
#include "domino.h"

#define CONNECT(signal, func) \
    signal().connect(sigc::mem_fun(*this, &func))

typedef ::Cairo::RefPtr<::Cairo::Context> CairoContext;


// ---------------- DATA -------------------

class MyData {
public:
    int win_width = 640;
    int win_height = 480;

    int m_mouse_button_num_pressed = 0;

    Domino activeDomino;        
    bool dominoClicked = false;
    double lastMouseX = 0;
    double lastMouseY = 0;
};


// ---------------- MAIN WINDOW -------------

class MainWindow {
public:
    Gtk::Window m_window;
    Gtk::VBox m_vbox1;
    Gtk::DrawingArea m_darea;

    MyData* m_my = nullptr;

    MainWindow(MyData& my)
    {
        m_my = &my;

        m_window.set_title("Demo 2");
        m_window.set_default_size(my.win_width, my.win_height);

        m_window.add(m_vbox1);
        m_vbox1.pack_start(m_darea, true, true);

        // CONNECT DRAW
        CONNECT(m_darea.signal_draw, MainWindow::darea_on_draw);

        // Mouse events
        m_darea.set_events(
            Gdk::BUTTON_PRESS_MASK |
            Gdk::BUTTON_RELEASE_MASK |
            Gdk::POINTER_MOTION_MASK
        );

        CONNECT(m_darea.signal_button_press_event, MainWindow::darea_on_button_press);
        CONNECT(m_darea.signal_button_release_event, MainWindow::darea_on_button_release);
        CONNECT(m_darea.signal_motion_notify_event, MainWindow::darea_on_motion_notify);

        m_window.show_all();
    }

    void repaint() {
        m_darea.queue_draw();
    }


    // ---------------- DRAW --------------------

    bool darea_on_draw(const CairoContext& cr)
    {
        m_my->activeDomino.draw(cr);
        return true;
    }


    // ----------------- MOUSE PRESS ------------

    bool darea_on_button_press(GdkEventButton* event)
    {
        m_my->m_mouse_button_num_pressed = event->button;

        // check click inside domino
        m_my->dominoClicked =
            m_my->activeDomino.domino_is_clicked(event->x, event->y);

        m_my->lastMouseX = event->x;
        m_my->lastMouseY = event->y;

        return true;
    }

    // ----------------- MOUSE RELEASE ----------

    bool darea_on_button_release(GdkEventButton* event)
    {
        if (m_my->dominoClicked &&
            m_my->activeDomino.rivet_is_clicked(event->x, event->y))
        {
            m_my->activeDomino.rotation =
                (m_my->activeDomino.rotation + 90) % 360;

            repaint();
        }

        m_my->dominoClicked = false;
        m_my->m_mouse_button_num_pressed = 0;
        return true;
    }


    // ----------------- MOUSE DRAG --------------

    bool darea_on_motion_notify(GdkEventMotion* event)
    {
        if (m_my->dominoClicked)
        {
            double dx = event->x - m_my->lastMouseX;
            double dy = event->y - m_my->lastMouseY;

            m_my->activeDomino.posX += dx;
            m_my->activeDomino.posY += dy;

            m_my->lastMouseX = event->x;
            m_my->lastMouseY = event->y;

            repaint();
        }

        return true;
    }
};


// ------------------ MAIN ---------------------

int main(int argc, char** argv)
{
    Gtk::Main kit(argc, argv);

    MyData my;
    MainWindow win(my);

    kit.run(win.m_window);
    return 0;
}
