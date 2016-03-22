#pragma once

#include <maya/MObject.h>
#include <maya/MString.h>
#include <fstream>

class MolecularExporter {

private:
	char * filePath;
	std::ofstream outputFile;

public:
	MolecularExporter(char * filePath);
	void exportScene();
	void exportScene2();

private:
	void processObject(MObject obj);
	void processParticleSystem(MObject obj);
	MString getObjectName(MObject obj);

};