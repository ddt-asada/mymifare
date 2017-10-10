#pragma once

#include "SDKmifare.h"

using namespace sdkmifare;
[STAThreadAttribute]
int main() {
	Application::Run(gcnew SDKmifare());
	return 0;
}