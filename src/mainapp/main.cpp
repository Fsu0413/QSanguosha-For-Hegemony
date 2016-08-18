
#include <QtGlobal>
#include <QApplication>

int main(int argc, char **argv)
{
    // QT_REQUIRE_VERSION(argc, argv, "5.6.0"); // Xusine: This macro is in the documents, but I didn't find it in the real header file

    QApplication a(argc, argv);



    return a.exec();
}
