#pragma once
#ifndef __BSOBJECT_H__
#define __BSOBJECT_H__

#include "BSEngine.h"

class OBSObject : public OBSEngine
{
	REFLECT(OBSObject, OBSEngine)

public:

	virtual void Update() override;
	virtual void Render() override;

protected:

};

#endif //__BSOBJECT_H__