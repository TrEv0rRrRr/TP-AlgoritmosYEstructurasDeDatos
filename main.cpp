#include "App.h"

int main() {
	setlocale(LC_ALL, "");

	App* app = new App();

	app->run();

	_getch();
}