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
