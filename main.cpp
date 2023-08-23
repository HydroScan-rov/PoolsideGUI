#include <glib.h>;
#include <gst/gst.h>;
#include <gst/video/videooverlay.h>;
#include "mainwindow.h"
#include "StabilizationSettings/StabilizationWindow.h"
#include <QApplication>
#include <QThread>

int main(int argc, char *argv[]) {
    // QApplication a(argc, argv);

    // MainWindow mainWindow;
    // mainWindow.show();
    // return a.exec();

    if (!g_thread_supported())
        g_thread_init(NULL);

    gst_init(&argc, &argv);
    QApplication app(argc, argv);
    app.connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()));

    // prepare the pipeline

    GstElement *pipeline = gst_pipeline_new("xvoverlay");
    GstElement *src = gst_element_factory_make("videotestsrc", NULL);
    GstElement *sink = gst_element_factory_make("xvimagesink", NULL);
    gst_bin_add_many(GST_BIN(pipeline), src, sink, NULL);
    gst_element_link(src, sink);

    // prepare the ui

    QWidget window;
    window.resize(320, 240);
    window.show();

    WId xwinid = window.winId();
    gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY(sink), xwinid);

    // run the pipeline

    GstStateChangeReturn sret = gst_element_set_state(pipeline,
        GST_STATE_PLAYING);
    if (sret == GST_STATE_CHANGE_FAILURE) {
        gst_element_set_state(pipeline, GST_STATE_NULL);
        gst_object_unref(pipeline);
        // Exit application
        QTimer::singleShot(0, QApplication::activeWindow(), SLOT(quit()));
    }

    int ret = app.exec();

    window.hide();
    gst_element_set_state(pipeline, GST_STATE_NULL);
    gst_object_unref(pipeline);

    return ret;
}
