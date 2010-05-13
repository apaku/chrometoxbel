/*
    Copyright (c) 2010 Andreas Pakulat <apaku@gmx.de>
    All rights reserved.

    Redistribution and use in source and binary forms, with or without modification,
    are permitted provided that the following conditions are met:

    Redistributions of source code must retain the above copyright notice, this list
    of conditions and the following disclaimer.
    Redistributions in binary form must reproduce the above copyright notice, this
    list of conditions and the following disclaimer in the documentation and/or
    other materials provided with the distribution.
    Neither the name of the <ORGANIZATION> nor the names of its contributors may be
    used to endorse or promote products derived from this software without specific
    prior written permission.
    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
    ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
    ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
    ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
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

class BookMark
{
public:
    QString id;
    QString name;
    QString added;
    QString url;
};

class Folder
{
public:
    QString id;
    QString name;
    QString added;
    QList<BookMark> bookmarks;
    QList<Folder> folders;
};

BookMark readBookMark( const QMap<QString,QVariant>& bookmark )
{
    BookMark mark;
    mark.id = bookmark["id"].toString();
    mark.added = bookmark["date_added"].toString();
    mark.name = bookmark["name"].toString();
    mark.url = bookmark["url"].toString();
    return mark;
}

Folder readFolder( const QMap<QString,QVariant>& folder )
{
    Folder result;
    QList<QVariant> children = folder["children"].toList();
    result.name = folder["name"].toString();
    result.added = folder["date_added"].toString();
    result.id = folder["id"].toString();
    foreach( const QVariant& child, children ) {
        QMap<QString,QVariant> data = child.toMap();
        if( !data.contains("type") ) {
            qWarning() << "No type information in" << data;
            continue;
        }
        if( data["type"] == "folder" ) {
            result.folders << readFolder( data );
        } else if( data["type"] == "url" ) {
            result.bookmarks << readBookMark( data );
        } else {
            qWarning() << "Unknown child type:" << data["type"];
        }
    }
    return result;
}

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


    if( !ok ) {
        qWarning() << "Error parsing input file:" << inputfile.fileName();
        return -1;
    }

    QMap<QString,QVariant> objects = var.toMap();
    QMap<QString,QVariant> roots = objects["roots"].toMap();

    QList<Folder> rootfolders;

    foreach( const QString& key, roots.keys() ) {
        rootfolders << readFolder( roots[key].toMap() );
    }


    return 0;
}
