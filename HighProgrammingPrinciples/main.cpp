#include "Main.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	Manager manager(argv[1], argv[2]);

	return a.exec();
}
