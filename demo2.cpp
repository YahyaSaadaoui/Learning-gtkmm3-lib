#include <iostream>
#include <gtkmm-3.0/gtkmm.h>
#include "domino.h"

#define CONNECT(signal, func) \
    signal().connect( sigc::mem_fun(*this, &func) )

typedef ::Cairo::RefPtr<::Cairo::Context> CairoContext;



class MyData {

public:
    int windowWidth = 640;
    int windowHeight = 480;
    int mousePressedButton = 0;
    int rectangleToggle = 1;
    bool isDominoBeingDragged = false;
    int rectWidth = 80;
    int rectHeight = 120;
    int circleX = 500;
    int circleY = 300;
    int circleRadius = 80;
    Domino activeDomino;
    bool dominoClicked = false;
    double lastMouseX = 0;
    double lastMouseY = 0;
};

class MainWindow {
public:
    Gtk::Window m_window;
    Gtk::VBox m_vbox1;
    Gtk::HBox m_hbox1;
    Gtk::Button m_button_quit {"Quit"};
    Gtk::Button m_button_click_me {"Cliquez-moi"};
    Gtk::Button m_button_modif {"Modification"};
    Gtk::Frame m_frame1;
    Gtk::DrawingArea m_darea;
    MyData *m_my = nullptr;

    MainWindow (MyData& my)
    {
        m_my = &my;

        m_window.set_title ("Demo 1");
        m_window.set_size_request (my.windowWidth, my.windowHeight);
        m_window.add (m_vbox1);
        m_vbox1.pack_start (m_hbox1, false, false, 5);

        m_hbox1.pack_start (m_button_click_me, false, false, 5);
        CONNECT (m_button_click_me.signal_clicked, 
            MainWindow::button_click_me_on_clicked);
            
        m_hbox1.pack_end (m_button_quit, false, false, 5);
        CONNECT (m_button_quit.signal_clicked, 
            MainWindow::button_quit_on_clicked);
               
        m_hbox1.pack_start (m_button_modif, false, false, 5);
        CONNECT (m_button_modif.signal_clicked, 
            MainWindow::button_modif_on_clicked);
     
        m_vbox1.pack_start (m_frame1, true, true, 2);
        m_frame1.set_border_width (2);
        m_frame1.add (m_darea);
        CONNECT (m_darea.signal_draw, MainWindow::darea_on_draw);

        m_darea.set_events (Gdk::BUTTON_PRESS_MASK |
                            Gdk::BUTTON_RELEASE_MASK |
                            Gdk::POINTER_MOTION_MASK |
                            Gdk::SCROLL_MASK );

        CONNECT (m_darea.signal_button_press_event,
            MainWindow::darea_on_button_press);
        CONNECT (m_darea.signal_button_release_event,
            MainWindow::darea_on_button_release);
        CONNECT (m_darea.signal_motion_notify_event,
            MainWindow::darea_on_motion_notify);
        CONNECT (m_darea.signal_scroll_event,
            MainWindow::darea_on_scroll);
        CONNECT (m_darea.signal_size_allocate,
            MainWindow::darea_on_size_allocate);

        m_darea.set_can_focus (true);
        m_darea.grab_focus();
        CONNECT (m_darea.signal_key_press_event,
            MainWindow::darea_on_key_press);

        m_window.show_all();
    }

    void repaint_darea()
    {
        m_darea.queue_draw();
    }

    void button_quit_on_clicked()
    {
        Gtk::Main::quit();
    }

    void button_click_me_on_clicked()
    {
        m_my->rectangleToggle = !m_my->rectangleToggle;
        repaint_darea();
    }
    
    void button_modif_on_clicked()
    {
        int temp = m_my->rectWidth;
        m_my->rectWidth = m_my->rectHeight;
        m_my->rectHeight = temp;
        repaint_darea();
    }

