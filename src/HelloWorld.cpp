// c++ includes
#include <iostream>
// maya includes
#include <maya/MSimple.h>
#include <maya/MIOStream.h>
#include <maya/MItDag.h>
#include <maya/MFnDependencyNode.h>
// my includes
#include "MolecularExporter.h"

#define OUTPUT_FILE_PATH "C:\\Users\\dvdkouril\\Documents\\github-projects\\maya-cellview-exporter\\scene-out.txt"

// This is a shortcut for implementing CellViewExport class...so far this is enough for me
DeclareSimpleCommand(CellViewExport, "David Kouril (DVDOURIL)", "2016");

MStatus CellViewExport::doIt(const MArgList&)
{

	std::cout << "CellView Exporter" << std::endl;
	MolecularExporter molExp = MolecularExporter(OUTPUT_FILE_PATH);

	//molExp.exportScene();
	molExp.exportScene2();

	return MS::kSuccess;
}