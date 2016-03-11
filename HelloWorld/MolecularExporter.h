#pragma once

#include <maya/MObject.h>
#include <fstream>

class MolecularExporter {

private:
	char * filePath;
	std::ofstream outputFile;

public:
	MolecularExporter(char * filePath);
	void exportScene();

private:
	void processObject(MObject obj);

};