#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
int getdir (string dir, vector<string> &files);
void runCommand(string s);
int main(int argc, char *argv[])
{
    string AudioLoc = argv[1];
    string VideoLoc = argv[2];
    string Finalloc = argv[3];
    string Logloc = argv[4];
    string Toolsloc = argv[5];
    string dir = string(".");
    vector<string> files = vector<string>();
    getdir(dir,files);
    for (unsigned int i = 0; i < files.size();i++) {
        if(files[i][files[i].size()-1] == 'i' && files[i][files[i].size()-2] == 'v' && files[i][files[i].size()-3] == 'a') {
            string newName = "";
            for(unsigned int j = 0; j < files[i].size() - 3; j++) {
                newName += files[i][j];
            }
            string commandVideo = Toolsloc + "x264.exe --bitrate 5000 --output " + VideoLoc +  newName + "mp4 " + files[i] + " 2>" + Logloc + files[i] +"_x264.log";;
	    string commandAudio = Toolsloc + "ffmpeg/bin/ffmpeg.exe -y -i " + files[i] + " -vn -ac 2 -ar 44100 -ab 320k -f mp3 " + AudioLoc + "outputAudio_" + newName + "mp3 2>" + Logloc + files[i] +"_ffmpeg.log";
	    string commandMux = Toolsloc + "mp4box.exe -fps 60 -add " + VideoLoc + newName + "mp4" + " -add " + AudioLoc + "outputAudio_" + newName + "mp3 " + Finalloc + newName + "mp4";                      
            cout << "Running x264...." << endl;
	    runCommand(commandVideo);
            cout << "x264 is done." << endl;               
	    cout << "Running FFMPEG...." << endl;
            runCommand(commandAudio);
            cout << "ffmpeg is done." << endl;
            cout << "Running mp4box...." << endl;
            runCommand(commandMux);
            cout << "mp4box is done." << endl;       
        }
    }
    return 0;
}
void runCommand(string s) {
    system(s.c_str());
}
int getdir (string dir, vector<string> &files) {
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }
    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}
