/* Copyright 2003-2009 ROBLOX Corporation, All Rights Reserved */
#include "stdafx.h"

#include "V8DataModel/PrismInstance.h"
#include "V8World/PrismPoly.h"
#include "V8World/Primitive.h"

#ifdef _PRISM_PYRAMID_

namespace RBX
{
const char* const  sPrism = "PrismPart";

using namespace Reflection;

const char* category_Prism = "Part ";
const EnumPropDescriptor<PrismInstance, PrismInstance::NumSidesEnum> PrismInstance::prop_sidesXML(
    "sides", category_Prism, &PrismInstance::GetNumSides, &PrismInstance::SetNumSides, PropertyDescriptor::STREAMING);
static const EnumPropDescriptor<PrismInstance, PrismInstance::NumSidesEnum> prop_sidesUI(
    "Sides", category_Prism, &PrismInstance::GetNumSides, &PrismInstance::SetNumSides, PropertyDescriptor::UI);

static const Vector3 InitialPrismPartSize = Vector3(4.0, 2.0, 4.0);

// Disable slice control for now.
// const PropDescriptor<PrismInstance, int> PrismInstance::prop_slices("Slices", category_Prism, &PrismInstance::GetNumSlices, &PrismInstance::SetNumSlices);

//////////////////////////////////////////////////////////
// Constructor in PointLight-style creatable format
PrismInstance::PrismInstance()
    : DescribedCreatable<PrismInstance, PartInstance, sPrism>("Prism")
    , numSides(sides6)   // default number of sides
    , numSlices(1)       // default number of slices
{
    setName("Prism");
    Primitive* myPrim = this->getPartPrimitive();
    myPrim->setGeometryType(Geometry::GEOMETRY_PRISM);
    myPrim->setGeometryParameter("NumSides", static_cast<int>(numSides));
    myPrim->setGeometryParameter("NumSlices", numSlices);
}
//////////////////////////////////////////////////////////

PrismInstance::~PrismInstance()
{
}

PrismInstance::NumSidesEnum PrismInstance::GetNumSides() const
{
    int num = getConstPartPrimitive()->getGeometryParameter("NumSides");
    return static_cast<NumSidesEnum>(num);
}

int PrismInstance::GetNumSlices() const
{
    return getConstPartPrimitive()->getGeometryParameter("NumSlices");
}

void PrismInstance::SetNumSides(PrismInstance::NumSidesEnum num)
{
    int NumSides = num; 
    raisePropertyChanged(prop_sidesXML); 
    raisePropertyChanged(prop_sidesUI); 

    getPartPrimitive()->setGeometryParameter("NumSides", NumSides);
    getPartPrimitive()->setGeometryParameter("NumSlices", NumSides);

    shouldRenderSetDirty();
}

void PrismInstance::SetNumSlices(int num)
{
    getPartPrimitive()->setGeometryParameter("NumSlices", num);

    shouldRenderSetDirty();
}

void PrismInstance::setPartSizeXml(const Vector3& rbxSize)
{
    Vector3 newSize = rbxSize;
    Vector3 currentSize = getPartSizeXml();

    if( rbxSize.x != currentSize.x )
        newSize.x = newSize.z = rbxSize.x;
    else if( rbxSize.z != currentSize.z )
        newSize.z = newSize.x = rbxSize.z;

    if(newSize != getPartSizeXml())
    {
        Super::setPartSizeXml(newSize);
    }
    else
    {
        refreshPartSizeUi();
    }
}

} // namespace

#endif // _PRISM_PYRAMID_
