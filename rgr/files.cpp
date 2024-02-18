#include "files.h"
#include <iostream>

OPENFILENAME ofn;
wchar_t szFile[100] = L"";

void Files::OpenFile(Viewer* viewer) {
	

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = L'\0'; 
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = L"Image files\0*.bmp\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	GetOpenFileName(&ofn);

	if (ofn.lpstrFile[0] != L'\0') {
		viewer->setFile(ofn.lpstrFile);
	}
}

void Files::SaveFile(Viewer* viewer) {
	if (ofn.lpstrFile != NULL) {
		GetSaveFileName(&ofn);

		int w;
		int h;
		BYTE* pixelMatrix;
		pixelMatrix = viewer->saveFile(&w, &h);

		FILE* f;
		int filesize = 54 + 3 * w * h;
		int counter = 0;
		unsigned char* img = NULL;

		img = (unsigned char*)malloc(3 * w * h);
		memset(img, 0, 3 * w * h);

		for (int y = h - 1; y >= 0; y--)
		{
			for (int x = 0; x < w; x++)
			{
				BYTE r = pixelMatrix[counter + 2];
				BYTE g = pixelMatrix[counter + 1];
				BYTE b = pixelMatrix[counter];
				img[(x + y * w) * 3 + 2] = (unsigned char)(r);
				img[(x + y * w) * 3 + 1] = (unsigned char)(g);
				img[(x + y * w) * 3 + 0] = (unsigned char)(b);
				counter += 4;
			}
		}

		unsigned char bmpfileheader[14] = { 'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0 };
		unsigned char bmpinfoheader[40] = { 40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0 };
		unsigned char bmppad[3] = { 0,0,0 };

		bmpfileheader[2] = (unsigned char)(filesize);
		bmpfileheader[3] = (unsigned char)(filesize >> 8);
		bmpfileheader[4] = (unsigned char)(filesize >> 16);
		bmpfileheader[5] = (unsigned char)(filesize >> 24);

		bmpinfoheader[4] = (unsigned char)(w);
		bmpinfoheader[5] = (unsigned char)(w >> 8);
		bmpinfoheader[6] = (unsigned char)(w >> 16);
		bmpinfoheader[7] = (unsigned char)(w >> 24);
		bmpinfoheader[8] = (unsigned char)(h);
		bmpinfoheader[9] = (unsigned char)(h >> 8);
		bmpinfoheader[10] = (unsigned char)(h >> 16);
		bmpinfoheader[11] = (unsigned char)(h >> 24);

		int err = _wfopen_s(&f, ofn.lpstrFile, L"wb");
		fwrite(bmpfileheader, 1, 14, f);
		fwrite(bmpinfoheader, 1, 40, f);
		for (int i = 0; i < h; i++)
		{
			fwrite(img + (w * (h - i - 1) * 3), 3, w, f);
			fwrite(bmppad, 1, (4 - (w * 3) % 4) % 4, f);
		}

		free(img);
		fclose(f);
	}
}