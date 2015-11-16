OpenFOAM® and OpenCFD® are registered trademarks of OpenCFD Limited, the producer OpenFOAM software. All registered trademarks are property of their respective owners.
This offering is not approved or endorsed by OpenCFD Limited, the producer of the OpenFOAM software and owner of the OPENFOAM® and OpenCFD® trade marks.
http://openfoam.org/

# moveDynamicRefineMesh

Small utility which uses dynamicRefineFvMesh to refine mesh cells around certain scalarField values. Therefore it has the same limitations of dynamicRefineFvMesh library in general. This code is based on moveDynamicMesh utility in OpenFOAM-dev. For more information about the refinement controls check dynamicRefineFvMesh class description. It could be used to refine mesh around shock waves or interface.

# Don't forget use mapFields after refining!!
