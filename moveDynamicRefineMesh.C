/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011-2015 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Application
    moveDynamicRefineMesh

Description
    Refine mesh according to a scalarField values.
    Refinement controls in constant/dynamicMeshDict using dynamicRefineFvMesh.
    It could be used to refine mesh around shock waves or interface.
    Tip: use foamCalc to create scalarField
    example: > foamCalc magGrad p
    Don't forget use mapFields after refining!!

\*---------------------------------------------------------------------------*/

#include "argList.H"
#include "Time.H"
#include "fvCFD.H"
#include "dynamicFvMesh.H"

using namespace Foam;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{

    timeSelector::addOptions();
    #include "addOverwriteOption.H"
    #include "addRegionOption.H"
    #include "setRootCase.H"
    #include "createTime.H"
    #include "createNamedDynamicFvMesh.H"

    instantList timeDirs = timeSelector::select0(runTime, args);
    runTime.functionObjects().off();
    const word oldInstance = mesh.pointsInstance();
    const bool overwrite = args.optionFound("overwrite");

    dictionary refineDict
    (
        IOdictionary
        (
            IOobject
            (
                "dynamicMeshDict",
                runTime.constant(),
                mesh,
                IOobject::MUST_READ,
                IOobject::NO_WRITE,
                false
            )
        ).subDict(mesh.type()+ "Coeffs")
    );

    const word fieldName(refineDict.lookup("field"));

    Info<< "Reading field " << fieldName << endl;
    Info<< "Time = " << runTime.timeName() << "\n" << endl;

    volScalarField svF
    (
        IOobject
        (
            fieldName,
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ,
            IOobject::NO_WRITE
        ),
        mesh
    );

    if (!overwrite)
    {
        runTime++;
    }
    // Refine
    mesh.update();

    // Write resulting mesh
    if (overwrite)
    {
        mesh.setInstance(oldInstance);
    }

    mesh.write();

    mesh.checkMesh(true);

    Info<< "End\n" << endl;

    return 0;
}

// ************************************************************************* //
