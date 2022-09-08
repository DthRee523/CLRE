#include "classfile.h"

ClassFile::ClassFile(QObject *parent) : QObject(parent)
{    
    QFile studentfile("student.json");
    studentfile.open(QFile::ReadOnly);

    QByteArray studentData = studentfile.readAll();
    studentfile.close();

    QJsonDocument doc = QJsonDocument::fromJson(studentData);
    QJsonArray arr = doc.array();

    for (int i = 0; i < arr.size(); i++)
    {
        QJsonObject arrObject = arr[i].toObject();
        QString path = arrObject.take("path").toString();
        QFile classfile(path);
        if (classfile.open(QFile::ReadOnly))
        {
            Student *student = new Student;
            QByteArray classData = classfile.readAll();
            QJsonDocument classDoc = QJsonDocument::fromJson(classData);
            QJsonObject object = classDoc.object();
            student->name = object.take("name").toString();
            student->course[0].C820 = object["class"].toObject()["Monday"].toObject()["820"].toString();
            student->course[0].C1005 = object["class"].toObject()["Monday"].toObject()["1005"].toString();
            student->course[0].C1255 = object["class"].toObject()["Monday"].toObject()["1255"].toString();
            student->course[0].C1440 = object["class"].toObject()["Monday"].toObject()["1440"].toString();
            student->course[1].C820 = object["class"].toObject()["Tuesday"].toObject()["820"].toString();
            student->course[1].C1005 = object["class"].toObject()["Tuesday"].toObject()["1005"].toString();
            student->course[1].C1255 = object["class"].toObject()["Tuesday"].toObject()["1255"].toString();
            student->course[1].C1440 = object["class"].toObject()["Tuesday"].toObject()["1440"].toString();
            student->course[2].C820 = object["class"].toObject()["Wednesday"].toObject()["820"].toString();
            student->course[2].C1005 = object["class"].toObject()["Wednesday"].toObject()["1005"].toString();
            student->course[2].C1255 = object["class"].toObject()["Wednesday"].toObject()["1255"].toString();
            student->course[2].C1440 = object["class"].toObject()["Wednesday"].toObject()["1440"].toString();
            student->course[3].C820 = object["class"].toObject()["Thursday"].toObject()["820"].toString();
            student->course[3].C1005 = object["class"].toObject()["Thursday"].toObject()["1005"].toString();
            student->course[3].C1255 = object["class"].toObject()["Thursday"].toObject()["1255"].toString();
            student->course[3].C1440 = object["class"].toObject()["Thursday"].toObject()["1440"].toString();
            student->course[4].C820 = object["class"].toObject()["Friday"].toObject()["820"].toString();
            student->course[4].C1005 = object["class"].toObject()["Friday"].toObject()["1005"].toString();
            student->course[4].C1255 = object["class"].toObject()["Friday"].toObject()["1255"].toString();
            student->course[4].C1440 = object["class"].toObject()["Friday"].toObject()["1440"].toString();
            student->course[5].C820 = object["class"].toObject()["Saturday"].toObject()["820"].toString();
            student->course[5].C1005 = object["class"].toObject()["Saturday"].toObject()["1005"].toString();
            student->course[5].C1255 = object["class"].toObject()["Saturday"].toObject()["1255"].toString();
            student->course[5].C1440 = object["class"].toObject()["Saturday"].toObject()["1440"].toString();
            student->course[6].C820 = object["class"].toObject()["Sunday"].toObject()["820"].toString();
            student->course[6].C1005 = object["class"].toObject()["Sunday"].toObject()["1005"].toString();
            student->course[6].C1255 = object["class"].toObject()["Sunday"].toObject()["1255"].toString();
            student->course[6].C1440 = object["class"].toObject()["Sunday"].toObject()["1440"].toString();
            students.push_back(student);
        }
        classfile.close();
    }
}
