#include <QApplication>
#include "systemevn.h"
#include <QStringList>

const QString identifiantUnique = "b3a558c6477b4191f5ff81d662ac8cf0";

int main(int argc,char **argv)
{
    QApplication VN(argc,argv);

    QStringList id;
    id << identifiantUnique;
    id.append("Microsoft Windows");

    SystemeVN *syst = new SystemeVN;
    syst->start();

    VN.exec();
    return 0;
}
