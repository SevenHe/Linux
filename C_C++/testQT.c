#include <qapplication.h>
#include <qpushbutton.h>

int main(int argc, char **argv) 
{
	QApplication app(argc, argv);
	
	QPushButton hello("Hello World!", 0);
	hello.resize(100, 30);
	
	app.setMainWidget(&hello);
	hello.show();
	
	return app.exec();

}
	
