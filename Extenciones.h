#ifndef IMAGE_EXTENSIONS_H
#define IMAGE_EXTENSIONS_H
#include <vector>
#include <string>
using namespace std;
vector<string> Imagenes() {
    return {".png", ".jpg", ".jpeg", ".bmp", ".gif", ".tiff", ".ico", ".svg", ".icon",".gif"};
}

vector <string> Pdf(){
    return{".pdf"};
}

vector <string> Videos(){
    return{".mp4", ".mov", ".avi", ".mkv", ".webm", ".avchd", ".flv", ".swf", ".f4v"};
}
vector <string> Office(){
    return{".doc", ".docm", ".docx", ".dot", ".dotm", ".dotx", ".xls", ".xlsx", ".xlsm", ".xlt", ".ppt", ".pptx", ".pps", ".pot"};
}

vector <string> Word(){
    return{".doc", ".docm", ".docx", ".dot", ".dotm", ".dotx"};
}

vector <string> Excel(){
    return{".xls", ".xlsx", ".xlsm", ".xlt"};
}

vector <string> PowerPoint(){
    return{".ppt", ".pptx", ".pps", ".pot"};
}

vector <string> Text(){
    return{".txt", ".rtf", ".tex", ".md"};
}

vector <string> Audio(){
    return{".mp3", ".wav", ".ogg", ".flac", ".aac", ".m4a"};
}

#endif // IMAGE_EXTENSIONS_H