    bool darea_on_draw (const CairoContext& cr)
    {
        std::cout << __func__ << " " << std::endl;
        
        m_my->activeDomino.draw(cr);
        
        cr->set_line_width (3);
        cr->move_to (500, 30);
        cr->line_to (600, 100);
        cr->line_to (450, 140);
        cr->close_path();
        cr->set_source_rgb (1.0, 0, 1.0);
        cr->stroke();

        cr->set_line_width (1);
        cr->rectangle (100, 120, 250, 180);
        cr->set_source_rgb (0.0, 0.0, 1.0);
        cr->stroke();

        cr->rectangle (80, 250, 100, 120);
        cr->set_source_rgb (1.0, 0.7, 0.7);
        cr->fill();

        if (m_my->rectangleToggle) {
            cr->rectangle (300, 150, m_my->rectWidth, m_my->rectHeight);
            cr->set_source_rgb (0.7, 1.0, 0.7);
            cr->fill_preserve();
            cr->set_source_rgb (0.0, 0.0, 0.0);
            cr->stroke();
        }

        cr->set_line_width (2);
        cr->arc (m_my->circleX, m_my->circleY, m_my->circleRadius,
                 0, PI * 2.0);
        cr->set_source_rgb (0.9, 0.9, 0.9);
        cr->fill_preserve();
        cr->set_source_rgb (0.5, 0.5, 0.5);
        cr->stroke();

        cr->set_font_size (20);
        cr->move_to (40, 60);
        cr->set_source_rgb (0.82, 0.41, 0.12);
        cr->show_text ("Some drawings:");
        cr->stroke();

        return true;
    }

    bool darea_on_button_press (GdkEventButton *event)
    {
        std::cout << __func__ << " " << event->button << " " <<
            event->x << " " << event->y << std::endl;

        m_darea.grab_focus();
        m_my->mousePressedButton = event->button;
        m_my->dominoClicked = 
            m_my->activeDomino.domino_is_clicked(event->x, event->y);
        m_my->lastMouseX = event->x;
        m_my->lastMouseY = event->y;
        return true;
    }

    bool darea_on_button_release (GdkEventButton *event)
    {
        if (m_my->dominoClicked &&
            m_my->activeDomino.rivet_is_clicked(event->x, event->y))
        {
            m_my->activeDomino.rotation = (m_my->activeDomino.rotation + 90) % 360;
            repaint_darea();
        }

        m_my->dominoClicked = false;
        std::cout << __func__ << " " << event->button << " " <<
            event->x << " " << event->y << std::endl;

        m_my->mousePressedButton = 0;
        return true;
    }

    bool darea_on_motion_notify (GdkEventMotion *event)
    {
        if (m_my->dominoClicked) {
            double dx = event->x - m_my->lastMouseX;
            double dy = event->y - m_my->lastMouseY;

            m_my->activeDomino.posX += dx;
            m_my->activeDomino.posY += dy;

            m_my->lastMouseX = event->x;
            m_my->lastMouseY = event->y;

            repaint_darea();
        }
        
        if (m_my->mousePressedButton > 0)
            std::cout << __func__ << " " << 
                event->x << " " << event->y << std::endl;

        return true;
    }

    bool darea_on_scroll (GdkEventScroll *event)
    {
        std::cout << __func__ << " " << event->direction << " " <<
            event->x << " " << event->y << std::endl;

        return true;
    }

    void darea_on_size_allocate (Gtk::Allocation& allocation)
    {
        std::cout << __func__ << " " << allocation.get_width() << " " << 
            allocation.get_height() << std::endl;
    }

    bool darea_on_key_press (GdkEventKey *event)
    {
        switch (event->keyval) {
            case GDK_KEY_a :
                std::cout << "Key 'a' pressed" << std::endl;
                break;

            case GDK_KEY_KP_Add :
            case GDK_KEY_plus :
                std::cout << "Key '+' pressed" << std::endl;
                break;

            default : 
                std::cout << "Key pressed: GDK_KEY_" << 
                    gdk_keyval_name(event->keyval) << std::endl;
        }
        return true;
    }

};

int main (int argc, char** argv)
{
    Gtk::Main app (argc, argv);

    MyData my;
    MainWindow main_window (my);

    app.run (main_window.m_window);
}

