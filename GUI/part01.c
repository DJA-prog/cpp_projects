#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>
#include <math.h>
#include <ctype.h>

// Make them global

GtkWidget *window;
GtkWidget *fixed01;
GtkWidget *button01;
GtkWidget *label01;
GtkBuilder *builder;

int main(int argc, char const *argv[])
{
    gtk_init(&argc, &argv); // init Gtk

    builder = gtk_builder_new_from_file
    return 0;
}
