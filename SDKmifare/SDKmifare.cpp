#pragma once

#include "AcceptanceForm.h"

using namespace sdkmifare;
[STAThreadAttribute]
int main() {
	Application::Run(gcnew AcceptanceForm());
	return 0;
}