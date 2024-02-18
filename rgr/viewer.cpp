#include "viewer.h"
#include <fstream>


Viewer::Viewer() {
	hWnd = NULL;
	hInst = NULL;
	IsOpenedFile = 0;
	zoom = 1;
	scrollX = 0;
	scrollY = 0;
	isMoveTool = 0;
	isPressed = false;
	pixelMatrix = new BYTE[1];
}

void Viewer::resetScreen() {
	InvalidateRect(hWnd, NULL, TRUE);
}

void Viewer::setFile(wchar_t* name) {
	img_name = name;
	IsOpenedFile = 1;
	resetScreen();
}

void Viewer::loadFile(HDC hdc) {
	BITMAP          bitmap;
	HDC             hdcMem;
	HBITMAP			oldBitmap;
	HBITMAP			hBitmap;
	hBitmap = (HBITMAP)LoadImage(NULL, img_name, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	pixelMatrix = getPixArray(hBitmap);
	hdcMem = CreateCompatibleDC(hdc);
	oldBitmap = (HBITMAP)SelectObject(hdcMem, hBitmap);
	GetObject(hBitmap, sizeof(BITMAP), &bitmap);
	img_width = bitmap.bmWidth;
	img_height = bitmap.bmHeight;
	BitBlt(hdc, STARTX, STARTY, STARTX + img_width, STARTY + img_height, hdcMem, 0, 0, SRCCOPY);
	SelectObject(hdcMem, oldBitmap);
	DeleteDC(hdcMem);
	DeleteObject(hBitmap);
	scrollbar.OnNewBmp(hWnd, img_width, img_height);
}

BYTE* Viewer::saveFile(int* img_w, int* img_h) {
	*img_w = img_width;
	*img_h = img_height;
	return pixelMatrix;
}

void Viewer::Paint(HWND hwnd, HINSTANCE hinst)
{
	if (hWnd == NULL) {
		hWnd = hwnd;
		hInst = hinst;
	}

	PAINTSTRUCT		ps;

	hdc = BeginPaint(hWnd, &ps);

	if (IsOpenedFile == 1) {
		loadFile(hdc);
		IsOpenedFile = 0;
	}
	else {
		StretchDIBits(hdc, STARTX - scrollX, STARTY - scrollY, img_width * zoom, img_height * zoom, 0, 0, img_width, img_height, pixelMatrix, &MyBMInfo, DIB_RGB_COLORS, SRCCOPY);
	}

	EndPaint(hWnd, &ps);
}

BYTE* Viewer::getPixArray(HBITMAP hBitmap)
{
	HDC hdc, hdcMem;

	hdc = GetDC(NULL);
	hdcMem = CreateCompatibleDC(hdc);

	MyBMInfo = { 0 };
	MyBMInfo.bmiHeader.biSize = sizeof(MyBMInfo.bmiHeader);

	if (0 == GetDIBits(hdcMem, hBitmap, 0, 0, NULL, &MyBMInfo, DIB_RGB_COLORS))
	{
		MessageBox(hWnd, L"ERROR0", L"Error", IDOK);
	}

	BYTE* lpPixels = new BYTE[MyBMInfo.bmiHeader.biSizeImage];

	MyBMInfo.bmiHeader.biSize = sizeof(MyBMInfo.bmiHeader);
	MyBMInfo.bmiHeader.biBitCount = 32;
	MyBMInfo.bmiHeader.biCompression = BI_RGB;
	MyBMInfo.bmiHeader.biHeight = (MyBMInfo.bmiHeader.biHeight < 0) ? (-MyBMInfo.bmiHeader.biHeight) : (MyBMInfo.bmiHeader.biHeight);

	if (0 == GetDIBits(hdc, hBitmap, 0, MyBMInfo.bmiHeader.biHeight, (LPVOID)lpPixels, &MyBMInfo, DIB_RGB_COLORS))
	{
		MessageBox(hWnd, L"ERROR", L"Error", IDOK);
	}

	return lpPixels;
}

void Viewer::zoomHDC()
{
	zoom += 0.2f;
	resetScreen();
}

void Viewer::unzoomHDC()
{
	zoom = zoom <= 1 ? 1 : zoom - 0.2f;
	resetScreen();
}

void Viewer::setScrollX(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	scrollX = scrollbar.OnHorizontalScroll(hWnd, wParam, lParam);
	resetScreen();
}

void Viewer::setScrollY(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	scrollY = scrollbar.OnVerticalScroll(hWnd, wParam, lParam);
	resetScreen();
}


void Viewer::OnLMBDown(HWND hWnd)
{
	if (isMoveTool) {
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(hWnd, &pt);
		x1 = x2 = pt.x;
		y1 = y2 = pt.y;
		isPressed = true;
	}
}

void Viewer::OnLMBUp(HWND hWnd)
{
	if (isMoveTool) {
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(hWnd, &pt);
		x2 = pt.x;
		y2 = pt.y;
		isPressed = false;
	}
}

void Viewer::OnMouseMove(HWND hWnd)
{
	if (isPressed && isMoveTool)
	{
		POINT pt;
		HDC hdc = GetDC(hWnd);
		GetCursorPos(&pt);
		ScreenToClient(hWnd, &pt);
		x2 = pt.x;
		y2 = pt.y;

		int difX = x2 - x1;
		if (difX != 0) scrollX = (int)difX;
		if (scrollX < 0) scrollX = 0;

		int difY = y2 - y1;
		if (difY != 0) scrollY = (int)difY;
		if (scrollY < 0) scrollY = 0;

		InvalidateRect(hWnd, NULL, TRUE);
	}
}

void Viewer::moveTool(int is)
{
	isMoveTool = is;
}


void Viewer::brightnessChange()
{
	int counter = 0;
	int R, G, B;
	int brightness;
	Func_MOD1(hInst, hWnd, &brightness);

	for (int y = 0; y < img_height; y++) {
		for (int x = 0; x < img_width; x++) {

			R = pixelMatrix[counter + 2] + brightness;
			G = pixelMatrix[counter + 1] + brightness;
			B = pixelMatrix[counter] + brightness;

			if (R < 0) R = 0;
			if (R > 255) R = 255;
			if (G < 0) G = 0;
			if (G > 255) G = 255;
			if (B < 0) B = 0;
			if (B > 255) B = 255;

			pixelMatrix[counter + 2] = (BYTE)R;
			pixelMatrix[counter + 1] = (BYTE)G;
			pixelMatrix[counter] = (BYTE)B;

			counter += 4;
		}
	}

	resetScreen();
}

void Viewer::contrastChange()
{
	int counter = 0;
	int R, G, B;
	int contrast;
	Func_MOD2(hInst, hWnd, &contrast);
	float factor = (259.0 * (contrast + 255.0)) / (255.0 * (259.0 - contrast));
	for (int y = 0; y < img_height; y++) {
		for (int x = 0; x < img_width; x++) {

			R = (factor * (pixelMatrix[counter + 2] - 128) + 128);
			G = (factor * (pixelMatrix[counter + 1] - 128) + 128);
			B = (factor * (pixelMatrix[counter] - 128) + 128);

			if (R < 0) R = 0;
			if (R > 255) R = 255;
			if (G < 0) G = 0;
			if (G > 255) G = 255;
			if (B < 0) B = 0;
			if (B > 255) B = 255;

			pixelMatrix[counter + 2] = (BYTE)R;
			pixelMatrix[counter + 1] = (BYTE)G;
			pixelMatrix[counter] = (BYTE)B;

			counter += 4;
		}
	}
	resetScreen();
}

void Viewer::rgbChange()
{
	int counter = 0;
	int R, G, B;
	int rMultiplier, gMultiplier, bMultiplier;
	Func_MOD3(hInst, hWnd, &rMultiplier, &gMultiplier, &bMultiplier);

	for (int y = 0; y < img_height; y++) {
		for (int x = 0; x < img_width; x++) {

			R = pixelMatrix[counter + 2] + rMultiplier;
			G = pixelMatrix[counter + 1] + gMultiplier;
			B = pixelMatrix[counter] + bMultiplier;

			if (R < 0) R = 0;
			if (R > 255) R = 255;
			if (G < 0) G = 0;
			if (G > 255) G = 255;
			if (B < 0) B = 0;
			if (B > 255) B = 255;

			pixelMatrix[counter + 2] = (BYTE)R;
			pixelMatrix[counter + 1] = (BYTE)G;
			pixelMatrix[counter] = (BYTE)B;

			counter += 4;
		}
	}

	resetScreen();
}