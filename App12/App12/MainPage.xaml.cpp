//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include <codecvt>

using namespace App12;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

MainPage::MainPage()
	: mLibzipFile(nullptr)
{
	InitializeComponent();
}

std::string PlatformStringToString(Platform::String^ ps) {
	if (ps == nullptr) {
		return std::string("");
	}
	std::wstring_convert<std::codecvt_utf8<wchar_t>> s_converter;
	return s_converter.to_bytes(ps->Data());
}

void App12::MainPage::OnClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
    auto f = Windows::ApplicationModel::Package::Current->InstalledLocation->Path;
	auto fileName = f + L"\\test.zip";
	//const char* filename = "C:\\Users\\johan\\AppData\\Local\\Packages\\d939d61b-834e-4a68-80cc-3d92e9fb04ea_5p7nm82acxzca\\LocalCache\\test.zip";
	
	auto filename = PlatformStringToString(fileName);
	int zipError = 0;
	mLibzipFile = zip_open(filename.c_str(), ZIP_CHECKCONS, &zipError);

	if (zipError == 0) {
        message->Text += L"Zip file loaded" + "\n";
	}
	else {
		zip_error_t error;
		zip_error_init_with_code(&error, zipError);
		const char* errorstr = zip_error_strerror(&error);
		OutputDebugString(L"Error while loading zip archive: %s for file!");
		zip_error_fini(&error);
	}
}
