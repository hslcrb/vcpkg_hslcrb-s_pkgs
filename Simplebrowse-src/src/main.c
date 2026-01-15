#include <gtk/gtk.h>
#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @file main.c
 * @brief Simplebrowse - A premium mini browser written in C using GTK3 and libcurl.
 * @author Rheehose (Rhee Creative)
 * @date 2026-01-15
 */

typedef struct {
    GtkWidget *window;
    GtkWidget *url_entry;
    GtkWidget *text_view;
    GtkTextBuffer *buffer;
    GtkWidget *status_label;
} BrowserApp;

// Global buffer for CURL response
struct MemoryStruct {
    char *memory;
    size_t size;
};

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    char *ptr = realloc(mem->memory, mem->size + realsize + 1);
    if (!ptr) {
        printf("not enough memory (realloc returned NULL)\n");
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

void apply_css(GtkWidget *widget) {
    GtkCssProvider *provider = gtk_css_provider_new();
    const gchar *css = 
        "window { background-color: #0f172a; color: #f8fafc; font-family: 'Inter', sans-serif; }"
        "headerbar { background: rgba(30, 41, 59, 0.8); border-bottom: 1px solid rgba(255, 255, 255, 0.1); }"
        "entry { background: rgba(51, 65, 85, 0.5); color: #f8fafc; border-radius: 8px; border: 1px solid rgba(255, 255, 255, 0.1); padding: 8px; margin: 4px; }"
        "textview text { background-color: #0f172a; color: #cbd5e1; font-family: 'Fira Code', monospace; font-size: 13px; }"
        "button { background: #3b82f6; color: white; border-radius: 6px; border: none; padding: 4px 12px; font-weight: bold; transition: all 0.2s; }"
        "button:hover { background: #2563eb; }"
        ".status { font-size: 11px; color: #94a3b8; padding: 4px; }";
    
    gtk_css_provider_load_from_data(provider, css, -1, NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                              GTK_STYLE_PROVIDER(provider),
                                              GTK_STYLE_PROVIDER_PRIORITY_USER);
}

void on_load_clicked(GtkButton *button, gpointer user_data) {
    BrowserApp *app = (BrowserApp *)user_data;
    const gchar *url = gtk_entry_get_text(GTK_ENTRY(app->url_entry));
    
    gtk_label_set_text(GTK_LABEL(app->status_label), "Connecting...");

    CURL *curl;
    CURLcode res;
    struct MemoryStruct chunk;
    chunk.memory = malloc(1);
    chunk.size = 0;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Simplebrowse/1.0");

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            char err[256];
            snprintf(err, sizeof(err), "Error: %s", curl_easy_strerror(res));
            gtk_text_buffer_set_text(app->buffer, err, -1);
            gtk_label_set_text(GTK_LABEL(app->status_label), "Failed to load.");
        } else {
            gtk_text_buffer_set_text(app->buffer, chunk.memory, -1);
            char status[64];
            snprintf(status, sizeof(status), "Loaded %lu bytes successfully.", (unsigned long)chunk.size);
            gtk_label_set_text(GTK_LABEL(app->status_label), status);
        }

        curl_easy_cleanup(curl);
        free(chunk.memory);
    }
    curl_global_cleanup();
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    BrowserApp *app = g_malloc(sizeof(BrowserApp));

    // Create Main Window
    app->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(app->window), "Simplebrowse");
    gtk_window_set_default_size(GTK_WINDOW(app->window), 1000, 700);
    g_signal_connect(app->window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Apply Premium CSS
    apply_css(app->window);

    // Header Bar
    GtkWidget *header = gtk_header_bar_new();
    gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(header), TRUE);
    gtk_header_bar_set_title(GTK_HEADER_BAR(header), "Simplebrowse");
    gtk_header_bar_set_subtitle(GTK_HEADER_BAR(header), "Premium Mini Browser");
    gtk_window_set_titlebar(GTK_WINDOW(app->window), header);

    // URL Entry
    app->url_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(app->url_entry), "Enter URL (e.g., http://google.com)");
    gtk_entry_set_text(GTK_ENTRY(app->url_entry), "https://example.com");
    gtk_header_bar_pack_start(GTK_HEADER_BAR(header), app->url_entry);
    gtk_widget_set_size_request(app->url_entry, 600, -1);

    // Load Button
    GtkWidget *load_button = gtk_button_new_with_label("Go");
    g_signal_connect(load_button, "clicked", G_CALLBACK(on_load_clicked), app);
    gtk_header_bar_pack_start(GTK_HEADER_BAR(header), load_button);

    // Layout
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(app->window), vbox);

    // Text View for Source
    GtkWidget *scrolled = gtk_scrolled_window_new(NULL, NULL);
    gtk_box_pack_start(GTK_BOX(vbox), scrolled, TRUE, TRUE, 0);
    
    app->text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(app->text_view), FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(app->text_view), TRUE);
    gtk_text_view_set_left_margin(GTK_TEXT_VIEW(app->text_view), 20);
    gtk_text_view_set_right_margin(GTK_TEXT_VIEW(app->text_view), 20);
    gtk_text_view_set_top_margin(GTK_TEXT_VIEW(app->text_view), 20);
    app->buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(app->text_view));
    gtk_container_add(GTK_CONTAINER(scrolled), app->text_view);

    // Placeholder content
    gtk_text_buffer_set_text(app->buffer, "Welcome to Simplebrowse!\nEnter a URL above to fetch content.", -1);

    // Status Label
    app->status_label = gtk_label_new("Ready");
    gtk_style_context_add_class(gtk_widget_get_style_context(app->status_label), "status");
    gtk_box_pack_start(GTK_BOX(vbox), app->status_label, FALSE, FALSE, 5);

    gtk_widget_show_all(app->window);
    gtk_main();

    g_free(app);
    return 0;
}
