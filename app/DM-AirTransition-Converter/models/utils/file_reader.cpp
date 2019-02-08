#include "file_reader.h"

FileReader::FileReader(QObject *parent) : QObject(parent)
{

}

void FileReader::readFileInfo(QString path)
{
    QString content = "";

    int linesCount = 0;

    QFile inputFile(path);
    if(inputFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream readStream(&inputFile);
        readStream.setCodec("Windows 1251");
        while(!readStream.atEnd())
        {
            content += readStream.readLine() + '\n';
            linesCount++;
            emit loading(linesCount);
        }
        emit successfullRead(content);
    }
}
