#include <QCoreApplication>
#include <QStringList>
#include <QFile>
#include <QVariant>

#include <QDebug>

#include <qjson/parser.h>

#include <iostream>

void printUsage()
{
    std::cout << "Usage:" << std::endl << "\t" << QCoreApplication::arguments().at(0).toLocal8Bit().data() << " <jsoninputfile> <xbeloutputfile>" << std::endl << std::endl;
}

int main(int argc, char **argv) {
    QCoreApplication app(argc, argv);
    if( QCoreApplication::arguments().count() < 3 || QCoreApplication::arguments().count() == 2 && ( QCoreApplication::arguments().at(1) == "-h" || QCoreApplication::arguments().at(1) == "--help" ) ) {
        printUsage();
        return 1;
    }
    QFile inputfile( QCoreApplication::arguments().at( 1 ) );
    QFile outputfile( QCoreApplication::arguments().at( 1 ) );

    QJson::Parser parser;
    bool ok;
    QVariant var = parser.parse( &inputfile, &ok );

    if( ok ) {
        qDebug() << var;
    } else {
        qDebug() << parser.errorString();
    }


    return 0;
}
